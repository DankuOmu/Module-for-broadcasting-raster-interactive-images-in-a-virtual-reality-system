import socket
import time
import struct

host = "127.0.0.1"
port = 12345

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((host, port))
    print("Подключено к серверу.")

    s.sendall(b"MOUSE:left_click,500,300\n")

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        pass

# with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#     s.connect((host, port))
#     print("Подключено. Ожидание скриншотов...")
#
#     while True:
#         header = s.recv(4)  # Размер изображения (4 байта)
#         if not header:
#             break
#         img_size = struct.unpack("!I", header)[0]
#         img_data = s.recv(img_size)
#         print(f"Получен скриншот: {len(img_data)} байт")
