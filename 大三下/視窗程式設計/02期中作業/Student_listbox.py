from tkinter import *
from tkinter.filedialog import askopenfilename, asksaveasfilename
from tkinter.font import BOLD
from tkinter.ttk import Button, Radiobutton, Checkbutton, Label, Entry, Style, Scrollbar # 只是為了好看, 可去掉
import tkinter.messagebox as messagebox
import MineSweeper 
import subprocess
import csv

# 讓程式碼好看些
from enum import Enum
from dataclasses import dataclass
from typing import List, Literal

class MessageHandler:
    def __init__(self):
        self.use_messagebox = BooleanVar(value=False)
        self.message_label = None
        self.create_style()
        
    def create_style(self):
        self.warningStyle = Style()
        self.warningStyle.configure(
            "Warning.TLabel",
            font=("Consolas", 10, BOLD),
            foreground="#D49B54"
        ) 

        self.infoStyle = Style()
        self.infoStyle.configure(
            "Info.TLabel",
            font=("Consolas", 10),
            foreground="#1F7D53"
        )

        self.errorStyle = Style()
        self.errorStyle.configure(
            "Error.TLabel",
            font=("Consolas", 10),
            foreground="#A62C2C"
        ) 
    def show_message(self, title:str, message:str, message_type:Literal["error", "warning", "info"] = "info"):
        if self.use_messagebox.get():
            if message_type == "error":
                messagebox.showerror(title=title, message=message)
            elif message_type == "warning":
                messagebox.showwarning(title=title, message=message)
            else:
                messagebox.showinfo(title=title, message=message)
        else:
            style_name = {
                "error": "Error.TLabel",
                "warning": "Warning.TLabel",
                "info": "Info.TLabel"
            }[message_type]

            self.message_label.config(
                text=f"[{title}] {message}",
                style=style_name
            )
class SortType(Enum):
    NAME = "name"
    GRADE = "grade"
    
@dataclass
class StudentInfo: 
    name: str
    grade: int
    is_deleted : bool = False

