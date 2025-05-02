import tkinter as tk
from tkinter import ttk
import threading
import socket
import struct
import time
import logging
from io import BytesIO
import pyautogui
from PIL import ImageGrab

# Настройка логирования сервера
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s - %(levelname)s - %(message)s",
    handlers=[
        logging.FileHandler("server_log.txt", encoding='utf-8'),
        logging.StreamHandler()
    ]
)

# Фиксированные параметры сервера
SERVER_QUALITY = 85  # Качество JPEG (1-100)
SERVER_HOST = '127.0.0.1'
SERVER_PORT = 12345


class VRControlApp:
    monitor_var: tk.StringVar
    interval_var: tk.IntVar
    monitor_cb: ttk.Combobox
    freq_spin: ttk.Spinbox
    start_btn: ttk.Button
    stop_btn: ttk.Button
    status_label: ttk.Label

    server_thread: threading.Thread | None
    server_socket: socket.socket | None
    current_conn: socket.socket | None
    is_streaming: bool

    def __init__(self, master):
        self.master = master
        master.title("Control Panel")

        self.monitor_var = tk.StringVar(value="Монитор 1")
        self.interval_var = tk.IntVar(value=3000)

        self.create_widgets()

        self.is_streaming = False
        self.current_conn = None
        self.server_thread = None
        self.server_socket = None

    def create_widgets(self):
        # Фрейм выбора монитора (заглушка)
        monitor_frame = ttk.LabelFrame(self.master, text="Выбор рабочего стола")
        ttk.Label(monitor_frame, text="Номер монитора:").grid(row=0, column=0, padx=5, pady=5)
        self.monitor_cb = ttk.Combobox(
            monitor_frame,
            textvariable=self.monitor_var,
            values=["Монитор 1", "Монитор 2", "Монитор 3"],
            state="readonly"
        )
        self.monitor_cb.grid(row=0, column=1, padx=5, pady=5)
        monitor_frame.pack(fill="x", padx=10, pady=5)

        # Фрейм интервала
        interval_frame = ttk.LabelFrame(self.master, text="Интервал передачи")
        ttk.Label(interval_frame, text="Интервал (мс):").grid(row=0, column=0, padx=5, pady=5)
        self.freq_spin = ttk.Spinbox(
            interval_frame,
            textvariable=self.interval_var,
            from_=100,
            to=86400000,
            increment=100,
            validate="key",
            validatecommand=(self.master.register(self.validate_int), "%P")
        )
        self.freq_spin.grid(row=0, column=1, padx=5, pady=5)
        interval_frame.pack(fill="x", padx=10, pady=5)

        # Кнопки управления
        btn_frame = ttk.Frame(self.master)
        self.start_btn = ttk.Button(btn_frame, text="Начать передачу", command=self.start_stream)
        self.stop_btn = ttk.Button(
            btn_frame,
            text="Закончить передачу",
            command=self.stop_stream,
            state=tk.DISABLED
        )
        self.start_btn.pack(side="left", padx=10, pady=10)
        self.stop_btn.pack(side="right", padx=10, pady=10)
        btn_frame.pack(fill="x", padx=10, pady=5)

        # Статусная строка
        self.status_label = ttk.Label(
            self.master,
            text="Трансляция остановлена",
            foreground="white",
            background="red",
            anchor="center"
        )
        self.status_label.pack(fill="x", padx=10, pady=5, ipady=3)

    @staticmethod
    def validate_int(value):
        """Проверка, что введено целое число (для интервала)."""
        try:
            if value:
                int(value)
            return True
        except ValueError:
            return False

    def start_stream(self):
        """Запуск сервера в отдельном потоке."""
        if not self.is_streaming:
            try:
                interval = self.interval_var.get()
                if interval < 3 or interval > 86400000:
                    raise ValueError("Интервал должен быть 3-86400000 мс")

                self.is_streaming = True
                self.server_thread = threading.Thread(
                    target=self.run_server,
                    args=(interval,),
                    daemon=True
                )
                self.server_thread.start()

                self.update_ui_state(started=True)
                self.status_label.configure(
                    text=f"Трансляция активна | Интервал: {interval} мс",
                    background="green"
                )

            except Exception as e:
                self.status_label.configure(
                    text=f"Ошибка: {str(e)}",
                    background="orange"
                )
                self.is_streaming = False

    def stop_stream(self):
        """Остановка сервера."""
        if self.is_streaming:
            self.is_streaming = False
            self.update_ui_state(started=False)
            self.status_label.configure(
                text="Трансляция остановлена",
                background="red"
            )
            try:
                if self.current_conn:
                    self.current_conn.close()
            except (OSError, AttributeError, BrokenPipeError) as e:
                logging.debug(f"Ошибка закрытия соединения: {e}")
            try:
                if self.server_socket:
                    self.server_socket.close()
            except OSError as e:
                logging.debug(f"Ошибка закрытия сокета: {e}")

    def update_ui_state(self, started):
        """Обновление состояния элементов интерфейса."""
        self.monitor_cb.configure(state="readonly")
        self.freq_spin.configure(state=tk.DISABLED if started else tk.NORMAL)
        self.start_btn.configure(state=tk.DISABLED if started else tk.NORMAL)
        self.stop_btn.configure(state=tk.NORMAL if started else tk.DISABLED)

    def run_server(self, interval_ms):
        """Основная логика сервера."""
        try:
            self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server_socket.bind((SERVER_HOST, SERVER_PORT))
            self.server_socket.listen(1)
            logging.info(f"Сервер запущен на {SERVER_HOST}:{SERVER_PORT}")

            self.current_conn, addr = self.server_socket.accept()
            logging.info(f"Подключен клиент: {addr}")

            buffer = b''
            while self.is_streaming:
                start_time = time.time()

                # Захват скриншота
                try:
                    screenshot = ImageGrab.grab()
                except Exception as e:
                    logging.error(f"Ошибка захвата экрана: {e}")
                    continue

                # Конвертация в JPEG
                try:
                    buffered = BytesIO()
                    screenshot.save(buffered, format="JPEG", quality=SERVER_QUALITY)
                    img_data = buffered.getvalue()
                except Exception as e:
                    logging.error(f"Ошибка конвертации: {e}")
                    continue

                # Отправка изображения клиенту
                try:
                    img_size = struct.pack("!I", len(img_data))
                    self.current_conn.sendall(b"IMG:" + img_size + img_data)
                except (BrokenPipeError, ConnectionResetError):
                    logging.error("Соединение разорвано клиентом.")
                    break

                # Прием кликов
                try:
                    self.current_conn.settimeout(0.1)
                    data = self.current_conn.recv(1024)
                    if data:
                        buffer += data
                        while b'\n' in buffer:
                            msg_part, buffer = buffer.split(b'\n', 1)
                            self.handle_mouse_event(msg_part.decode().strip())
                except socket.timeout:
                    pass

                # Точное интервал
                elapsed = time.time() - start_time
                sleep_time = max(0, interval_ms / 1000 - elapsed)
                time.sleep(sleep_time)

        except ConnectionResetError:
            logging.error("Соединение разорвано клиентом.")
        except Exception as e:
            logging.error(f"Ошибка сервера: {e}")
        finally:
            self.is_streaming = False
            if self.current_conn:
                self.current_conn.close()
            if self.server_socket:
                self.server_socket.close()
            logging.info("Сервер остановлен")
            self.master.after(0, self.update_ui_state, False)
            self.master.after(0, lambda: self.status_label.configure(
                text="Трансляция остановлена",
                background="red"
            ))

    @staticmethod
    def handle_mouse_event(msg: str) -> None:
        if msg.startswith("MOUSE:"):
            try:
                parts = msg.split(":", 1)
                if len(parts) != 2:
                    raise ValueError("Неверный формат сообщения")

                click_info = parts[1].split(",")
                if len(click_info) != 3:
                    raise ValueError("Неверное количество параметров клика")

                click_type, x_str, y_str = click_info
                x = float(x_str)
                y = float(y_str)

                pyautogui.moveTo(x, y)
                mouse_button, action = click_type.split("_")
                pyautogui.click(button=mouse_button)

                logging.info(f"Клик {click_type} на ({x}, {y})")

            except Exception as e:
                logging.error(f"Ошибка обработки клика: {e}. Сообщение: {msg}")


if __name__ == "__main__":
    root = tk.Tk()
    app = VRControlApp(root)
    root.mainloop()
