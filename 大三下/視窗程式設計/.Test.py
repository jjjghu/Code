import tkinter as tk
from tkinter import *
import tkinter.colorchooser as colorchooser
import tkinter.messagebox as messagebox
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
class VariableDemo: 
    def __init__(self):
        # variable
        self.msg_on = False
        # window
        self.window = Tk()
        self.window.title("Variable")
        self.x = StringVar()
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
    
    def create_widget(self):
        label = Label(self.window, textvariable=self.x, fg="blue", bg="lightyellow", font=("Verdana", 16, "bold"), width=25, height=2)
        label.pack()
        btn = Button(self.window, text="Click me", command = self.button_on_click)
        btn.pack()
        
    def button_on_click(self):
        if self.msg_on == False:
            self.x.set("I wanna play a game")
        else:
            self.x.set("")
        self.msg_on = not self.msg_on
class RepaymentCalculator:
    def __init__(self):
        self.window = Tk()
        self.window.title("算完壓力好大")
        
        self.rate_var = StringVar()
        self.year_var = StringVar()
        self.loan_var = StringVar()
        self.month_var = StringVar()
        self.repayment_var = StringVar()
        
        self.create_widget()
    
    def start(self):
        self.window.mainloop()
    
    def create_widget(self):
        row = 0
        labelText_EntryTextVariable = [("Rate",self.rate_var), ("Year",self.year_var), ("Loan Money", self.loan_var)]
        for (labelText, EntryTextVariable) in labelText_EntryTextVariable:    
            Label(self.window, text=labelText, anchor="w", padx=5).grid(row=row, column=0, sticky="w")
            Entry(self.window, textvariable=EntryTextVariable, justify="right").grid(row=row, column=1)
            row = row + 1
        
        for (key, value) in [("Month", self.month_var), ("Repayment",self.repayment_var)]:
            Label(self.window, text=key, anchor="w", padx=5).grid(row=row, column=0, sticky="w")
            Label(self.window, textvariable=value, anchor="e").grid(row=row, column=1, sticky="e")
            row = row + 1
        
        Button(self.window, text="Calculate", command=self.calculate).grid(row=5, column=1)
    
    def calculate(self):
        try:
            rate = float(self.rate_var.get()) / 100 /    12
            years = int(self.year_var.get())
            loan = float(self.loan_var.get())
            months = years * 12
            
            if(rate != 0):            
                monthly_payment = int((loan * rate) / (1 - (1 / (1 + rate) ** months)))
            else:
                monthly_payment = int(loan * rate)
                
            repayment = monthly_payment * months

            self.month_var.set(f"{int(monthly_payment)}")
            self.repayment_var.set(f"{int(repayment)}")
        
        except ValueError:
            self.month_var.set("Error")
            self.repayment_var.set("Error")
class RadioButtonDemo:
    def __init__(self):
       self.window = Tk()
       self.window.title("RadioButton")
       
       self.var = StringVar()
       self.var.set("girl")
       
       self.create_widget()
       
    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        self.label = Label(self.window, text="You are a girl", bg="lightyellow", width=30)
        self.boy_radio = Radiobutton(self.window, text="Boy", variable=self.var, value="boy", command=self.printSelection)
        self.girl_radio = Radiobutton(self.window, text="Girl", variable=self.var, value="girl", command=self.printSelection)
        
        self.label.pack() 
        self.boy_radio.pack()
        self.girl_radio.pack()
        
    def printSelection(self):
        self.label.config(text="You are a " + self.var.get())
class FlagsDemo:
    def __init__(self):
        self.window = Tk()
        self.var = StringVar()
        self.var.set("The Selected Country")
        self.create_widget()

    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        
        self.label = Label(self.window, text="The Selected Country", bg="lightyellow", fg = "blue", width=30)
        self.label.pack()

        self.images = [] # 需要保持引用，避免被垃圾處理機制消除
        imagePaths = [("Images/Tile1.png", 1), ("Images/Tile2.png", 2), ("Images/Tile3.png", 3), ("Images/Tile4.png", 4), ("Images/Tile5.png", 5)]
        for (path, name) in imagePaths:
            image = PhotoImage(file=path)
            self.images.append(image)
            radioButton = Radiobutton(self.window, text=name, variable=self.var, value=name, image=image, indicatoron=0, command=self.printSelection)
            radioButton.pack()

    def printSelection(self):
        self.label.config(text=self.var.get())
