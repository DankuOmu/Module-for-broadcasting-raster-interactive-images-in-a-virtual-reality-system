import tkinter as tk
from tkinter import ttk


class VRControlApp:
    def __init__(self, master):
        self.master = master
        master.title("Control Panel")

        self.var1 = tk.IntVar(value=50)
        self.var2 = tk.IntVar(value=0)
        self.mode_var = tk.StringVar(value="c1")

        self.label1 = tk.Label(master, text="a:")
        self.scale1 = tk.Scale(master, from_=0, to=100, variable=self.var1, orient='horizontal')

        self.label2 = tk.Label(master, text="b:")
        self.spinbox2 = tk.Spinbox(master, from_=0, to=100, textvariable=self.var2)

        self.mode_label = tk.Label(master, text="c:")
        self.mode_combobox = ttk.Combobox(
            master,
            textvariable=self.mode_var,
            values=["c1", "c2", "c3", "c4"]
        )

        self.button_frame = tk.Frame(master)
        self.status_button = tk.Button(self.button_frame, text="status", command=self.show_status)
        self.exit_button = tk.Button(self.button_frame, text="stop", command=self.master.destroy)

        self.label1.grid(row=0, column=0, padx=10, pady=5, sticky="w")
        self.scale1.grid(row=0, column=1, padx=10, pady=5)
        self.label2.grid(row=1, column=0, padx=10, pady=5, sticky="w")
        self.spinbox2.grid(row=1, column=1, padx=10, pady=5)
        self.mode_label.grid(row=2, column=0, padx=10, pady=5, sticky="w")
        self.mode_combobox.grid(row=2, column=1, padx=10, pady=5)

        self.button_frame.grid(row=3, column=0, columnspan=2, pady=10)
        self.status_button.pack(side="left", padx=20)
        self.exit_button.pack(side="right", padx=20)

    def show_status(self):
        print(
            f"status:\n"
            f"a = {self.var1.get()}%\n"
            f"b = {self.var2.get()}%\n"
            f"c = {self.mode_var.get()}"
        )


if __name__ == "__main__":
    root = tk.Tk()
    app = VRControlApp(root)
    root.mainloop()