import tkinter 
from tkinter import *
from PIL import Image, ImageTk

def GetGemometryMiddleSetting(mainTk : Tk, width, height):
    screenWidth = mainTk.winfo_screenwidth()
    screenHeight = mainTk.winfo_screenheight()
    return "%dx%d+%d+%d"%(width, height, (screenWidth - width) / 2, (screenHeight - height) / 2); 
    
def countUp(label : Label):
    time = 0
    def update():
        nonlocal time
        label.config(text=str(time))
        time += 1
        label.after(1000, update)
    update()

def CreateTimer(mainTk : Tk): 
    label = Label(mainTk, 
                text="I Love Tkinter",
                background="black",
                foreground="white",
                cursor="hand2",
                height=20,
                width=100,
                wraplength=40,
                bitmap="hourglass",
                compound=LEFT)
    label.anchor("center")
    countUp(label)
    return label

def CreateColorTable(mainTk : Tk): 
    Colors = ["red", "orange", "yellow", "green", "blue", "purple"]
    r = 0
    for color in Colors:
        Label(mainTk, text=color, relief="groove", width=20).grid(row=r, column=0)
        Label(mainTk, bg=color,width=20).grid(row=r, column=1)
        r += 1
         
def CreateLoginDemo(mainTk : Tk, image : PhotoImage):
    # image = Image.open("B.jpg")
    # won = ImageTk.PhotoImage(image)
    
    logo = Label(mainTk, image = image, text = "標題", compound=BOTTOM)
    
    IDLabel = Label(mainTk, text="ID", bg="#C3C3C3")
    passwordLabel = Label(mainTk, text="Phone", bg="#C3C3C3")
    IDLabel.grid(row = 1, pady = 10, padx = 10, sticky=W+E)
    passwordLabel.grid(row = 2, pady = 10, padx = 10, sticky=W+E)
    
    logo.grid(row = 0, column = 0, columnspan=2, pady = 10, padx = 10)
    IDEntry = Entry(mainTk)
    passwordEntry = Entry(mainTk, show="*")
    
    IDEntry.grid(row = 1, column= 1, sticky=W+E)
    passwordEntry.grid(row = 2, column= 1, pady=10, sticky=W+E)
def init(mainTk : Tk):
    # 視窗標題, 大小, 顏色 
    mainTk.title("TEST")
    mainTk.geometry(GetGemometryMiddleSetting(mainTk, width=800, height=600))
    mainTk.configure(bg="#C3C3C3")    

def on_button_click(char):
    if char == "Clr":
        entry["text"] = ""
        return
    currentText = entry["text"]
    if(currentText == "Error"):
        entry["text"] = ""
    if char == '=':
        try:
            result = eval(entry.get())
            entry.set(result)
        except Exception:
            entry.set("Error")
    else:
        entry.set(entry.get() + char)

if __name__ == "__main__":      
    mainTk = Tk()
    init(mainTk)

    # entry = Entry(mainTk, text="", bg="yellow", font=("Arial", 20), width=20)
    # entry.grid(columnspan=4)
    # buttons = [
    #     ('7', 1, 0), ('8', 1, 1), ('9', 1, 2), ('+', 1, 3),
    #     ('4', 2, 0), ('5', 2, 1), ('6', 2, 2), ('-', 2, 3),
    #     ('1', 3, 0), ('2', 3, 1), ('3', 3, 2), ('*', 3, 3),
    #     ('0', 4, 0), ('.', 4, 1), ('=', 4, 2), ('Clr', 4, 3)
    # ]
    # for (text, row, column) in buttons:
    #     button = Button(mainTk, text=text, font=("Arial", 16), width=5, height=2)
    #     button.grid(row=row, column=column, command= lambda: on_button_click(text))
    # entry.pack()
    image = Image.open("B.jpg")
    image = ImageTk.PhotoImage(image)
    CreateLoginDemo(mainTk=mainTk,image=image)
    # CreateColorTable(mainTk=mainTk)
    # Create Caculator
    mainTk = mainloop()