class CheckBoxDemo:
    def __init__(self):
        self.window = Tk()
        self.window.title("CheckBox Demo")
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        self.entry = Entry(self.window, width=30)
        self.entry.pack(pady = 5)
        
        buttonFrame = Frame(self.window)
        buttonFrame.pack(pady=5)
        
        Button(buttonFrame, text="選取", command=self.select).pack(side=LEFT, padx=5)
        Button(buttonFrame, text="取消選取", command=self.deselect).pack(side=LEFT, padx=5)
        Button(buttonFrame, text="刪除", command=self.clear_entry).pack(side=LEFT, padx=5)
        Button(buttonFrame, text="結束", command=self.window.quit).pack(side=LEFT, padx=5)
        
        self.isReadOnlyVar = BooleanVar()
        self.checkbox = Checkbutton(self.window, text="唯讀", variable=self.isReadOnlyVar, command=self.readonly)
        self.checkbox.pack(pady=5)
        
    def select(self):
        self.entry.select_range(0, END)
        
    def deselect(self):
        self.entry.select_clear()
        
    def clear_entry(self):
        self.entry.delete(0, END)
        
    def readonly(self):
        if self.isReadOnlyVar.get() == True:
           self.entry.config(state=DISABLED)
        else:
            self.entry.config(state=NORMAL)
class FrameDemo:
    def __init__(self):
        self.window = Tk()
        self.window.title("Frame")
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        
        self.bgColorVar = StringVar(self.window)
        self.bgColorVar.set("pink")
        
        self.ColorFrame = Frame(self.window, bg=self.bgColorVar.get())
        self.ColorFrame.pack(padx=5,pady=5)
        
        self.CodeFrame = Frame(self.window, bg=self.bgColorVar.get())
        self.CodeFrame.pack(padx=5)
        
        Radiobutton(self.ColorFrame, text="Pink", value="pink", variable=self.bgColorVar,background=self.bgColorVar.get(),command=self.changeBg).pack(side=LEFT, padx=5)
        Radiobutton(self.ColorFrame, text="Green", value="green", variable=self.bgColorVar,background=self.bgColorVar.get(),command=self.changeBg).pack(side=LEFT, padx=5)
        Radiobutton(self.ColorFrame, text="Brown", value="brown", variable=self.bgColorVar,background=self.bgColorVar.get(),command=self.changeBg).pack(side=LEFT, padx=5)
        
        label = Label(self.CodeFrame, text="請複選常用的程式語言")
        label.pack()
        
        Checkbutton(self.CodeFrame, background = self.bgColorVar.get(), text="Python").pack(anchor=W)
        Checkbutton(self.CodeFrame, background = self.bgColorVar.get(), text="Java").pack(anchor=W)
        Checkbutton(self.CodeFrame, background = self.bgColorVar.get(), text="Ruby").pack(anchor=W)
        
    def changeBg(self):
        color = self.bgColorVar.get()
        self.ColorFrame.config(bg=color)
        self.CodeFrame.config(bg=color)
        
        # 更新ColorFrame中的單選按鈕背景色
        for widget in self.ColorFrame.winfo_children():
            widget.config(bg=color)
            
        # 更新CodeFrame中的標籤和複選框背景色
        for widget in self.CodeFrame.winfo_children():
            widget.config(bg=color)
class LabelFrameDemo: 
    def __init__(self):
        self.window = Tk()
        self.window.title("LabelFrame")
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
    
    def create_widget(self):
        self.load_image()
        self.load_LoginFrame()
        
    def load_image(self):
        self.image = PhotoImage(file="COMPLETE/Images/Cat.png")
        self.image = self.image.subsample(4)
        self.labelImage = Label(self.window, image=self.image, text="這是一隻可愛的貓", compound=BOTTOM)
        self.labelImage.pack()
    
    def load_LoginFrame(self):
        self.loginFrame = LabelFrame(self.window, text="Data check", padx=5, pady=5)
        # ID, passowrd
        self.labelID = Label(self.loginFrame, text="ID")
        self.labelPassword = Label(self.loginFrame, text="Password")
        self.entryID = Entry(self.loginFrame)
        self.entryPassword = Entry(self.loginFrame)
        self.labelID.grid(row=0, column=0)
        self.labelPassword.grid(row=1, column=0)
        self.entryID.grid(row=0, column=1)
        self.entryPassword.grid(row=1, column=1)
        self.loginFrame.pack()
