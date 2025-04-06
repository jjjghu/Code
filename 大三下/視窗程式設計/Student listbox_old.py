from tkinter import *
from tkinter.filedialog import askopenfilename, asksaveasfilename
import tkinter.messagebox as messagebox
from tkinter.ttk import Button, Radiobutton, Checkbutton, Label, Entry # 只是為了好看
from tkinter.ttk import Treeview # 唯一用到的課外東西, 可使用 Listbox 替代 (如果嚴格要求不能用課外的話)
import subprocess
import csv

# 讓程式碼好看些
from enum import Enum
from dataclasses import dataclass
from typing import List

from numpy import tile
    
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

    def load_data(self, file_path: str) -> bool:
        try:
            with open(file_path, mode='r', newline='', encoding='utf-8') as file:
                reader = csv.reader(file)
                for row in reader:
                    if row:
                        name, grade = row
                        self.add_student(name, int(grade))
            return True
        except FileNotFoundError:
            print(f"檔案 {file_path} 不存在，無法載入資料。")
            return False
    def save_data(self, file_path : str) -> bool:
        try:
            with open(file_path, mode='w', newline='', encoding='utf-8') as file:
                writer = csv.writer(file)
                for student in self.students:
                    if not student.is_deleted:
                        writer.writerow([student.name, student.grade])
            
            messagebox.showinfo(title="存檔成功", message=f"資料已成功儲存至 {file_path}")
            return True
        except Exception as e:
            messagebox.showerror(title="存檔失敗", message=f"儲存資料時發生錯誤: {e}")
            return False
        
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
        self.window.title("Studnet Management System")
        self.window.geometry('')
        self.create_variable()
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
        
    def create_variable(self):
        self.student_data = StudentData()
        
        self.input_name_var = StringVar()
        self.input_grade_var = StringVar()
        
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
        
        # 加在 top_frame 裡
        top_frame = Frame(self.window)

        # input layout 
        input_frame = Frame(top_frame)
        Label(input_frame, text="姓名").grid(row=0, column=0, padx=(5, 5))
        Entry(input_frame, textvariable=self.input_name_var, width=30).grid(row=0,column=1)
        Label(input_frame, text="成績").grid(row=1, column=0, padx=(5, 5))
        Entry(input_frame, textvariable=self.input_grade_var, width=30).grid(row=1, column=1)    
        input_frame.grid(row=0, column=0)

        # 空白空間
        Label(top_frame).grid(row=0, column=1, sticky="ew")
        top_frame.columnconfigure(1, weight=1) 

        # file layout
        file_frame = Frame(top_frame)
        Button(file_frame, text="匯入", command=self.on_importButton_pressed).pack(fill=X, pady=(0, 5))
        Button(file_frame, text="匯出", command=self.on_exportButton_pressed).pack(fill=X)
        file_frame.grid(row=0, column=2, sticky="ne",padx=(0, 5))

        top_frame.pack(fill=X)

        
        # button layout 
        button_frame = Frame(self.window)
        Button(button_frame, text="新增", command=self.on_addButton_pressed).grid(row = 0, column=0, padx=5)
        Button(button_frame, text="搜尋", command=self.on_searchButton_pressed).grid(row = 0, column=1, padx=5)
        Button(button_frame, text="刪除", command=self.on_delButton_pressed).grid(row = 0, column=2, padx=5)
        Button(button_frame, text="更新", command=self.on_updateButton_pressed).grid(row=0, column=3, padx=5)
        button_frame.pack(pady=10)
        
        
        # option layout 
        option_frame = Frame(self.window)
        Checkbutton(option_frame, text="降序", variable=self.sort_descending, command=self.update_treeview).grid(row = 0, column=0, padx=5) 
        Radiobutton(option_frame, text="依姓名排列", variable=self.sort_reference, value=SortType.NAME.value, command=self.update_treeview).grid(row=0, column=1, padx=5)
        Radiobutton(option_frame, text="依成績排列", variable=self.sort_reference, value=SortType.GRADE.value, command=self.update_treeview).grid(row=0, column=2, padx=5)
        Checkbutton(option_frame, text="顯示刪除資訊", variable=self.show_deleted, command=self.update_treeview).grid(row=0, column=3, padx=5)
        option_frame.pack(pady=10)
        
        # Treeview layout
        database_frame = Frame(self.window)
        y_scrollbar = Scrollbar(database_frame, orient=VERTICAL)
        x_scrollbar = Scrollbar(database_frame, orient=HORIZONTAL)
    
        self.treeview = Treeview(
            database_frame, 
            column=("姓名", "成績"), 
            show="headings", 
            yscrollcommand=y_scrollbar.set, 
            xscrollcommand= x_scrollbar.set
        )
        self.treeview.heading("姓名", text="▲姓名", command=self.sort_by_name)
        self.treeview.heading("成績", text="成績", command=self.sort_by_grade)
        self.treeview.column("姓名",width=160, anchor=CENTER)
        self.treeview.column("成績",width=160, anchor=CENTER)
        
        self.treeview.bind("<Button-3>",self.on_heading_right_click)
        self.treeview.bind("<Double-1>",self.on_heading_double_click)
        
        y_scrollbar.pack(fill=Y, side=RIGHT)
        x_scrollbar.pack(fill=X, side=BOTTOM)    
        y_scrollbar.config(command=self.treeview.yview)
        x_scrollbar.config(command=self.treeview.xview)
        
        self.treeview.pack(expand=True, fill=BOTH)
        database_frame.pack(expand=True, fill=BOTH)
        
        # 測試資料
        for i in range(1000):
            self.student_data.add_student(str(1000 - i), i)
            self.treeview.insert('', END, values=(1000 - i, i))
            
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
        
    def on_importButton_pressed(self):
        file_path = askopenfilename(filetypes=[("CSV files", "*.csv")])
        if self.student_data.load_data(file_path): 
            self.update_treeview()
        
    def on_exportButton_pressed(self):
        file_path = asksaveasfilename(defaultextension=".csv", filetypes=[("CSV files", "*.csv")])
        self.student_data.save_data(file_path)

    def on_addButton_pressed(self):
        if self.input_valid(): 
            student_name = self.input_name_var.get()
            student_grade = int(self.input_grade_var.get())
            if self.student_data.search_student(student_name) is None: 
                self.student_data.add_student(student_name, student_grade)
                self.update_treeview()
            else: 
                messagebox.showwarning(title="錯誤訊息", message=f"學生 {student_name} 已存在!")
            
    def on_searchButton_pressed(self):
        name = self.input_name_var.get()
        if not name:
            messagebox.showerror(title="錯誤訊息", message="請輸入學生姓名")
            return
        
        student_info = self.student_data.search_student(name)
        if student_info:
            messagebox.showinfo(title="搜尋結果", message=f"{student_info.name} 的成績為 {student_info.grade}")           
        else: 
            messagebox.showwarning(title="搜尋結果", message=f"找不到學生 {name}")
        self.update_treeview()
        
    def on_delButton_pressed(self):
        name = self.input_name_var.get()
        if not name:
            messagebox.showerror(title="錯誤訊息", message="請輸入學生姓名")
            return
        
        if self.student_data.delete_student(name):
            messagebox.showinfo(title="刪除結果", message=f"已經將學生 {name} 資料刪除")
            self.update_treeview()          
        else: 
            messagebox.showwarning(title="刪除結果", message=f"找不到學生 {name}")
        
    def on_updateButton_pressed(self):
        if self.input_valid():    
            name = self.input_name_var.get()
            new_grade = int(self.input_grade_var.get())
            if self.student_data.update_student(name, new_grade):
                messagebox.showinfo(title="更新結果", message=f"學生 {name} 的成績已更新為 {new_grade}")
                self.update_treeview()
                self.input_name_var.set("")
                self.input_grade_var.set("")
            else:
                messagebox.showwarning(title="更新結果", message=f"找不到學生 {name}")  
    def on_scale_changed(self, event):
        self.update_treeview()
    
    def on_heading_right_click(self, event):
        column = self.treeview.identify_column(event.x)
        if column == "#1": 
            self.sort_reference.set(SortType.NAME.value)
            self.reverse_sort_descending()
            self.update_treeview()
        elif column == "#2": 
            self.sort_reference.set(SortType.GRADE.value)
            self.reverse_sort_descending()
            self.update_treeview()
            
    def on_heading_double_click(self, event):
        selected_student = self.treeview.identify_row(event.y)
        if selected_student: 
            student_info = self.treeview.item(selected_student)["values"]
            name = student_info[0]
            grade = student_info[1]
            self.input_name_var.set(name)
            self.input_grade_var.set(grade)
            
    def sort_by_name(self):
        self.sort_reference.set(SortType.NAME.value)
        self.update_treeview()
        
    def sort_by_grade(self):
        self.sort_reference.set(SortType.GRADE.value)
        self.update_treeview()
        
    def update_treeview(self):
        sorted_students = self.student_data.sort_students(
            self.sort_reference.get(), 
            self.sort_descending.get(),
            self.gradeThresholdVar.get(),
            self.show_deleted.get()
        )
        
        self.treeview.delete(*self.treeview.get_children())
        for student in sorted_students:
            self.treeview.insert('', END, values=(student.name, student.grade))

        icon = "▼" if self.sort_descending.get() == True else "▲"
        if self.sort_reference.get() == SortType.GRADE.value: 
            self.treeview.heading("姓名", text=f"姓名")
            self.treeview.heading("成績", text=f"{icon}成績")
        elif self.sort_reference.get() == SortType.NAME.value:
            self.treeview.heading("姓名", text=f"{icon}姓名")
            self.treeview.heading("成績", text=f"成績")
                    
    def reverse_sort_descending(self):
        self.sort_descending.set(not self.sort_descending.get())
        # ▼▲
        
    def input_valid(self): 
        student_name = self.input_name_var.get()
        student_grade = self.input_grade_var.get()
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
# 加入資料導入功能
# 加入圖標
# 效能問題暫不考慮