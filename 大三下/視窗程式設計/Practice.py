from tkinter import *
from tkinter.ttk import Combobox, Notebook, Style, Progressbar, Button as ttk_Button, Treeview
import tkinter.colorchooser as colorchooser
import tkinter.messagebox as messagebox
from BaseDemo import BaseDemo, DemoContainer
class Calculator:
    def __init__(self):
        self.window = Tk()
        self.window.title("Calculator")
        
        self.expression = ""
        self.input_text = StringVar()
        
        self.create_widgets()
        
    def start(self):
        self.window.mainloop()
    
    def create_widgets(self):
        # 顯示欄位
        entry = Entry(self.window, textvariable=self.input_text, font=("Arial"), justify='right', bg='yellow')
        entry.grid(row=0, column=0, columnspan=4, ipadx=8, ipady=8)
        
        # 按鈕配置
        buttons = [
            ('7', 1, 0), ('8', 1, 1), ('9', 1, 2), ('*', 1, 3),
            ('4', 2, 0), ('5', 2, 1), ('6', 2, 2), ('-', 2, 3),
            ('1', 3, 0), ('2', 3, 1), ('3', 3, 2), ('+', 3, 3),
            ('0', 4, 0), ('C', 4, 1), ('=', 4, 2)
        ]
        
        for (text, row, col) in buttons:
            btn = Button(self.window, text=text, font=("Arial"), width=5, height=2, 
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
        self.window.title("Variable Demo")
        self.x = StringVar()
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
    
    def create_widget(self):
        label = Label(self.window, textvariable=self.x, fg="blue", bg="lightyellow", font=("Verdana", 16, "bold"), width=25, height=2)
        label.pack()
        btn = Button(self.window, text="Click me", command = self.on_button_click)
        btn.pack()
        
    def on_button_click(self):
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
       self.window.title("RadioButton Demo")
       
       self.var = StringVar()
       self.var.set("girl")
       
       self.create_widget()
       
    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        self.label = Label(self.window, text="You are a girl", bg="lightyellow", width=30)
        self.boy_radio = Radiobutton(self.window, text="Boy", variable=self.var, value="boy", command=self.print_selection)
        self.girl_radio = Radiobutton(self.window, text="Girl", variable=self.var, value="girl", command=self.print_selection)
        
        self.label.pack() 
        self.boy_radio.pack()
        self.girl_radio.pack()
        
    def print_selection(self):
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
            radioButton = Radiobutton(self.window, text=name, variable=self.var, value=name, image=image, indicatoron=0, command=self.print_selection)
            radioButton.pack()

    def print_selection(self):
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
        self.window.title("Frame Demo")
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
        
        Radiobutton(self.ColorFrame, text="Pink", value="pink", variable=self.bgColorVar,background=self.bgColorVar.get(),command=self.change_bg).pack(side=LEFT, padx=5)
        Radiobutton(self.ColorFrame, text="Green", value="green", variable=self.bgColorVar,background=self.bgColorVar.get(),command=self.change_bg).pack(side=LEFT, padx=5)
        Radiobutton(self.ColorFrame, text="Brown", value="brown", variable=self.bgColorVar,background=self.bgColorVar.get(),command=self.change_bg).pack(side=LEFT, padx=5)
        
        label = Label(self.CodeFrame, text="請複選常用的程式語言")
        label.pack()
        
        Checkbutton(self.CodeFrame, background = self.bgColorVar.get(), text="Python").pack(anchor=W)
        Checkbutton(self.CodeFrame, background = self.bgColorVar.get(), text="Java").pack(anchor=W)
        Checkbutton(self.CodeFrame, background = self.bgColorVar.get(), text="Ruby").pack(anchor=W)
        
    def change_bg(self):
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
        self.window.title("LabelFrame Demo")
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
    
    def create_widget(self):
        self.load_image()
        self.load_LoginFrame()
        
    def load_image(self):
        self.image = PhotoImage(file="Images/Cat.png")
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
        self.window.title("MessageBox Demo")
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
        self.create_protocol_binding()
        self.create_variable()
        self.create_widget()
    
    def start(self):
        self.window.mainloop()
        
    def create_protocol_binding(self):
        self.window.protocol("WM_DELETE_WINDOW", self.on_close)
            
    def create_variable(self):
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
        self.window.title("Close Window Demo")
        self.window.geometry("300x200")
        self.health = 3
        self.create_protocol_binding()
        self.create_widget()
        self.create_binding()
    
    def start(self):
        self.window.mainloop()
        
    def create_protocol_binding(self):
        self.window.protocol("WM_DELETE_WINDOW", self.on_close)
        
    def create_widget(self):
        self.canvas = Canvas(self.window)
        self.scrollbar = Scrollbar(self.canvas, orient=VERTICAL, command=self.canvas.yview)
        self.key_frame = Frame(self.canvas)
        
        self.canvas.create_window((0, 0), window=self.key_frame, anchor="nw")
        self.canvas.configure(yscrollcommand=self.scrollbar.set)
        self.canvas.pack(side=LEFT, fill=BOTH, expand=True)
        
        self.scrollbar.pack(side=RIGHT, fill=Y)
        
        
    def create_binding(self):
        self.window.bind("<Key>", self.on_key_pressed)
        self.key_frame.bind("<Configure>", self.on_frame_configure)

    def show_clicked_key(self, event): 
        Label(self.key_frame, text="Key pressed: {}".format(repr(event.char))).pack(side=TOP, anchor=W)
        
    def on_frame_configure(self, event):
        self.canvas.configure(scrollregion=self.canvas.bbox("all"))
        
    def on_key_pressed(self, event):
        if(event.char == 'q'):
            self.window.destroy()
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
class ListboxDemo:
    def __init__(self):
        self.window = Tk()
        self.window.title("ListBox Demo")
        self.window.geometry("500x250")
        self.create_widget()
        self.create_binding()
        
    def start(self):
        self.window.mainloop()

    def create_widget(self):
        self.inputFrame = Frame(self.window)
        self.inputFrame.pack(fill=X, padx=5, pady=5, anchor=W)

        self.leftListBoxFrame = Frame(self.window)
        self.leftListBoxFrame.pack(side=LEFT)
        
        self.rightListBoxFrame = Frame(self.window)
        self.rightListBoxFrame.pack(side=LEFT)
        
        # inputFrame
        self.inputEntry = Entry(self.inputFrame)
        self.inputEntry.pack(side=LEFT)
        self.inputConfirmButton = Button(self.inputFrame, text="Add")
        self.inputConfirmButton.pack(side=LEFT, padx=(5,0))
        
        # LeftListboxFrame
        self.listbox1 = Listbox(self.leftListBoxFrame, selectmode=EXTENDED)
        self.listbox1.pack(fill=X, pady=5, padx=5, anchor=W)
        self.listbox1.insert(END, "MINION_EXPANDER")
        self.listbox1.insert(END, "DIAMOND_SPREADING")
        self.listbox1.insert(END, "PORK_CHOP")
        
        self.MoveToList2Button = Button(self.leftListBoxFrame, text="MoveToListbox2")
        self.MoveToList2Button.pack(anchor=CENTER)
        
        # RightListboxFrame
        self.listbox2 = Listbox(self.rightListBoxFrame, selectmode=EXTENDED)
        self.listbox2.pack(fill=X, pady=5, padx=0, anchor=W)
        self.listbox2.insert(END, "SING MY PLEASURE")
        self.listbox2.insert(END, "GOLDEN HOUR")
        self.listbox2.insert(END, "PHASMOPHOBIA")
        
        self.MoveToList1Button = Button(self.rightListBoxFrame, text="MoveToListbox1")
        self.MoveToList1Button.pack(anchor=CENTER)
        
    def create_binding(self):
        self.inputConfirmButton.config(command=self.on_input_confirm)
        self.window.bind("<Key>", self.digit_key_binding)
        self.MoveToList1Button.config(command=self.on_moveToList1Button_pressed)
        self.MoveToList2Button.config(command=self.on_moveToList2Button_pressed)
            
    def digit_key_binding(self, event):
        if(event.char.isdigit()):
            pressedIndex = int(event.char) - 1
            if(self.listbox1.select_includes(pressedIndex)):
                self.listbox1.selection_clear(pressedIndex)
            else:
                self.listbox1.selection_set(pressedIndex)
                
    def on_input_confirm(self):
        entryValue = self.inputEntry.get()
        if(entryValue):        
            self.inputEntry.delete(0, END)
            self.listbox1.insert(END, entryValue)

    def on_moveToList1Button_pressed(self):
        indexs = self.listbox2.curselection()
        for index in indexs:
            insertedItem = self.listbox2.get(index)
            self.listbox1.insert(END, insertedItem)
        for index in reversed(indexs):
            self.listbox2.delete(index)  
            
    def on_moveToList2Button_pressed(self):
        indexs = self.listbox1.curselection()
        for index in indexs:
            insertedItem = self.listbox1.get(index)
            self.listbox2.insert(END, insertedItem)
        for index in reversed(indexs):
            self.listbox1.delete(index)
class WidgetPractice:
    def __init__(self):
        # Scrollbar
        # OptionMenu
        # ComboBox
        self.window = Tk()
        self.window.title("Widget Practice")
        self.window.geometry('')
        self.create_variable()
        self.create_widget()
        self.create_binding()
        
    def start(self):
        self.window.mainloop()
    
    def create_variable(self):
        self.colorVar = StringVar()
        self.fontsizeVar = IntVar()
        
    def create_widget(self):
        # inputFrame
        self.inputFrame = Frame(self.window)
        self.inputFrame.pack()
        
        self.inputEntry = Entry(self.inputFrame)
        self.inputAddButton = Button(self.inputFrame, text="Add")
        self.inputDelButton = Button(self.inputFrame, text="Del")

        self.inputEntry.pack(side=LEFT, padx=5, pady=5)
        self.inputAddButton.pack(side=LEFT, padx=5, pady=5)   
        self.inputDelButton.pack(side=LEFT, padx=5, pady=5)
        
        # Scrollbar
        self.scrollbarFrame = Frame(self.window)
        self.scrollbarFrame.pack()
        
        self.scrollbar = Scrollbar(self.scrollbarFrame)
        self.scrollbar.pack(side=RIGHT, fill=Y)
        
        self.listbox = Listbox(self.scrollbarFrame, selectmode=MULTIPLE, yscrollcommand=self.scrollbar.set)
        self.listbox.pack()
        
        self.scrollbar.config(command=self.listbox.yview)
        
        # OptionMenu
        colors = ["red", "blue", "green", "yellow", "white"]
        self.colorOptionMenu = OptionMenu(self.window, self.colorVar, *colors)
        self.colorOptionMenu
        self.colorOptionMenu.pack(pady=5)
        
        # Combobox
        self.fontsizeComboBox = Combobox(self.window, textvariable=self.fontsizeVar, value=[12, 14, 16, 18, 20])
        self.fontsizeComboBox.set(12)
        self.fontsizeComboBox.pack(padx=5, pady=5)
        
    def create_binding(self):
        self.inputAddButton.config(command=self.on_AddButton_pressed)
        self.inputDelButton.config(command=self.on_DelButton_pressed)
        self.colorVar.trace_add("write", self.on_colorVar_changed)
        self.fontsizeVar.trace_add("write", self.on_fontsize_changed)
        
    def on_AddButton_pressed(self):
        entryValue = self.inputEntry.get()
        if(entryValue):
            self.inputEntry.delete(0, END)
            self.listbox.insert(END, entryValue)
    
    def on_DelButton_pressed(self):
        indexs = self.listbox.curselection()
        for index in reversed(indexs):
            self.listbox.delete(index)
    
    def on_colorVar_changed(self, *args):
        color = self.colorVar.get()
        self.listbox.config(bg=color)  
        
    def on_fontsize_changed(self, *args):
        fontsize = self.fontsizeVar.get()
        self.listbox.config(font=('MiSans', fontsize))
class PanedWindowDemo:
    def __init__(self):
        self.window = Tk()
        self.window.title("PanedWindow Demo")
        self.window.geometry('')
        self.create_widget()
    
    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        self.paned_window = PanedWindow(self.window, orient="horizontal")
        self.paned_window.pack(fill=BOTH, expand=True)
        
        # self.frame1 = Frame(self.window, bg="red")
        # self.paned_window.add(self.frame1, minsize=100)
        
        # self.frame2 = Frame(self.window, bg="blue")
        # self.paned_window.add(self.frame2, minsize=100) 
        
        WIDTH = 120
        self.leftFrame = LabelFrame(self.window, text="leftFrame", width=WIDTH, height=150)
        self.paned_window.add(self.leftFrame, weight=1) # weight = 拉深受影響的程度
        
        self.midFrame = LabelFrame(self.window, text="midFrame", width=WIDTH)
        self.paned_window.add(self.midFrame, weight=1)
        
        self.rightFrame = LabelFrame(self.window, text="rightFrame", width=WIDTH)
        self.paned_window.add(self.rightFrame, weight=1)
class NoteBookDemo:
    def __init__(self):
        self.window.title("NoteBook Demo")
        self.window.geometry('300x200')
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        notebook = Notebook(self.window)
        notebook.pack(padx=10, pady=10, fill=BOTH, expand=True)
        
        frame1 = Frame(self.window)
        notebook.add(frame1, text="Frame1")
        
        frame2 = Frame(self.window)
        notebook.add(frame2, text="Frame2")
        
        button = Button(frame1, text="Click me!", command=self.on_button_pressed)
        button.pack()
        
    def on_button_pressed(self):
        messagebox.showinfo("messagebox!", "HELLO!")    
class ProgressBarDemo:
    def __init__(self):
        self.window.title("Progressbar Demo")
        self.window.geometry('300x200')
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        self.progressbar = Progressbar(self.window, 
                                     length=200,          
                                     mode='determinate',   
                                     maximum=100,          
                                     value=0)              
        self.progressbar.pack(pady=20)
        
        Button(self.window, text="Start", command=self.on_startProgressButton_pressed).pack(pady=5)
        Button(self.window, text="Reset", command=self.on_resetProgressButton_pressed).pack(pady=5)
    
    def on_startProgressButton_pressed(self):
        value = self.progressbar['value']
        if value < 100:
            self.progressbar['value'] += 10
            self.window.after(100, self.on_startProgressButton_pressed)  # 每 100ms 更新一次
    
    def on_resetProgressButton_pressed(self):
        self.progressbar['value'] = 0
class MenuDemo:
    def __init__(self):
        self.window.title("Menu Demo")
        self.window.geometry('300x200')
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        # 創建主選單列
        self.menubar = Menu(self.window)
        self.window.config(menu=self.menubar)
        
        # 創建檔案選單
        self.fileMenu = Menu(self.menubar, tearoff=0)  # tearoff=0 移除虛線
        self.menubar.add_cascade(label="檔案", menu=self.fileMenu)
        self.fileMenu.add_command(label="開啟", command=self.on_open)
        self.fileMenu.add_command(label="儲存", command=self.on_save)
        self.fileMenu.add_separator()  # 分隔線
        self.fileMenu.add_command(label="離開", command=self.window.quit)
        
        # 創建編輯選單
        self.editMenu = Menu(self.menubar, tearoff=0)
        self.menubar.add_cascade(label="編輯", menu=self.editMenu)
        self.editMenu.add_command(label="剪下", command=self.on_cut)
        self.editMenu.add_command(label="複製", command=self.on_copy)
        self.editMenu.add_command(label="貼上", command=self.on_paste)
        
        # 創建說明選單
        self.helpMenu = Menu(self.menubar, tearoff=0)
        self.menubar.add_cascade(label="說明", menu=self.helpMenu)
        self.helpMenu.add_command(label="關於", command=self.show_about)
    
    def on_open(self):
        messagebox.showinfo("開啟", "開啟檔案")
        
    def on_save(self):
        messagebox.showinfo("儲存", "儲存檔案")
        
    def on_cut(self):
        messagebox.showinfo("剪下", "剪下內容")
        
    def on_copy(self):
        messagebox.showinfo("複製", "複製內容")
        
    def on_paste(self):
        messagebox.showinfo("貼上", "貼上內容")
        
    def show_about(self):
        messagebox.showinfo("關於", "這是一個選單示範程式")
class MenuPart(BaseDemo):
    def __init__(self, window=None):
        super().__init__(window)
        self.create_widget()
        
    def create_widget(self):
        # 主選單
        self.menubar = Menu(self.window)
        self.window.config(menu=self.menubar)
        
        # Function
        self.functionMenu = Menu(self.menubar, tearoff=False)
        self.menubar.add_cascade(label="Function", menu=self.functionMenu)
        self.functionMenu.add_command(label="Start Progress", command=self.on_start_progress)
        self.functionMenu.add_command(label="Stop Progress", command=self.on_stop_progress)
        
        # Appearance
        self.appearanceMenu = Menu(self.menubar, tearoff=False)
        self.menubar.add_cascade(label="Appearance", menu=self.appearanceMenu)
        self.appearanceMenu.add_command(label="Red", command=lambda color="red": self.on_appearance_change(color))
        self.appearanceMenu.add_command(label="Green", command=lambda color="green": self.on_appearance_change(color))
        self.appearanceMenu.add_command(label="Blue", command=lambda color="blue": self.on_appearance_change(color))
        
        # Mode
        self.modeMenu = Menu(self.menubar, tearoff=False)
        self.menubar.add_cascade(label="Mode", menu=self.modeMenu)
        self.modeMenu.add_command(label="Normal", command=lambda mode="determinate":self.on_progressBarStatus_change(mode))
        self.modeMenu.add_command(label="Indeterminate", command=lambda mode="indeterminate":self.on_progressBarStatus_change(mode))
        
    def on_start_progress(self):
        if self.container:
            progress_demo = self.container.get_demo(ProgressBarPart)
            if progress_demo:
                progress_demo.start_progress()

    def on_stop_progress(self):
        if self.container:
            progress_demo = self.container.get_demo(ProgressBarPart)
            if progress_demo:
                progress_demo.stop_progress()
    
    def on_appearance_change(self, color : str):
        if self.container:
            progress_demo = self.container.get_demo(ProgressBarPart)
            if progress_demo:
                progress_demo.change_color(color)
        
    def on_progressBarStatus_change(self, mode : str):
        if self.container:
            progress_demo = self.container.get_demo(ProgressBarPart)
            if progress_demo:
                progress_demo.change_mode(mode)         
class ProgressBarPart(BaseDemo):
    def __init__(self, window=None):
        super().__init__(window)
        self.progress_value = 0
        self.is_running = False
        self.create_style()
        self.create_widget()

    def create_style(self):
        style = Style()
        style.theme_use('clam')
        self.STYLE_RED = "red.Horizontal.TProgressbar"
        self.STYLE_GREEN = "green.Horizontal.TProgressbar"
        self.STYLE_BLUE = "blue.Horizontal.TProgressbar"
        style.configure(self.STYLE_RED, troughcolor='white', background='red')
        style.configure(self.STYLE_GREEN, troughcolor='white', background='green')
        style.configure(self.STYLE_BLUE, troughcolor='white', background='blue')
        
    def create_widget(self):
        self.progressbar = Progressbar(self.window, length=500, mode='determinate', maximum=100, value=0)
        self.progressbar.configure(style=self.STYLE_GREEN)
        self.progressbar.pack(padx=20, pady=20)
        
    def start_progress(self):
        self.is_running = True
        self.update_progress()
        
    def stop_progress(self):
        self.is_running = False
        
    def update_progress(self):
        if self.is_running:
            self.progress_value = (self.progress_value + 1) % 101
            self.progressbar['value'] = self.progress_value
            self.window.after(50, self.update_progress)
            
    def change_color(self, color):
        style_name = f"{color}.Horizontal.TProgressbar"
        self.progressbar.configure(style=style_name)

    def change_mode(self, mode):
        self.progressbar.configure(mode=mode)
class TreeViewDemo:
    def __init__(self):
        self.window:Tk = Tk()
        self.window.title("TreeView")
        self.window.geometry("")
        self.create_widget()
    
    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        cities = ["台北", "台中", "台南"]
        roads = ["中正街", "中華路", "中山路"]
        tree = Treeview(self.window, columns=("cities", "roads"), show="headings")
        
        tree.heading("cities", text="城市")
        tree.heading("roads", text="道路")
        
        tree.column("cities", width=150, anchor="center")
        tree.column("roads", width=150, anchor="center")
                
        
        tree.tag_configure("evenrow", background="lightgrey")
        tree.tag_configure("oddrow", background="white")
        
        for i in range(len(cities)):
            if i % 2 == 0:
                tree.insert("", "end", values=(cities[i], roads[i]), tags=("evenrow",))
            else:
                tree.insert("", "end", values=(cities[i], roads[i]), tags=("oddrow",))
            
        tree.pack(padx=20, pady=20)

if __name__ == "__main__":
    # demo_container = DemoContainer()
    
    # menu_demo = demo_container.add_demo(MenuPart)
    # progress_demo = demo_container.add_demo(ProgressBarPart)
    
    # menu_demo.set_container(demo_container)
    # demo_container.window.title("ProgressBar With Demo")
    # demo_container.start()
    
    # Calculator, VariableDemo, RepaymentCalculator, RadioButtonDemo, FlagsDemo
    # LabelFrameDemo ShowInformation, ScaleDemo, SpinBoxDemo,
    # MessageBoxDemo, EventAndBindDemo, CloseWindowDemo, ListboxDemo
    # WidgetPractice, PanedWindowDemo, NoteBookDemo, ProgressBarDemo, MenuDemo
    demo = TreeViewDemo()
    demo.start()