from tkinter import *
from tkinter.filedialog import askopenfilename, asksaveasfilename
from tkinter.ttk import Button, Radiobutton, Checkbutton, Entry # 只是為了好看, 可去掉
from enum import Enum
from dataclasses import dataclass
from typing import List
import tkinter.messagebox as messagebox
import subprocess
import csv

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
        self.students = []
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
        self.window.title("Student Management System")
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
        Label(input_frame, text="姓名:").grid(row=0, column=0, padx=(5, 5))
        Entry(input_frame, textvariable=self.input_name_var, width=30).grid(row=0,column=1)
        Label(input_frame, text="成績:").grid(row=1, column=0, padx=(5, 5))
        Entry(input_frame, textvariable=self.input_grade_var, width=30).grid(row=1, column=1)    
        input_frame.grid(row=0, column=0)

        # 空白空間
        Label(top_frame).grid(row=0, column=1, sticky="ew")
        top_frame.columnconfigure(1, weight=1) 

        # file layout
        file_frame = Frame(top_frame)
        Button(file_frame, text="匯入csv", command=self.on_importButton_pressed).pack(fill=X, pady=(0, 5))
        Button(file_frame, text="匯出csv", command=self.on_exportButton_pressed).pack(fill=X)
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
        Checkbutton(option_frame, text="降序", variable=self.sort_descending, command=self.update_listbox).grid(row = 0, column=0, padx=5) 
        Radiobutton(option_frame, text="依姓名排列", variable=self.sort_reference, value=SortType.NAME.value, command=self.update_listbox).grid(row=0, column=1, padx=5)
        Radiobutton(option_frame, text="依成績排列", variable=self.sort_reference, value=SortType.GRADE.value, command=self.update_listbox).grid(row=0, column=2, padx=5)
        Checkbutton(option_frame, text="顯示刪除資訊", variable=self.show_deleted, command=self.update_listbox).grid(row=0, column=3, padx=5)
        option_frame.pack(pady=10)
        
        # listbox layout
        database_frame = Frame(self.window)
        
        header_frame = Frame(database_frame)
        self.name_header = Label(header_frame, text="▲姓名", width=20, relief=GROOVE)
        self.grade_header = Label(header_frame, text="成績", width=20, relief=GROOVE)
        # left click header
        self.name_header.bind("<Button-1>", lambda e, sortType=SortType.NAME.value, is_right_click=False: self.on_header_click(e, sortType, is_right_click))
        self.grade_header.bind("<Button-1>", lambda e, sortType=SortType.GRADE.value, is_right_click=False: self.on_header_click(e, sortType, is_right_click))
        # right click header
        self.name_header.bind("<Button-3>", lambda e, sortType=SortType.NAME.value, is_right_click=True: self.on_header_click(e, sortType, is_right_click))
        self.grade_header.bind("<Button-3>", lambda e, sortType=SortType.GRADE.value, is_right_click=True: self.on_header_click(e, sortType, is_right_click))

        self.name_header.pack(side=LEFT, padx=(0, 1))
        self.grade_header.pack(side=LEFT)
        header_frame.pack(fill=X)
        
        y_scrollbar = Scrollbar(database_frame, orient=VERTICAL)
        x_scrollbar = Scrollbar(database_frame, orient=HORIZONTAL)

        self.listbox = Listbox(
            database_frame,
            width=40,
            yscrollcommand=y_scrollbar.set,
            xscrollcommand=x_scrollbar.set,
            activestyle='none'
        )
        self.listbox.bind("<Double-1>", self.on_item_double_click)

        y_scrollbar.pack(side=RIGHT, fill=Y)
        x_scrollbar.pack(side=BOTTOM, fill=X)
        
        y_scrollbar.config(command=self.listbox.yview)
        x_scrollbar.config(command=self.listbox.xview)
        
        self.listbox.pack(side=LEFT, expand=True, fill=BOTH)
        database_frame.pack(expand=True, fill=BOTH, pady=0)
        
        # 測試資料
        for i in range(100):
            name = str(100 - i)
            grade = i
            self.student_data.add_student(name, grade)
            display_text = f"{name:^19}-{grade:^19}"
            self.listbox.insert(END, display_text)
            
        # Scale
        label_frame = LabelFrame(self.window, text="分數拉桿")
        Scale(
            label_frame, 
            from_=0, 
            to_=100,
            troughcolor="gray", 
            tickinterval=50, 
            orient=HORIZONTAL,
            variable=self.gradeThresholdVar,
            command= self.on_scale_changed,
        ).pack(fill=X)
        label_frame.pack(fill=X)
        
    def on_importButton_pressed(self):
        file_path = askopenfilename(filetypes=[("CSV files", "*.csv")])
        if self.student_data.load_data(file_path): 
            self.update_listbox()
        
    def on_exportButton_pressed(self):
        file_path = asksaveasfilename(defaultextension=".csv", filetypes=[("CSV files", "*.csv")])
        self.student_data.save_data(file_path)
        
    def on_addButton_pressed(self):
        if self.input_valid(): 
            student_name = self.input_name_var.get()
            student_grade = int(self.input_grade_var.get())
            if self.student_data.search_student(student_name) is None: 
                self.student_data.add_student(student_name, student_grade)
                self.update_listbox()
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
        self.update_listbox()
        
    def on_delButton_pressed(self):
        name = self.input_name_var.get()
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
            name = self.input_name_var.get()
            new_grade = int(self.input_grade_var.get())
            if self.student_data.update_student(name, new_grade):
                messagebox.showinfo(title="更新結果", message=f"學生 {name} 的成績已更新為 {new_grade}")
                self.update_listbox()
                self.input_name_var.set("")
                self.input_grade_var.set("")
            else:
                messagebox.showwarning(title="更新結果", message=f"找不到學生 {name}")  
                
    def on_scale_changed(self, event):
        self.update_listbox()

    def on_header_click(self, event, sortType:SortType, is_right_click:bool):
        if sortType == SortType.NAME.value:    
            self.sort_reference.set(SortType.NAME.value)
            if is_right_click: 
                self.reverse_sort_descending()
            self.update_listbox()
        elif sortType == SortType.GRADE.value: 
            self.sort_reference.set(SortType.GRADE.value)
            if is_right_click:
                self.reverse_sort_descending()
            self.update_listbox()
            
    def on_item_double_click(self, event):
        selection = self.listbox.curselection()
        if selection:
            item_text = self.listbox.get(selection[0])
            name,grade = item_text.split("-")
            name = name.strip()
            grade = grade.strip()
            self.input_name_var.set(name)
            self.input_grade_var.set(grade)

    def on_sortbyName_pressed(self):
        self.sort_reference.set(SortType.NAME.value)
        self.update_listbox()

    def on_sortbyGrade_pressed(self):
        self.sort_reference.set(SortType.GRADE.value)
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
            
        icon = "▼" if self.sort_descending.get() == True else "▲"
        if self.sort_reference.get() == SortType.GRADE.value: 
            self.name_header.config(text=f"姓名")
            self.grade_header.config(text=f"{icon}成績")
        elif self.sort_reference.get() == SortType.NAME.value:
            self.name_header.config(text=f"{icon}姓名")
            self.grade_header.config(text=f"成績")
            
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
    
# 使用 listbox
# 將資料分離出來
