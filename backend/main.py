import socket
import struct
import time
import argparse
import logging
from io import BytesIO
import pyautogui
from PIL import ImageGrab
from screeninfo import get_monitors

# Настройка логирования
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s - %(levelname)s - %(message)s",
    handlers=[
        logging.FileHandler("server_log.txt", encoding='utf-8'),
        logging.StreamHandler()
    ]
)

class Monitor:
    def __init__(self, index, name, x, y, width, height, is_primary):
        self.index = index
        self.name = name
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.is_primary = is_primary

    @property
    def description(self):
        primary_marker = " (основной)" if self.is_primary else ""
        return (f"Монитор {self.index}: {self.name}{primary_marker}, "
                f"Разрешение: {self.width}x{self.height}, "
                f"Позиция: ({self.x}, {self.y})")

    @property
    def bbox(self):
        return (self.x, self.y, self.x + self.width, self.y + self.height)


# Получение списка всех мониторов
def get_monitors_list():
    monitors = []
    for i, m in enumerate(get_monitors(), 1):
        monitors.append(Monitor(
            index=i,
            name=m.name,
            x=m.x,
            y=m.y,
            width=m.width,
            height=m.height,
            is_primary=m.is_primary
        ))
    return monitors

# Безопасное преобразование относительных координат с округлением
def safe_coordinate_conversion(rel_value, max_value):
    pixel = round(rel_value * max_value)
    return min(max(pixel, 0), max_value - 1)

# Выбор монитора в консоли
def select_monitor_interactively():
    monitors = get_monitors_list()

    print("\nДоступные мониторы:")
    for m in monitors:
        print(m.description)

    while True:
        try:
            choice = int(input("\nВведите номер монитора: "))
            if 1 <= choice <= len(monitors):
                selected = monitors[choice - 1]
                logging.info(f"Выбран монитор: {selected.description}")
                return selected
            print("Ошибка: номер должен быть в диапазоне 1-{}".format(len(monitors)))
        except ValueError:
            print("Ошибка: введите целое число")

def main():
    logging.info(f"Программа запущена.")

    parser = argparse.ArgumentParser(description='Сервер для передачи скриншотов и обработки кликов.')
    parser.add_argument('--host', type=str, default='127.0.0.1', help='Хост сервера')
    parser.add_argument('--port', type=int, default=12345, help='Порт сервера')
    parser.add_argument('--interval', type=int, default=3000, help='Интервал между скриншотами (мс)')
    parser.add_argument('--quality', type=int, default=85, help='Качество JPEG (1-100)')
    args = parser.parse_args()

    host = args.host
    port = args.port
    interval_ms = args.interval
    quality = args.quality

    # Выбор монитора пользователем
    monitor = select_monitor_interactively()

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)
    logging.info(f"Сервер запущен на {host}:{port}. Ожидание подключения...")

    conn, addr = server_socket.accept()
    logging.info(f"Подключен клиент: {addr}")

    buffer = b''
    try:
        while True:
            # Захват скриншота
            try:
                screenshot = ImageGrab.grab(bbox=monitor.bbox)
            except Exception as e:
                logging.error(f"Ошибка захвата экрана: {e}")
                time.sleep(interval_ms / 1000)
                continue

            # Конвертация в JPEG
            try:
                buffered = BytesIO()
                screenshot.save(buffered, format="JPEG", quality=quality)
                img_data = buffered.getvalue()
            except Exception as e:
                logging.error(f"Ошибка конвертации изображения: {e}")
                time.sleep(interval_ms / 1000)
                continue

            # Отправка изображения
            try:
                img_size = struct.pack("!I", len(img_data))
                conn.sendall(b"IMG:" + img_size + img_data)
            except (BrokenPipeError, ConnectionResetError) as e:
                logging.error(f"Ошибка отправки данных: {e}")
                break
            except Exception as e:
                logging.error(f"Неизвестная ошибка при отправке: {e}")
                break

            # Прием и обработка событий
            try:
                conn.settimeout(0.001)
                data = conn.recv(1024)
                if data:
                    buffer += data
                    # Обработка всех полных сообщений
                    while b'\n' in buffer:
                        msg_part, buffer = buffer.split(b'\n', 1)
                        msg = msg_part.decode().strip()
                        if msg.startswith("MOUSE:"):
                            part1, rest = msg.split(':', 1)
                            part2, rest = rest.split(',', 1)
                            part3, part4 = rest.split(',', 1)
                            parts = [part1, part2, part3, part4]
                            if len(parts) == 4:
                                _, click_type, x_str, y_str = parts
                                try:
                                    x = float(x_str)
                                    y = float(y_str)

                                    # Преобразование координат в абсолютные
                                    x = monitor.x + safe_coordinate_conversion(x, monitor.width)
                                    y = monitor.y + safe_coordinate_conversion(y, monitor.height)

                                    pyautogui.moveTo(x, y)
                                    pyautogui.click(button=click_type)
                                    logging.info(f"Клик {click_type} на ({x}, {y})")
                                except Exception as e:
                                    logging.error(f"Ошибка обработки клика: {e}")
                            else:
                                logging.warning(f"Неверный формат сообщения: {msg}")
            except socket.timeout:
                pass
            except ConnectionResetError:
                logging.error("Соединение разорвано клиентом.")
                break
            except Exception as e:
                logging.error(f"Ошибка приема данных: {e}")
                break

            time.sleep(interval_ms / 1000)

    except KeyboardInterrupt:
        logging.info("Остановка сервера по запросу пользователя.")
    finally:
        conn.close()
        server_socket.close()
        logging.info("Сервер остановлен.")

if __name__ == "__main__":
    main()