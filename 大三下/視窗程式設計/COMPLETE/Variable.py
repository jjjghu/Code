import tkinter as tk
from tkinter import *
class Variable: 
    def __init__(self):
        # variable
        self.msg_on = False
        # window
        self.window = Tk()
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
if __name__ == "__main__":
    variable = Variable()
    variable.start()