class ShowInformation:
    def __init__(self):
        self.window = Tk()
        self.window.title("Show Information")
        self.createVariable()
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
        
    def createVariable(self):
        self.colorVar = IntVar()
        self.boldVar = IntVar()
        self.italicVar = IntVar()

    def create_widget(self):
        topFrame = Frame(self.window)
        topFrame.pack()
        
        Radiobutton(topFrame, text="Light Blue", bg="lightblue", variable=self.colorVar, value=1).grid(row=0, column=0)
        Radiobutton(topFrame, text="Light Green", bg="lightgreen", variable=self.colorVar, value=2).grid(row=0, column=1)
        
        Checkbutton(topFrame, text="Bold", variable=self.boldVar).grid(row=1, column=0)
        Checkbutton(topFrame, text="Italic", variable=self.italicVar).grid(row=1, column=1)
        
        inputFrame = Frame(self.window)
        inputFrame.pack()
                
        Label(inputFrame, text="Input:").pack(side=LEFT, padx=5)
        self.InputEntry = Entry(inputFrame)
        self.InputEntry.pack(side=LEFT, fill=X, expand=True, padx=5)
        Button(inputFrame, text="Run", command=self.RunButtonPressed).pack(side=LEFT, padx=5)
        
    def RunButtonPressed(self):
        
        if self.colorVar.get() == 1:
            print("Light Blue: Set")
            
        if self.colorVar.get() == 2:
            print("Light Green: Set")
            
        if self.boldVar.get() == 1:
            print("Bold: Set")
            
        if self.italicVar.get() == 1:
            print("Italic: Set")
            
        print("Name: " + self.InputEntry.get())
class ScaleDemo:
    def __init__(self):
        self.window = Tk()
        self.window.title("Scale Demo")
        self.window.geometry("300x200")
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        self.labelFrame = LabelFrame(self.window, text="Color Change")
        self.labelFrame.place(relx=0.5, rely=0.5, anchor=CENTER)
        # self.labelFrame.pack(), 和 place 不能同時使用
        
        # RGB Slider
        self.sliderFrame = Frame(self.labelFrame)
        self.sliderFrame.pack(side=TOP, fill=X)
        self.redScale = Scale(self.sliderFrame, from_=0, to=255, orient=VERTICAL, command=self.changeColor)
        self.greenScale = Scale(self.sliderFrame, from_=0, to=255, orient=VERTICAL, command=self.changeColor)
        self.blueScale = Scale(self.sliderFrame, from_=0, to=255, orient=VERTICAL, command=self.changeColor)    
        self.redScale.pack(side=LEFT, padx=5)
        self.greenScale.pack(side=LEFT, padx=5)
        self.blueScale.pack(side=LEFT, padx=5)
        
        # askColor Button
        bottomFrame = Frame(self.labelFrame)
        bottomFrame.pack(side=BOTTOM, fill=X)
        Button(bottomFrame, text="Click me!", command=self.askColor).pack(side=BOTTOM, pady=5)

    def askColor(self):
        color = colorchooser.askcolor()
        if color:
            self.window.config(bg=color[1])
            # set slider value 
            r, g, b = color[0]
            self.redScale.set(r)
            self.greenScale.set(g)
            self.blueScale.set(b)
        
    def changeColor(self, value):
        r = self.redScale.get()
        g = self.greenScale.get()
        b = self.blueScale.get()
        colorHex = "#{:02x}{:02x}{:02x}".format(r, g, b)
        self.window.config(bg=colorHex)
class SpinBoxDemo:
    def __init__(self):
        self.window = Tk()
        self.window.title("SpinBox Demo")
        self.window.geometry("300x200")
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
    
    def create_widget(self):
        self.numberSpinbox = Spinbox(self.window, from_=0, to=100, increment=5)
        self.numberSpinbox.config(font=("DFKai-SB", 16))
        self.numberSpinbox.pack()
        
        self.value = ["十日終焉", "逆轉裁判", "活俠傳"]
        self.StringSpinBox = Spinbox(self.window, values=self.value, font=("Arial", 16), command=self.change_font)
        self.StringSpinBox.pack()
        
    def change_font(self):
        current = self.StringSpinBox.get()
        if current == "十日終焉": 
            self.StringSpinBox.config(font=("Arial", 16))
        elif current == "逆轉裁判":
            self.StringSpinBox.config(font=("Arial", 16))
        elif current == "活俠傳":
            self.StringSpinBox.config(font=("DFKai-SB", 16))
