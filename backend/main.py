import socket
import struct
import time
import argparse
import logging
from io import BytesIO
import pyautogui
from PIL import ImageGrab

# Настройка логирования
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s - %(levelname)s - %(message)s",
    handlers=[
        logging.FileHandler("server_log.txt", encoding='utf-8'),
        logging.StreamHandler()
    ]
)

def main():
    parser = argparse.ArgumentParser(description='Сервер для передачи скриншотов и обработки кликов.')
    parser.add_argument('--host', type=str, default='0.0.0.0', help='Хост сервера')
    parser.add_argument('--port', type=int, default=8888, help='Порт сервера')
    parser.add_argument('--interval', type=int, default=3000, help='Интервал между скриншотами (мс)')
    parser.add_argument('--quality', type=int, default=85, help='Качество JPEG (1-100)')
    args = parser.parse_args()

    host = args.host
    port = args.port
    interval_ms = args.interval
    quality = args.quality

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
                screenshot = ImageGrab.grab()
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
                            parts = msg.split(':')
                            if len(parts) == 4:
                                _, click_type, x_str, y_str = parts
                                try:
                                    x = float(x_str)
                                    y = float(y_str)
                                    screen_width, screen_height = pyautogui.size()
                                    real_x = int(x * screen_width)
                                    real_y = int(y * screen_height)
                                    pyautogui.moveTo(real_x, real_y)
                                    pyautogui.click(button=click_type)
                                    logging.info(f"Клик {click_type} на ({real_x}, {real_y})")
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