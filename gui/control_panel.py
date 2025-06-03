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
from screeninfo import get_monitors

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
SERVER_QUALITY = 85
SERVER_HOST = '127.0.0.1'
SERVER_PORT = 12345


class VRControlApp:
    monitor_var: tk.StringVar
    frequency_var: tk.DoubleVar
    quality_var: tk.IntVar
    monitor_cb: ttk.Combobox
    freq_spin: ttk.Spinbox
    quality_spin: ttk.Spinbox
    start_btn: ttk.Button
    stop_btn: ttk.Button
    status_label: ttk.Label

    def __init__(self, master):
        self.master = master
        master.title("Control Panel")

        self.monitors = self.get_monitors()
        self.selected_monitor = tk.StringVar()
        self.interval_var = tk.IntVar(value=3000)

        self.create_widgets()

        self.is_streaming = False
        self.current_conn = None
        self.server_thread = None
        self.server_socket = None

    @staticmethod
    def get_monitors():
        """Получение списка мониторов с их параметрами"""
        monitors = []
        for i, m in enumerate(get_monitors(), 1):
            primary = " (основной)" if m.is_primary else ""
            monitors.append({
                "index": i,
                "name": f"Монитор {i}: {m.width}x{m.height}{primary}",
                "bbox": (m.x, m.y, m.x + m.width, m.y + m.height)
            })
        return monitors

    def create_widgets(self):
        # Фрейм выбора монитора
        monitor_frame = ttk.LabelFrame(self.master, text="Выбор рабочего стола")
        ttk.Label(monitor_frame, text="Монитор:").grid(row=0, column=0, padx=5, pady=5)

        monitor_names = [m["name"] for m in self.monitors]
        self.monitor_cb = ttk.Combobox(
            monitor_frame,
            textvariable=self.selected_monitor,
            values=monitor_names,
            state="readonly"
        )
        self.monitor_cb.current(0)
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
                if interval < 10 or interval > 86400000:
                    raise ValueError("Интервал должен быть 10-86400000 мс")

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

    @staticmethod
    def safe_coordinate_conversion(rel_value, max_value):
        """Безопасное преобразование относительных координат"""
        pixel = round(rel_value * max_value)
        return min(max(pixel, 0), max_value - 1)

    @staticmethod
    def images_are_different(img1, img2):
        """Сравнение изображений для кэширования"""
        if img1 is None or img2 is None:
            return True
        return img1.tobytes() != img2.tobytes()

    def run_server(self, interval_ms):
        """Основная логика сервера с поддержкой выбора монитора"""
        try:
            # Получение выбранного монитора
            selected_idx = int(self.selected_monitor.get().split(":")[0].split()[-1]) - 1
            monitor = self.monitors[selected_idx]
            logging.info(f"Выбран монитор: {monitor['name']}")

            self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server_socket.bind((SERVER_HOST, SERVER_PORT))
            self.server_socket.listen(1)
            logging.info(f"Сервер запущен на {SERVER_HOST}:{SERVER_PORT}")

            self.current_conn, addr = self.server_socket.accept()
            logging.info(f"Подключен клиент: {addr}")

            prev_screenshot = None
            buffer = b''
            while self.is_streaming:
                start_time = time.time()

                # Захват скриншота выбранного монитора
                try:
                    screenshot = ImageGrab.grab(bbox=monitor["bbox"])
                except Exception as e:
                    logging.error(f"Ошибка захвата экрана: {e}")
                    continue

                # Проверка на изменения
                if self.images_are_different(screenshot, prev_screenshot):
                    prev_screenshot = screenshot

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

                # Прием и обработка кликов
                try:
                    self.current_conn.settimeout(0.1)
                    data = self.current_conn.recv(1024)
                    if data:
                        buffer += data
                        while b'\n' in buffer:
                            msg_part, buffer = buffer.split(b'\n', 1)
                            self.handle_mouse_event(msg_part.decode().strip(), monitor)
                except socket.timeout:
                    pass

                # Точный интервал
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

    def handle_mouse_event(self, msg: str, monitor: dict) -> None:
        """Обработка кликов с учетом выбранного монитора"""
        if msg.startswith("MOUSE:"):
            try:
                parts = msg.split(":", 1)
                click_info = parts[1].split(",")

                if len(click_info) != 3:
                    raise ValueError("Неверный формат сообщения")

                click_type, x_str, y_str = click_info
                x_rel = float(x_str)
                y_rel = float(y_str)

                # Преобразование координат
                x = monitor["bbox"][0] + self.safe_coordinate_conversion(x_rel, monitor["bbox"][2] - monitor["bbox"][0])
                y = monitor["bbox"][1] + self.safe_coordinate_conversion(y_rel, monitor["bbox"][3] - monitor["bbox"][1])

                pyautogui.moveTo(x, y)
                mouse_button = click_type.split("_")[0]
                pyautogui.click(button=mouse_button)

                logging.info(f"Клик {click_type} на ({x}, {y})")

            except Exception as e:
                logging.error(f"Ошибка обработки клика: {e}. Сообщение: {msg}")


if __name__ == "__main__":
    root = tk.Tk()
    app = VRControlApp(root)
    root.mainloop()