class StudentData:
    def __init__(self, handler : MessageHandler):
        self.students: List[StudentInfo] = []
        self.message_handler = handler
        
    def load_data(self, file_path: str) -> bool:
        try:
            with open(file_path, mode='r', newline='', encoding='utf-8') as file:
                reader = csv.reader(file)
                for row in reader:
                    if row:
                        name, grade = row
                        self.add_student(name, int(grade))
            self.message_handler.show_message(title="匯入成功", message=f"檔案 {file_path} 匯入成功!", message_type="info")
            return True
        except FileNotFoundError:
            self.message_handler.show_message(title="錯誤訊息", message=f"檔案 {file_path} 不存在，無法載入資料。", message_type="error")
            return False
        except ValueError: 
            self.message_handler.show_message(title="錯誤訊息", message=f"檔案 {file_path} 資料有誤，無法載入資料。", message_type="error")

    def save_data(self, file_path : str) -> bool:
        try:
            with open(file_path, mode='w', newline='', encoding='utf-8') as file:
                writer = csv.writer(file)
                for student in self.students:
                    if not student.is_deleted:
                        writer.writerow([student.name, student.grade])
            self.message_handler.show_message(title="存檔成功", message=f"資料已成功儲存至 {file_path}", message_type="info")
            return True
        except Exception as e:
            self.message_handler.show_message(title="存檔失敗", message=f"儲存資料時發生錯誤: {e}", message_type="error")
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
        self.create_protocolBinding()
        self.create_widget()
        
    def start(self):
        self.window.mainloop()
        
    def create_variable(self):
        self.message_handler = MessageHandler()
        self.student_data = StudentData(self.message_handler)
        
        self.input_name_var = StringVar()
        self.input_grade_var = StringVar()        
        
        self.gradeThresholdVar = IntVar(value=0)
        self.show_deleted = BooleanVar(value=False)
        
        self.sort_reference = StringVar(value=SortType.NAME.value)
        self.sort_descending = BooleanVar(value=False)
        
        self.minesweeper_process = None
    
    def create_protocolBinding(self):
        self.window.protocol("WM_DELETE_WINDOW", self.on_close)
        
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
        
        Button(file_frame, text="匯入csv", cursor="hand2", command=self.on_importButton_pressed).pack(fill=X, pady=(0, 5))
        Button(file_frame, text="匯出csv", cursor="hand2", command=self.on_exportButton_pressed).pack(fill=X)
        file_frame.grid(row=0, column=2, sticky="ne",padx=(0, 5))

        top_frame.pack(fill=X)

        # button layout 
        button_frame = Frame(self.window)
        Button(button_frame, text="新增", cursor="hand2", command=self.on_addButton_pressed).grid(row = 0, column=0, padx=5)
        Button(button_frame, text="搜尋", cursor="hand2", command=self.on_searchButton_pressed).grid(row = 0, column=1, padx=5)
        Button(button_frame, text="刪除", cursor="hand2", command=self.on_delButton_pressed).grid(row = 0, column=2, padx=5)
        updateButton = Button(button_frame, text="更新", cursor="hand2", command=self.on_updateButton_pressed)
        updateButton.grid(row=0, column=3, padx=5)
        updateButton.bind("<Double-2>", self.on_gameButton_pressed)
        button_frame.pack(pady=10)
        
        # option layout 
        option_frame = Frame(self.window)
        Checkbutton(option_frame, cursor="hand2", text="降序", variable=self.sort_descending, command=self.update_database).grid(row = 0, column=0, padx=5) 
        Radiobutton(option_frame, cursor="hand2", text="依姓名排列", variable=self.sort_reference, value=SortType.NAME.value, command=self.update_database).grid(row=0, column=1, padx=5)
        Radiobutton(option_frame, cursor="hand2", text="依成績排列", variable=self.sort_reference, value=SortType.GRADE.value, command=self.update_database).grid(row=0, column=2, padx=5)
        Checkbutton(option_frame, cursor="hand2", text="顯示刪除資訊", variable=self.show_deleted, command=self.update_database).grid(row=0, column=3, padx=5)
        option_frame.pack(pady=10)
        
        # listbox layout
        database_frame = Frame(self.window)
        
        header_frame = Frame(database_frame)
        self.name_header = Label(header_frame, cursor="hand2", text="▲姓名", width=20, relief=GROOVE)
        self.grade_header = Label(header_frame, cursor="hand2", text="成績", width=20, relief=GROOVE)
        # left click header
        self.name_header.bind("<Button-1>", lambda e, sortType=SortType.NAME.value, is_right_click=False: self.on_header_click(e, sortType, is_right_click))
        self.grade_header.bind("<Button-1>", lambda e, sortType=SortType.GRADE.value, is_right_click=False: self.on_header_click(e, sortType, is_right_click))
        # right click header
        self.name_header.bind("<Button-3>", lambda e, sortType=SortType.NAME.value, is_right_click=True: self.on_header_click(e, sortType, is_right_click))
        self.grade_header.bind("<Button-3>", lambda e, sortType=SortType.GRADE.value, is_right_click=True: self.on_header_click(e, sortType, is_right_click))

        self.name_header.pack(side=LEFT, padx=(0, 1))
        self.grade_header.pack(side=LEFT, padx=(0,1))
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
            cursor="hand2",
            tickinterval=50, 
            orient=HORIZONTAL,
            variable=self.gradeThresholdVar,
            command= self.on_scale_changed,
        ).pack(fill=X)
        label_frame.pack(fill=X)

        # 輸出訊息
        message_frame = LabelFrame(self.window, text="訊息控制")
        Checkbutton(
            message_frame, 
            text="使用對話框顯示訊息",
            cursor="hand2", 
            variable=self.message_handler.use_messagebox
        ).pack(side=TOP, fill=X, pady=(0,5))
        
        canvas = Canvas(message_frame, height=50)
        scrollbar = Scrollbar(message_frame, orient=HORIZONTAL, command=canvas.xview)
        canvas.config(xscrollcommand=scrollbar.set)

        scrollable_frame = Frame(canvas)

        self.message_handler.message_label = Label(
            scrollable_frame, 
            text="訊息將顯示在這裡...",
            justify=LEFT,
        )
        self.message_handler.message_label.pack(fill=BOTH, expand=True, pady=(0,5))
        canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")

        scrollbar.pack(side="bottom", fill="x")
        canvas.pack(side=LEFT, fill=X, expand=True)
        
        scrollable_frame.update_idletasks()
        bbox = canvas.bbox("all")
        if bbox:
            canvas.config(height=bbox[3] - bbox[1])
        canvas.config(scrollregion=bbox)        
        scrollable_frame.bind("<Configure>", lambda event: canvas.config(scrollregion=canvas.bbox("all")))
        message_frame.pack(fill=X, pady=10)
        
    def on_importButton_pressed(self):
        file_path = askopenfilename(filetypes=[("CSV files", "*.csv")])
        if self.student_data.load_data(file_path): 
            self.update_database()
        
    def on_exportButton_pressed(self):
        file_path = asksaveasfilename(defaultextension=".csv", filetypes=[("CSV files", "*.csv")])
        self.student_data.save_data(file_path)
        
    def on_addButton_pressed(self):
        if self.input_valid(): 
            student_name = self.input_name_var.get()
            student_grade = int(self.input_grade_var.get())
            if self.student_data.search_student(student_name) is None: 
                self.student_data.add_student(student_name, student_grade)
                self.update_database()
                self.message_handler.show_message(title="更新成功", message=f"成功新增學生 {student_name}, 成績 {student_grade}", message_type="info")
            else: 
                self.message_handler.show_message(title="錯誤訊息", message=f"學生 {student_name} 已存在!", message_type="warning")
                  
    def on_searchButton_pressed(self):
        name = self.input_name_var.get()
        if not name:
            self.message_handler.show_message(title="錯誤訊息", message="請輸入學生姓名", message_type="warning")
            return
        
        student_info = self.student_data.search_student(name)
        if student_info:
            self.message_handler.show_message(title="搜尋結果", message=f"{student_info.name} 的成績為 {student_info.grade}")           
        else:             
            self.message_handler.show_message(title="搜尋結果", message=f"找不到學生 {name}", message_type="warning")
        self.update_database()
        
    def on_delButton_pressed(self):
        name = self.input_name_var.get()
        if not name:
            self.message_handler.show_message(title="錯誤訊息", message="請輸入學生姓名", message_type="error")
            return
        
        if self.student_data.delete_student(name):
            self.message_handler.show_message(title="刪除結果", message=f"已經將學生 {name} 資料刪除", message_type="info")
            self.update_database()     
        else: 
            self.message_handler.show_message(title="刪除結果", message=f"找不到學生 {name}", message_type="warning")
            
    def on_updateButton_pressed(self):
        if self.input_valid():    
            name = self.input_name_var.get()
            new_grade = int(self.input_grade_var.get())
            if self.student_data.update_student(name, new_grade):
                self.message_handler.show_message(title="更新結果", message=f"學生 {name} 的成績已更新為 {new_grade}", message_type="info")
                self.update_database()
            else:
                self.message_handler.show_message(title="更新結果", message=f"找不到學生 {name}", message_type="warning")  
                
    def on_scale_changed(self, event):
        self.update_database()

    def on_header_click(self, event, sortType:SortType, is_right_click:bool):
        if sortType == SortType.NAME.value:    
            self.sort_reference.set(SortType.NAME.value)
            if is_right_click: 
                self.reverse_sort_descending()
            self.update_database()
        elif sortType == SortType.GRADE.value: 
            self.sort_reference.set(SortType.GRADE.value)
            if is_right_click:
                self.reverse_sort_descending()
            self.update_database()
            
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
        self.update_database()

    def on_sortbyGrade_pressed(self):
        self.sort_reference.set(SortType.GRADE.value)
        self.update_database()
    
    def on_gameButton_pressed(self, e):
        if self.minesweeper_process is None or self.minesweeper_process.poll() is not None:
            self.minesweeper_process = subprocess.Popen(["python", "minesweeper.py"])
            
    def on_close(self): 
        if self.minesweeper_process is not None: 
            self.minesweeper_process.terminate()
        self.window.destroy()
        
    def update_database(self):
        sorted_students = self.student_data.sort_students(
            self.sort_reference.get(),
            self.sort_descending.get(),
            self.gradeThresholdVar.get(),
            self.show_deleted.get()
        )
        
        self.listbox.delete(0, END)
        
        for student in sorted_students:
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
            self.message_handler.show_message(title="錯誤訊息", message="請輸入學生資訊!", message_type="error")
            return False  
        elif not student_grade: 
            self.message_handler.show_message(title="錯誤訊息", message="請輸入學生成績!", message_type="error") 
            return False
        elif not student_name: 
            self.message_handler.show_message(title="錯誤訊息", message="請輸入學生姓名!", message_type="error") 
            return False
        elif not student_grade.isdigit():
            self.message_handler.show_message(title="錯誤訊息", message="成績應為正整數!", message_type="error")
            return False
        elif int(student_grade) > 100 or int(student_grade) < 0:
            self.message_handler.show_message(title="錯誤訊息", message="成績應為0 ~ 100 之間的正整數!", message_type="error")
            return False
        return True
    
if __name__=="__main__":
    student = Student()
    student.start()
    
# 使用 listbox
# 將資料分離出來
