import tkinter as tk
from tkinter import ttk


class VRControlApp:
    monitor_var: tk.StringVar
    frequency_var: tk.DoubleVar
    monitor_cb: ttk.Combobox
    freq_spin: ttk.Spinbox
    start_btn: ttk.Button
    stop_btn: ttk.Button
    status_label: ttk.Label

    def __init__(self, master):
        self.master = master
        master.title("Control Panel")
        self.is_streaming = False
        self.monitor_var = tk.StringVar(value="Монитор 1")
        self.frequency_var = tk.DoubleVar(value=1.0)
        self.create_widgets()

    def create_widgets(self):
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

        freq_frame = ttk.LabelFrame(self.master, text="Частота передачи")
        ttk.Label(freq_frame, text="Интервал (секунды):").grid(row=0, column=0, padx=5, pady=5)
        self.freq_spin = ttk.Spinbox(
            freq_frame,
            textvariable=self.frequency_var,
            from_=0.1,
            to=3600.0,
            increment=0.1,
            validate="key",
            validatecommand=(self.master.register(self.validate_float), "%P")
        )
        self.freq_spin.grid(row=0, column=1, padx=5, pady=5)
        freq_frame.pack(fill="x", padx=10, pady=5)

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

        self.status_label = ttk.Label(
            self.master,
            text="Статус: Трансляция остановлена",
            foreground="white",
            background="red",
            anchor="center"
        )
        self.status_label.pack(fill="x", padx=10, pady=5, ipady=3)

    @staticmethod
    def validate_float(value: str) -> bool:
        try:
            if value:
                float(value)
            return True
        except ValueError:
            return False

    def start_stream(self):
        if not self.is_streaming:
            try:
                freq = self.frequency_var.get()
                if not 0.1 <= freq <= 3600:
                    raise ValueError("Частота должна быть в диапазоне 0.1-3600 секунд")

                self.is_streaming = True
                self.monitor_cb.configure(state=tk.DISABLED)
                self.freq_spin.configure(state=tk.DISABLED)
                self.start_btn.configure(state=tk.DISABLED)
                self.stop_btn.configure(state=tk.NORMAL)

                status_text = (
                    f"Трансляция активна: {self.monitor_var.get()}, "
                    f"интервал {freq:.1f} сек"
                )
                self.status_label.configure(
                    text=status_text,
                    background="green"
                )

                print(f"Запуск трансляции: {status_text}")

            except Exception as e:
                self.status_label.configure(
                    text=f"Ошибка: {str(e)}",
                    background="orange"
                )
                self.is_streaming = False

    def stop_stream(self):
        if self.is_streaming:
            self.is_streaming = False

            self.monitor_cb.configure(state="readonly")
            self.freq_spin.configure(state=tk.NORMAL)
            self.start_btn.configure(state=tk.NORMAL)
            self.stop_btn.configure(state=tk.DISABLED)

            self.status_label.configure(
                text="Трансляция остановлена",
                background="red"
            )

            print("Трансляция остановлена")


if __name__ == "__main__":
    root = tk.Tk()
    app = VRControlApp(root)
    root.mainloop()