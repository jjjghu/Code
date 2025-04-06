from tkinter import *
from tkinter.ttk import *
import tkinter.messagebox as messagebox
from enum import Enum
from dataclasses import dataclass
from typing import List
    
class SortType(Enum):
    NAME = "name"
    GRADE = "grade"
    
@dataclass
class StudentInfo: 
    name: str
    grade: int
    is_deleted : bool = False

class StudentData:
    def __init__(self):
        self.students: List[StudentInfo] = []

    def add_student(self, name:str, grade:int):
        student = StudentInfo(name, grade)
        self.students.append(student)
    
    def delete_student(self, name:str) -> bool : 
        for student in self.students:
            if student.name == name:
                student.is_deleted == True
                return True
        return False

    def search_student(self, name:str):
        for student in self.students:
            if student.name == name and not student.is_deleted:
                return student
        return None
    
    def get_all_students(self, show_deleted : bool = False):
        if not show_deleted:
            return [student for student in self.students if not student.is_deleted]
        else: 
            return [student for student in self.students if student.is_deleted]  

    def sort_students(self, sort_type:SortType, ascending: bool):
        print("sort_students")
        students = self.get_all_students()
        if sort_type == SortType.NAME.value:
            return sorted(students, key=lambda x: x.name, reverse = not ascending)
        elif sort_type == SortType.GRADE.value:
            return sorted(students, key=lambda x: x.name, reverse = ascending)
        
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
        self.student_data = StudentData()
        self.nameVar = StringVar()
        self.gradeVar = StringVar()
        self.show_deleted = BooleanVar()
        
        self.sort_reference = StringVar()
        self.sort_reference.set(SortType.NAME.value)
        self.sort_ascending = BooleanVar()
        
    def create_widget(self):
        self.window.config(padx=20, pady=20)
        
        # input layout 
        input_frame = Frame(self.window)
        Label(input_frame, text="姓名").grid(row=0, column=0, padx=(0, 5))
        Entry(input_frame, textvariable=self.nameVar, width=20).grid(row=0,column=1)
        Label(input_frame, text="成績").grid(row=1, column=0, padx=(0, 5))
        Entry(input_frame, textvariable=self.gradeVar, width=20).grid(row=1, column=1)    
        input_frame.pack()
        
        # button layout 
        button_frame = Frame(self.window)
        Button(button_frame, text="新增", command=self.on_addButton_pressed).grid(row = 0, column=0, padx=5)
        Button(button_frame, text="搜尋", command=self.on_searchButton_pressed).grid(row = 0, column=1, padx=5)
        Button(button_frame, text="刪除", command=self.on_delButton_pressed).grid(row = 0, column=2, padx=5)
        Button(button_frame, text="更新", command=self.on_updateButton_pressed).grid(row=0, column=3, padx=5)
        button_frame.pack(pady=10)
        
        
        # option layout 
        option_frame = Frame(self.window)
        Checkbutton(option_frame, text="升序", variable=self.sort_ascending).grid(row = 0, column=0, padx=5) 
        Radiobutton(option_frame, text="依姓名排列", variable=self.sort_reference, value=SortType.NAME.value, command=self.sort_students).grid(row=0, column=1, padx=5)
        Radiobutton(option_frame, text="依成績排列", variable=self.sort_reference, value=SortType.GRADE.value, command=self.sort_students).grid(row=0, column=2, padx=5)
        Checkbutton(option_frame, text="顯示刪除資訊", variable=self.show_deleted).grid(row=0, column=3, padx=5)
        option_frame.pack(pady=10)
        
        # Treeview layout
        database_frame = Frame(self.window)
        y_scrollbar = Scrollbar(database_frame, orient=VERTICAL)
        x_scrollbar = Scrollbar(database_frame, orient=HORIZONTAL)
    
        self.database_treeview = Treeview(
            database_frame, 
            column=("姓名", "成績"), 
            show="headings", 
            yscrollcommand=y_scrollbar.set, 
            xscrollcommand= x_scrollbar.set
        )
        self.database_treeview.heading("姓名", text="姓名")
        self.database_treeview.heading("成績", text="成績")
        self.database_treeview.column("姓名",width=160, anchor=CENTER)
        self.database_treeview.column("成績",width=160, anchor=CENTER)
        self.database_treeview.grid(row=0, column=0, sticky=NSEW)
        
        y_scrollbar.grid(row=0, column=1, sticky='ns')
        x_scrollbar.grid(row=1, column=0, sticky='ew')
    
        y_scrollbar.config(command=self.database_treeview.yview)
        x_scrollbar.config(command=self.database_treeview.xview)
        
        database_frame.grid_rowconfigure(0, weight=1)
        database_frame.grid_columnconfigure(0, weight=1)
        database_frame.pack(expand=True, fill=BOTH, pady=10)
        
        for i in range(100):
            self.student_data.add_student(str(100 - i), i)
            self.database_treeview.insert('', END, values=(100 - i, i))
        
    def on_addButton_pressed(self):
        if self.input_valid(): 
            student_name = self.nameVar.get()
            student_grade = self.gradeVar.get()
            self.student_data.add_student(student_name, student_grade)
            self.database_treeview.insert('', END, values=(student_name, student_grade))
            self.nameVar.set("")
            self.gradeVar.set("")
            
    def on_searchButton_pressed(self):
        if not self.nameVar.get():
            messagebox.showerror(title="錯誤訊息", message="請輸入學生姓名")
            return
        student_info = self.student_data.search_student(self.nameVar.get())
        if student_info:
            messagebox.showinfo(title="搜尋結果", message=f"{student_info.name} 的成績為 {student_info.grade}")            
        else: 
            messagebox.showwarning(title="搜尋結果", message=f"找不到學生{self.nameVar.get()}")
            
        # students = self.database_treeview.get_children()
        # found = False
        # for student in students:
        #     values = self.database_treeview.item(student)['values']
        #     if str(values[0]) == student_name:
        #         messagebox.showinfo(title="搜尋結果", message=f"{values[0]} 的成績為 {values[1]}")
        #         found = True
        #         self.database_treeview.selection_set(student)
        #         self.database_treeview.see(student)
        #         break
        # if not found: 
        #     messagebox.showwarning(title="搜尋結果", message=f"找不到學生{student_name}")
        
    def on_delButton_pressed(self):
        selected_students = self.database_treeview.selection()
        if not selected_students: 
            messagebox.showerror(title="刪除結果", message="無選擇中的學生!")
        for student in selected_students:
            values = self.database_treeview.item(student)['values']
            self.student_data.delete_student(str(values[0]))
            # result = self.student_data.delete_student(str(values[0]))
            # print("successfully delete student" if result else "fail to delete student")
            self.database_treeview.delete(student)

    def sort_students(self):
        sorted_students = self.student_data.sort_students(
            self.sort_reference.get(), 
            self.sort_ascending.get()
        )
        self.database_treeview.delete(*self.database_treeview.get_children())
        for student in sorted_students:
            self.database_treeview.insert('', END, values=(student.name, student.grade))        
        # students = self.database_treeview.get_children()
        # students_with_values = [(self.database_treeview.item(item, "values"), item) for item in students]
        # if self.sort_reference.get() == SortType.GRADE.value:
        #     sorted_students = sorted(students_with_values, key=lambda x: int(x[0][1]), reverse=self.sort_ascending.get())
        # elif self.sort_reference.get() == SortType.NAME.value:
        #     sorted_students = sorted(students_with_values, key=lambda x: x[0][0], reverse=self.sort_ascending.get())
        # for i, (values, item) in enumerate(sorted_students):
        #     self.database_treeview.move(item, '', i)

    def on_updateButton_pressed(self):
        print("update_button_pressed")
        pass
    
    def input_valid(self): 
        student_name = self.nameVar.get()
        student_grade = self.gradeVar.get()
        if not student_name and not student_grade:         
            messagebox.showerror(title="錯誤訊息", message="請輸入學生資訊!")
            return False  
        elif not student_grade: 
            messagebox.showerror(title="錯誤訊息", message="請輸入學生成績!")    
            return False
        elif not student_name: 
            messagebox.showerror(title="錯誤訊息", message="請輸入學生姓名!")    
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
    
# 將資料分離出來