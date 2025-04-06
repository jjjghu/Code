from tkinter import *
import tkinter.messagebox as messagebox
from tkinter.ttk import Button, Radiobutton, Checkbutton, Entry # 只是為了好看, 可去掉
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
    
    def delete_student(self, name:str ) -> bool : 
        for student in self.students:
            if student.name == name and student.is_deleted == False:
                student.is_deleted = True
                return True
        return False

    def search_student(self, name:str) -> StudentInfo:
        for student in self.students:
            if student.name == name and not student.is_deleted:
                return student
        return None
    
    def get_all_students(self, show_deleted : bool = False):
        if not show_deleted:
            return [student for student in self.students if not student.is_deleted]
        else: 
            return [student for student in self.students if student.is_deleted]  

    def update_student(self, name:str, new_grade:int)->bool:
        student = self.search_student(name)
        if student:
            student.grade = new_grade
            return True
        return False
    
    def sort_students(self, sort_type:SortType, descending: bool, threshold:int, show_deleted : bool = False):
        students = self.get_all_students(show_deleted)
        students = [s for s in students if s.grade >= threshold]
        if sort_type == SortType.NAME.value:
            return sorted(students, key=lambda x: x.name, reverse=descending)
        elif sort_type == SortType.GRADE.value:
            return sorted(students, key=lambda x: x.grade, reverse=descending)

        
class Student():
    def __init__(self):
        self.window = Tk()
        self.window.title("Student Management System")
        self.window.geometry('')
        self.create_variable()
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
        
    def create_variable(self):
        self.student_data = StudentData()
        
        self.nameVar = StringVar()
        self.gradeVar = StringVar()
        
        self.gradeThresholdVar = IntVar()
        self.gradeThresholdVar.set(0)
        
        self.show_deleted = BooleanVar()
        self.show_deleted.set(False)
        
        self.sort_reference = StringVar()
        self.sort_reference.set(SortType.NAME.value)
        
        self.sort_descending = BooleanVar()
        self.sort_descending.set(False)
        
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
        Checkbutton(option_frame, text="降序", variable=self.sort_descending).grid(row = 0, column=0, padx=5) 
        Radiobutton(option_frame, text="依姓名排列", variable=self.sort_reference, value=SortType.NAME.value, command=self.update_listbox).grid(row=0, column=1, padx=5)
        Radiobutton(option_frame, text="依成績排列", variable=self.sort_reference, value=SortType.GRADE.value, command=self.update_listbox).grid(row=0, column=2, padx=5)
        Checkbutton(option_frame, text="顯示刪除資訊", variable=self.show_deleted, command=self.update_listbox).grid(row=0, column=3, padx=5)
        option_frame.pack(pady=10)
        
        # listbox layout
        database_frame = Frame(self.window)
        
        header_frame = Frame(database_frame)
        name_header = Label(header_frame, text="姓名", width=19, relief=GROOVE, font=("Courier New", 12))
        grade_header = Label(header_frame, text="成績", width=19, relief=GROOVE, font=("Courier New", 12))

        name_header.pack(side=LEFT, padx=(0, 1))
        grade_header.pack(side=LEFT)
        
        y_scrollbar = Scrollbar(database_frame, orient=VERTICAL)
        x_scrollbar = Scrollbar(database_frame, orient=HORIZONTAL)

        self.listbox = Listbox(
            database_frame,
            width=40,
            font=("Courier New", 12),
            yscrollcommand=y_scrollbar.set,
            xscrollcommand=x_scrollbar.set
        )


        y_scrollbar.pack(side=RIGHT, fill=Y)
        x_scrollbar.pack(side=BOTTOM, fill=X)
        
        y_scrollbar.config(command=self.listbox.yview)
        x_scrollbar.config(command=self.listbox.xview)
        
        header_frame.pack(fill=X)
        self.listbox.pack(side=LEFT, expand=True, fill=BOTH)
        database_frame.pack(expand=True, fill=BOTH, pady=10)
        
        # 測試資料
        for i in range(100):
            name = str(100 - i)
            grade = i
            self.student_data.add_student(name, grade)
            display_text = f"{name:^19}-{grade:^19}"
            self.listbox.insert(END, display_text)
            
        # Scale
        Scale(
            self.window, 
            from_=0, 
            to_=100,
            troughcolor="gray", 
            tickinterval=50, 
            orient=HORIZONTAL,
            variable=self.gradeThresholdVar,
            command= self.on_scale_changed
        ).pack(fill=X)
        
    def on_addButton_pressed(self):
        if self.input_valid(): 
            student_name = self.nameVar.get()
            student_grade = self.gradeVar.get()
            if self.student_data.search_student(student_name) is None: 
                self.student_data.add_student(student_name, student_grade)
                self.update_listbox()
            else: 
                messagebox.showwarning(title="錯誤訊息", message=f"學生 {student_name} 已存在!")
            
    def on_searchButton_pressed(self):
        name = self.nameVar.get()
        if not name:
            messagebox.showerror(title="錯誤訊息", message="請輸入學生姓名")
            return
        
        student_info = self.student_data.search_student(name)
        if student_info:
            messagebox.showinfo(title="搜尋結果", message=f"{student_info.name} 的成績為 {student_info.grade}")           
        else: 
            messagebox.showwarning(title="搜尋結果", message=f"找不到學生 {name}")
        self.update_listbox()
    def on_delButton_pressed(self):
        name = self.nameVar.get()
        if not name:
            messagebox.showerror(title="錯誤訊息", message="請輸入學生姓名")
            return
        
        if self.student_data.delete_student(name):
            messagebox.showinfo(title="刪除結果", message=f"已經將學生 {name} 資料刪除")
            self.update_listbox()          
        else: 
            messagebox.showwarning(title="刪除結果", message=f"找不到學生 {name}")
        
            
    def on_updateButton_pressed(self):
        if self.input_valid():    
            name = self.nameVar.get()
            new_grade = int(self.gradeVar.get())
            if self.student_data.update_student(name, new_grade):
                messagebox.showinfo(title="更新結果", message=f"學生 {name} 的成績已更新為 {new_grade}")
                self.update_listbox()
                self.nameVar.set("")
                self.gradeVar.set("")
            else:
                messagebox.showwarning(title="更新結果", message=f"找不到學生 {name}")  
    def on_scale_changed(self, event):
        self.update_listbox()
        
    def update_listbox(self):
        sorted_students = self.student_data.sort_students(
            self.sort_reference.get(),
            self.sort_descending.get(),
            self.gradeThresholdVar.get(),
            self.show_deleted.get()
        )
        
        self.listbox.delete(0, END)  # 清空 listbox
        
        for student in sorted_students:
            # 使用格式化字串
            display_text = f"{student.name:^19}-{student.grade:^19}"
            self.listbox.insert(END, display_text)       
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
    
# 使用 treeview 
# 將資料分離出來
