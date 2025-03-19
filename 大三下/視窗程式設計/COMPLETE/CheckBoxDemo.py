from tkinter import *
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
            
if __name__ == "__main__":
    checkBoxDemo = CheckBoxDemo()
    checkBoxDemo.start()