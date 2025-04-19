import time
import os
import logging
from PIL import ImageGrab


# Настройка логирования
def setup_logging(log_file="screenshot_log.txt"):
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s - %(levelname)s - %(message)s",
        handlers=[
            logging.FileHandler(log_file, encoding='utf-8'),  # Запись в файл
            logging.StreamHandler()  # Вывод в консоль
        ]
    )


def take_screenshot(interval_ms, save_folder="screenshots"):
    """
    Делает скриншоты всего экрана с заданным интервалом и сохраняет их в папку save_folder

    :param interval_ms: Интервал между скриншотами в миллисекундах.
    :param save_folder: Папка для сохранения скриншотов (по умолчанию "screenshots").
    """
    if not os.path.exists(save_folder):
        try:
            os.makedirs(save_folder)
            logging.info(f"Папка {save_folder} создана.")
        except (PermissionError, OSError) as e:
            logging.error(f"Ошибка создания папки: {e}")
            return

    count = 0
    try:
        while True:
            timestamp = time.strftime("%Y%m%d_%H%M%S")
            filename = os.path.join(save_folder, f"screenshot_{timestamp}_{count}.png")

            try:
                screenshot = ImageGrab.grab()
                screenshot.save(filename)
                logging.info(f"Скриншот сохранён: {filename}")
                count += 1
            except (PermissionError, IOError) as e:
                logging.error(f"Ошибка сохранения: {e}")
            except Exception as e:
                logging.error(f"Ошибка захвата экрана: {e}")

            time.sleep(interval_ms / 1000)

    except KeyboardInterrupt:
        logging.info("Скрипт остановлен пользователем.")
    except Exception as e:
        logging.critical(f"Неожиданная ошибка: {e}")


if __name__ == "__main__":
    setup_logging()  # Инициализация логирования
    logging.info("Программа запущена.")
    time.sleep(0.1)

    try:
        interval = int(input("Введите интервал между скриншотами (мс): "))
        if interval <= 0:
            raise ValueError("Интервал должен быть > 0")
    except ValueError as e:
        logging.warning(f"Некорректный интервал: {e}. Используется 1000 мс.")
        interval = 1000

    take_screenshot(interval)