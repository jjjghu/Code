from tkinter import *
from tkinter import messagebox
import sys
import os

# Import both game versions
from MineSweeper import MineSweeper
from MineSweeper_Multiplayer import MineSweeperMultiplayer

class GameLauncher:
    def __init__(self, root):
        self.root = root
        self.root.title("踩地雷遊戲啟動器")
        self.root.geometry("400x300")
        self.root.resizable(False, False)
        
        # Center the window
        self.center_window()
        
        # Create UI
        self.create_widgets()
    
    def center_window(self):
        """Center the window on screen"""
        self.root.update_idletasks()
        width = self.root.winfo_width()
        height = self.root.winfo_height()
        x = (self.root.winfo_screenwidth() - width) // 2
        y = (self.root.winfo_screenheight() - height) // 2
        self.root.geometry(f"{width}x{height}+{x}+{y}")
    
    def create_widgets(self):
        """Create launcher UI"""
        # Title
        title_label = Label(self.root, text="踩地雷遊戲", font=("Arial", 24, "bold"))
        title_label.pack(pady=20)
        
        # Description
        desc_label = Label(self.root, text="請選擇遊戲模式", font=("Arial", 14))
        desc_label.pack(pady=10)
        
        # Buttons frame
        button_frame = Frame(self.root)
        button_frame.pack(pady=20)
        
        # Single player button
        single_button = Button(
            button_frame, 
            text="單人遊戲", 
            font=("Arial", 12),
            width=15,
            height=2,
            command=self.launch_single_player
        )
        single_button.pack(pady=10)
        
        # Multiplayer button
        multi_button = Button(
            button_frame, 
            text="雙人對戰", 
            font=("Arial", 12),
            width=15,
            height=2,
            command=self.launch_multiplayer
        )
        multi_button.pack(pady=10)
        
        # Exit button
        exit_button = Button(
            self.root, 
            text="退出", 
            font=("Arial", 10),
            width=10,
            command=self.root.destroy
        )
        exit_button.pack(side=BOTTOM, pady=10)
    
    def launch_single_player(self):
        """Launch single player game"""
        self.root.destroy()
        new_window = Tk()
        game = MineSweeper(new_window)
        game.start()
    
    def launch_multiplayer(self):
        """Launch multiplayer game"""
        self.root.destroy()
        new_window = Tk()
        game = MineSweeperMultiplayer(new_window)
        game.start()

if __name__ == "__main__":
    root = Tk()
    app = GameLauncher(root)
    root.mainloop()