class MessageBoxDemo:
    def __init__(self):
        self.window = Tk()
        self.window.title("MessageBox")
        # self.window.geometry("300x200")
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        btn_texts = [
            "NORMAL", "WARNING", "ERROR", "QUESTION", 
            "YES/NO", "ASKOKCANCEL", "ASKYESNOCANCEL", "ASKRETRYCANCEL", 
            "ASKOKCANCEL", "ASKYESNOCANCEL", "ASKRETRYCANCEL"
        ]
        # 建立一個 Frame 用來放置按鈕
        btn_frame = Frame(self.window)
        btn_frame.pack(expand=True)
        
        # 計算每排需要的列數 (兩排排列)
        num_columns = (len(btn_texts) + 1) // 2
        for idx, text in enumerate(btn_texts):
            row = idx // num_columns  # 前 num_columns 個在第一排，其餘在第二排
            col = idx % num_columns
            btn = Button(btn_frame, text=text, command=lambda t=text: self.show_message(t), width=20)
            btn.grid(row=row, column=col, padx=5, pady=5)
        
    def show_message(self, mtype):
        actions = {"NORMAL": messagebox.showinfo,
                "WARNING": messagebox.showwarning,
                "ERROR": messagebox.showerror,
                "QUESTION": messagebox.askquestion,
                "YES/NO": messagebox.askyesno,
                "ASKOKCANCEL": messagebox.askokcancel,
                "ASKYESNOCANCEL": messagebox.askyesnocancel,
                "ASKRETRYCANCEL": messagebox.askretrycancel}
        actions.get(mtype, messagebox.showinfo)("我是一個 MessageBox", "Hello, World!")      
class EventAndBindDemo:
    def __init__(self):
        self.window = Tk()
        self.window.title("Event and Bind Demo")
        self.window.geometry("800x600")
        self.createProtocolBinding()
        self.createVariable()
        self.create_widget()
    
    def start(self):
        self.window.mainloop()
        
    def createProtocolBinding(self):
        self.window.protocol("WM_DELETE_WINDOW", self.on_close)
            
    def createVariable(self):
        self.bindVar = BooleanVar()
        self.bindVar.set(False)

    def create_widget(self):
        self.textLabel = Label(self.window, text="Mouse location - x:NULL, y:NULL")
        self.textLabel.pack()
        self.window.bind("<Button-1>", self.left_click)
        self.window.bind("<Button-3>", self.right_click)
        
        bindCheckBox = Checkbutton(self.window, text="bind move", variable=self.bindVar, command=self.bind_move)
        bindCheckBox.pack()
        
    def on_close(self):
        msg = messagebox.askokcancel("OKCANCEL", "是否要關閉視窗?")
        if msg == True:
            self.window.destroy()
            
    def left_click(self, event):
        self.textLabel.config(text="Left click - x:{}, y:{}".format(event.x, event.y))
    
    def right_click(self, event):
        self.textLabel.config(text="Right click - x:{}, y:{}".format(event.x, event.y))        
    
    def move(self, event):
        self.textLabel.config(text="Move - x:{}, y:{}".format(event.x, event.y))
    
    def bind_move(self):
        if self.bindVar.get() == True:
            print("bind move")
            self.window.bind("<Motion>", self.move)
        else:
            print("unbind move")
            self.window.unbind("<Motion>")
            
class CloseWindowDemo:
    def __init__(self):
        self.window = Tk()
        self.window.title("Close Window")
        self.window.geometry("300x200")
        self.health = 3
        self.createProtocolBinding()
        self.create_widget()
    
    def start(self):
        self.window.mainloop()
        
    def createProtocolBinding(self):
        self.window.protocol("WM_DELETE_WINDOW", self.on_close)
        
    def create_widget(self):
        self.window.bind("<Key>", self.on_key_pressed)

    def show_clicked_key(self, event): 
        Label(self.window, text="Key pressed: {}".format(repr(event.char))).pack(side=TOP, anchor=W)
        
    def on_key_pressed(self, event):
        self.show_clicked_key(event)
        
    def on_close(self):
        msg = None
        if self.health > 1:
            msg = messagebox.askokcancel("OKCANCEL", "是否要關閉視窗? 您還有{}次機會".format(self.health))
        else:
            msg = messagebox.askyesno("OKCANCEL", "你真的真的要關閉視窗嗎!?".format(self.health))
        
        self.health -= 1
        if msg == True and self.health <= 0:
            self.window.destroy()
    
if __name__ == "__main__":
    closeWindowDemo = CloseWindowDemo()
    closeWindowDemo.start()