import socket
import struct
import time
import argparse
import logging
from io import BytesIO
import pyautogui
from PIL import ImageGrab
from screeninfo import get_monitors
from datetime import datetime  # добавлен импорт

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

def safe_coordinate_conversion(rel_value, max_value):
    pixel = round(rel_value * max_value)
    return min(max(pixel, 0), max_value - 1)

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

def images_are_different(img1, img2):
    if img1 is None or img2 is None:
        return True

    return img1.tobytes() != img2.tobytes()


def main():
    logging.info(f"Программа запущена.")

    parser = argparse.ArgumentParser(description='Сервер для передачи скриншотов и обработки кликов.')
    parser.add_argument('--host', type=str, default='192.168.1.106', help='Хост сервера')
    parser.add_argument('--port', type=int, default=12345, help='Порт сервера')
    parser.add_argument('--interval', type=int, default=3000, help='Интервал между скриншотами (мс)')
    parser.add_argument('--quality', type=int, default=85, help='Качество JPEG (1-100)')
    args = parser.parse_args()

    host = args.host
    port = args.port
    interval_ms = args.interval
    quality = args.quality

    monitor = select_monitor_interactively()

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)
    logging.info(f"Сервер запущен на {host}:{port}. Ожидание подключения...")

    conn, addr = server_socket.accept()
    logging.info(f"Подключен клиент: {addr}")

    prev_screenshot = None
    buffer = b''
    send_timestamp = None  # для времени отправки изображения

    try:
        while True:
            # Захват скриншота
            try:
                screenshot = ImageGrab.grab(bbox=monitor.bbox)
            except Exception as e:
                logging.error(f"Ошибка захвата экрана: {e}")
                time.sleep(interval_ms / 1000)
                continue

            if images_are_different(screenshot, prev_screenshot):
                prev_screenshot = screenshot

                try:
                    buffered = BytesIO()
                    screenshot.save(buffered, format="JPEG", quality=quality)
                    img_data = buffered.getvalue()
                except Exception as e:
                    logging.error(f"Ошибка конвертации изображения: {e}")
                    time.sleep(interval_ms / 1000)
                    continue

                # Отправка изображения и логирование времени отправки
                try:
                    img_size = struct.pack("!I", len(img_data))
                    send_time = datetime.now()
                    send_timestamp = int(send_time.timestamp() * 1000)  # время в мс с эпохи
                    send_time_str = send_time.strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]
                    conn.sendall(b"IMG:" + img_size + img_data)
                    logging.info(f"Изображение отправлено. Время отправки: {send_time_str}, размер: {len(img_data)} байт")
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
                    while b'\n' in buffer:
                        msg_part, buffer = buffer.split(b'\n', 1)
                        msg = msg_part.decode().strip()
                        if msg.startswith("MOUSE:"):
                            try:
                                part1, rest = msg.split(':', 1)
                                parts = rest.split(',')
                                if len(parts) == 4:
                                    click_type = parts[0].split('_')[0]
                                    x_str = parts[1]
                                    y_str = parts[2]
                                    client_timestamp_str = parts[3]

                                    if click_type[1] != "up":
                                        x = float(x_str)
                                        y = float(y_str)

                                        x = monitor.x + safe_coordinate_conversion(x, monitor.width)
                                        y = monitor.y + safe_coordinate_conversion(y, monitor.height)
                                        pyautogui.moveTo(x, y)
                                        pyautogui.click(button=click_type)

                                        server_time = datetime.now()
                                        server_time_str = server_time.strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]

                                        try:
                                            client_ts_int = int(client_timestamp_str)
                                            client_time = datetime.fromtimestamp(client_ts_int / 1000)
                                            client_time_str = client_time.strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]
                                        except Exception:
                                            client_time_str = f"Неверный формат timestamp: {client_timestamp_str}"

                                        logging.info(f"Клик {click_type} на ({x}, {y}) получен. Время клика клиента: {client_time_str}, время получения сервера: {server_time_str}")
                                else:
                                    logging.warning(f"Неверный формат сообщения: {msg}")
                            except Exception as e:
                                logging.error(f"Ошибка разбора сообщения клика: {e}")
                        elif msg.startswith("IMG_RCVD:"):
                            try:
                                client_ts_str = msg[len("IMG_RCVD:"):].strip()
                                client_ts_int = int(client_ts_str)
                                if send_timestamp is not None:
                                    latency = client_ts_int - send_timestamp
                                    logging.info(f"Задержка передачи изображения: {latency} мс")
                                else:
                                    logging.warning("Получено подтверждение, но время отправки не зафиксировано.")
                            except Exception as e:
                                logging.error(f"Ошибка разбора сообщения IMG_RCVD: {e}")
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
