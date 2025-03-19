import tkinter as tk
class Calculator:
    def __init__(self):
        self.window = tk.Tk()
        self.window.title("Calculator")
        
        self.expression = ""
        self.input_text = tk.StringVar()
        
        self.create_widgets()
    def start(self):
        self.window.mainloop()
    def create_widgets(self):
        # 顯示欄位
        entry = tk.Entry(self.window, textvariable=self.input_text, font=("Arial"), justify='right', bg='yellow')
        entry.grid(row=0, column=0, columnspan=4, ipadx=8, ipady=8)
        
        # 按鈕配置
        buttons = [
            ('7', 1, 0), ('8', 1, 1), ('9', 1, 2), ('*', 1, 3),
            ('4', 2, 0), ('5', 2, 1), ('6', 2, 2), ('-', 2, 3),
            ('1', 3, 0), ('2', 3, 1), ('3', 3, 2), ('+', 3, 3),
            ('0', 4, 0), ('C', 4, 1), ('=', 4, 2)
        ]
        
        for (text, row, col) in buttons:
            btn = tk.Button(self.window, text=text, font=("Arial"), width=5, height=2, 
                            command=lambda t=text: self.on_button_click(t))
            btn.grid(row=row, column=col, padx=5, pady=5)
    
    def on_button_click(self, char):
        if char == '=':
            try:
                self.expression = str(eval(self.expression))
            except Exception:
                self.expression = "Error"
        elif char == 'C':
            self.expression = ""
        else:
            self.expression += char
        
        self.input_text.set(self.expression)
if __name__ == "__main__":
    calculator = Calculator()
    calculator.start()