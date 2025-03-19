from tkinter import *
class Flags:
    def __init__(self):
        self.window = Tk()
        self.var = StringVar()
        self.var.set("The Selected Country")
        self.create_widget()

    def start(self):
        self.window.mainloop()
        
    def create_widget(self):
        
        self.label = Label(self.window, text="The Selected Country", bg="lightyellow", fg = "blue", width=30)
        self.label.pack()

        self.images = [] # 需要保持引用，避免被垃圾處理機制消除
        imagePaths = [("Images/Tile1.png", 1), ("Images/Tile2.png", 2), ("Images/Tile3.png", 3), ("Images/Tile4.png", 4), ("Images/Tile5.png", 5)]
        for (path, name) in imagePaths:
            image = PhotoImage(file=path)
            self.images.append(image)
            radioButton = Radiobutton(self.window, text=name, variable=self.var, value=name, image=image, indicatoron=0, command=self.printSelection)
            radioButton.pack()

    def printSelection(self):
        self.label.config(text=self.var.get())
if __name__ == "__main__":
    flags = Flags()
    flags.start()