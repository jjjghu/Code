from tkinter import *
import tkinter.messagebox as messagebox
from tkinter.ttk import *

from numpy import sort

# import tkinter.colorchooser as colorchooser

# from BaseDemo import BaseDemo, DemoContainer


class Student():
    def __init__(self):
        self.window = Tk()
        self.window.title("Student")
        self.window.geometry('')
        self.create_variable()
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
    
    def create_variable(self):
        self.nameVar = StringVar()
        self.gradeVar = StringVar()
        
    def create_widget(self):
        self.window.config(padx=20, pady=20)
        input_frame = Frame(self.window)
        Label(input_frame, text="姓名").grid(row=0, column=0, padx=(0, 5))
        Entry(input_frame, textvariable=self.nameVar, width=20).grid(row=0,column=1)
        Label(input_frame, text="成績").grid(row=1, column=0, padx=(0, 5))
        Entry(input_frame, textvariable=self.gradeVar, width=20).grid(row=1, column=1)    
        input_frame.pack()
        
        button_frame = Frame(self.window)
        Button(button_frame, text="新增", command=self.on_AddButton_pressed).grid(row = 0, column=0, padx=5)
        Button(button_frame, text="刪除", command=self.on_DelButton_pressed).grid(row = 0, column=1, padx=5)
        Button(button_frame, text="排序", command=self.on_SortButton_pressed).grid(row = 0, column=2, padx=5)
        button_frame.pack(pady=10)
        
        self.database_treeview = Treeview(self.window, column=("姓名", "成績"), show="headings")
        self.database_treeview.heading("姓名", text="姓名")
        self.database_treeview.heading("成績", text="成績")
        self.database_treeview.column("姓名",width=160, anchor=CENTER)
        self.database_treeview.column("成績",width=160, anchor=CENTER)
        self.database_treeview.pack()
        
        for i in range(10):
            self.database_treeview.insert('', 'end', values=(10 - i, 10 - i))
        
        
    def on_AddButton_pressed(self):
        if self.input_valid(): 
            student_name = self.nameVar.get()
            student_grade = self.gradeVar.get()
            print(f"學生姓名: {student_name}, 成績: {student_grade}")
            self.database_treeview.insert('', 'end', values=(student_name, student_grade))
            self.nameVar.set("")
            self.gradeVar.set("")
            
    def on_DelButton_pressed(self):
        selected_students = self.database_treeview.selection()
        for student in selected_students:
            self.database_treeview.delete(student)

    def on_SortButton_pressed(self):
        students = self.database_treeview.get_children()
        # 將項目轉換為列表，包含值和項目ID
        students_with_values = [(self.database_treeview.item(item, "values"), item) for item in students]
        # 根據第二欄位（索引1）的數字進行排序
        sorted_students = sorted(students_with_values, key=lambda x: int(x[0][1]))
        # 重新插入排序後的項目
        for i, (values, item) in enumerate(sorted_students):
            self.database_treeview.move(item, '', i)
    
    def input_valid(self): 
        student_name = self.nameVar.get()
        student_grade = self.gradeVar.get()
        if not student_name and not student_grade:         
            messagebox.showerror(title="錯誤訊息", message="請輸入資訊!")
            return False  
        elif not student_grade: 
            messagebox.showerror(title="錯誤訊息", message="請輸入成績!")    
            return False
        elif not student_name: 
            messagebox.showerror(title="錯誤訊息", message="請輸入姓名!")    
            return False
        elif not student_grade.isdigit():
            messagebox.showerror(title="錯誤訊息", message="成績應為正整數!")
            return False
        elif int(student_grade) > 100 or int(student_grade) < 0:
            messagebox.showerror(title="錯誤訊息", message="成績應為0 ~ 100 之間的正整數!")
            return False
        return True
    
if __name__=="__main__":
    student = Student()
    student.start()