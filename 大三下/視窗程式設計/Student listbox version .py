from tkinter import *
import tkinter.messagebox as messagebox

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
        self.sort_ascending = True
        self.student_list = []
        
    def create_widget(self):
        self.window.config(padx=20, pady=20)

        input_frame = Frame(self.window)
        Label(input_frame, text="姓名").grid(row=0, column=0, padx=(0, 5))
        Entry(input_frame, textvariable=self.nameVar, width=20).grid(row=0, column=1)
        Label(input_frame, text="成績").grid(row=1, column=0, padx=(0, 5))
        Entry(input_frame, textvariable=self.gradeVar, width=20).grid(row=1, column=1)    
        input_frame.pack()

        button_frame = Frame(self.window)
        Button(button_frame, text="新增", command=self.on_addButton_pressed).grid(row = 0, column=0, padx=5)
        Button(button_frame, text="搜尋", command=self.on_searchButton_pressed).grid(row = 0, column=1, padx=5)
        Button(button_frame, text="刪除", command=self.on_delButton_pressed).grid(row = 0, column=2, padx=5)
        sortButton = Button(button_frame, text="排序", command=self.on_sortButton_pressed, bitmap="hourglass", compound=LEFT)
        sortButton.bind("<Button-3>", self.on_sortButton_rightClick)
        sortButton.grid(row=0,column=4,padx=5)
        button_frame.pack(pady=10)

        database_frame = Frame(self.window)
        header_frame = Frame(database_frame)
        name_header = Label(header_frame, text="姓名", width=19, relief=GROOVE)
        name_header.pack(side=LEFT, padx=(0, 1))
        grade_header = Label(header_frame, text="成績", width=19, relief=GROOVE)
        grade_header.pack(side=LEFT)
        
        # name_header.bind("<Button-1>", lambda e: self.sort_by_name())
        # grade_header.bind("<Button-1>", lambda e: self.sort_by_grade())
        header_frame.pack(fill=X, padx=5)
        
        self.database_listbox = Listbox(database_frame, width=40, height=10, justify=CENTER)
        self.database_listbox.pack(fill=X, padx=5)

        for i in range(10):
            name = str(10 - i)
            grade = str(10 - i)
            self.student_list.append((name, grade))
            self.database_listbox.insert(END, f"{name:^19}-{grade:^19}")
        database_frame.pack()

    def on_addButton_pressed(self):
        if self.input_valid(): 
            student_name = self.nameVar.get()
            student_grade = self.gradeVar.get()
            self.student_list.append((student_name, student_grade))
            self.database_listbox.insert(END, f"{student_name:^19}-{student_grade:^19}")
            self.nameVar.set("")
            self.gradeVar.set("")
            
    def on_searchButton_pressed(self):
        student_name : str = self.nameVar.get()
        if not student_name:
            messagebox.showerror(title="錯誤訊息", message="請輸入學生姓名")
            return
        found = False
        for idx, (name, grade) in enumerate(self.student_list):
            if name == student_name:
                messagebox.showinfo(title="搜尋結果", message=f"學生{name}的成績為{grade}")
                self.database_listbox.selection_clear(0, END)
                self.database_listbox.selection_set(idx)
                self.database_listbox.see(idx)
                found = True
                break
        if not found: 
            messagebox.showinfo(title="搜尋結果", message=f"找不到學生{student_name}")
        
    def on_delButton_pressed(self):
        selected_indices = self.database_listbox.curselection()
        if not selected_indices:
            messagebox.showinfo(title="刪除訊息", message="並沒有選擇選項")
            return
        for index in reversed(selected_indices):
            self.database_listbox.delete(index)
            del self.student_list[index]

    def on_sortButton_pressed(self):
        self.student_list.sort(key=lambda x: int(x[1]), reverse=self.sort_ascending)
        self.update_listbox()

    def on_sortButton_rightClick(self, event):
        self.sort_ascending = not self.sort_ascending
        print(f"sort ascending: {self.sort_ascending}")

    def update_listbox(self):
        self.database_listbox.delete(0, END)
        for name, grade in self.student_list:
            self.database_listbox.insert(END, f"{name:^19}-{grade:^19}")

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
