import tkinter as tk
from tkinter import messagebox
import random

class Cell:
    def __init__(self, row, col):
        self.row      = row 
        self.col      = col     
        self.type     = "empty" # "empty", "mine", "number"
        self.number   = 0
        self.revealed = False
        self.flagged  = False
        self.exploded = False

class MinesweeperGame:
    def __init__(self, master, width=16, height=16, mine_count=32):
        self.master     = master
        self.width      = width
        self.height     = height
        self.mine_count = mine_count
        self.game_over  = False
        self.cells      = []
        self.buttons    = []
        self.frame      = tk.Frame(master)
        self.frame.pack()
        
        self.load_images()
        self.create_board()
        self.new_game()

    def load_images(self):
        self.tile_images = {}
        self.tile_images["Tile1"]       = tk.PhotoImage(file="Images/Tile1.png")
        self.tile_images["Tile2"]       = tk.PhotoImage(file="Images/Tile2.png")
        self.tile_images["Tile3"]       = tk.PhotoImage(file="Images/Tile3.png")
        self.tile_images["Tile4"]       = tk.PhotoImage(file="Images/Tile4.png")
        self.tile_images["Tile5"]       = tk.PhotoImage(file="Images/Tile5.png")
        self.tile_images["Tile6"]       = tk.PhotoImage(file="Images/Tile6.png")
        self.tile_images["Tile7"]       = tk.PhotoImage(file="Images/Tile7.png")
        self.tile_images["Tile8"]       = tk.PhotoImage(file="Images/Tile8.png")
        self.tile_images["TileEmpty"]   = tk.PhotoImage(file="Images/TileEmpty.png")
        self.tile_images["TileExploded"] = tk.PhotoImage(file="Images/TileExploded.png")
        self.tile_images["TileFlag"]    = tk.PhotoImage(file="Images/TileFlag.png")
        self.tile_images["TileUnknown"] = tk.PhotoImage(file="Images/TileUnknown.png")
        self.tile_images["TileMine"]        = tk.PhotoImage(file="Images/TileMine.png")

    def create_board(self):
        for r in range(self.height):
            row_buttons = []
            for c in range(self.width):
                btn = tk.Button(
                    self.frame,
                    image=self.tile_images["TileUnknown"],
                    relief="flat",
                    borderwidth=0,
                    highlightthickness=0,
                    command=lambda r=r, c=c: self.left_click(r, c)  # 左鍵點擊
                )
                btn.bind("<Button-3>", lambda event, r=r, c=c: self.right_click(r, c))  # 右鍵點擊
                btn.grid(row=r, column=c, padx=0, pady=0)
                row_buttons.append(btn)
            self.buttons.append(row_buttons)
        self.reset_button = tk.Button(self.master, text="重置遊戲", command=self.new_game)
        self.reset_button.pack(pady=10)

    def new_game(self):
        self.game_over = False
        self.cells = [[Cell(r, c) for c in range(self.width)] for r in range(self.height)]
        self.place_mines()
        self.calculate_numbers()
        self.update_board()

    def place_mines(self):
        count = 0
        while count < self.mine_count:
            r = random.randrange(self.height)
            c = random.randrange(self.width)
            if self.cells[r][c].type != "mine":
                self.cells[r][c].type = "mine"
                count += 1

    def calculate_numbers(self):
        for r in range(self.height):
            for c in range(self.width):
                cell = self.cells[r][c]
                if cell.type == "mine":
                    continue
                mine_count = 0
                for dr in [-1, 0, 1]:
                    for dc in [-1, 0, 1]:
                        nr = r + dr
                        nc = c + dc
                        if 0 <= nr < self.height and 0 <= nc < self.width:
                            if self.cells[nr][nc].type == "mine":
                                mine_count += 1
                if mine_count > 0:
                    cell.type   = "number"
                    cell.number = mine_count

    def left_click(self, r, c):
        if self.game_over:
            return
        cell = self.cells[r][c]
        if cell.revealed and cell.flagged:
            return
        if cell.type == "mine":
            cell.exploded = True
            cell.revealed = True
            self.game_over = True
            self.reveal_all_mines()
            messagebox.showinfo("遊戲結束", "你踩到地雷了！")
        elif cell.type == "number":
            cell.revealed = True
        elif cell.type == "empty":
            self.flood_fill(r, c)
        self.check_win_condition()
        self.update_board()

    def right_click(self, r, c):
        if self.game_over:
            return
        cell = self.cells[r][c]
        if cell.revealed:
            return
        cell.flagged = not cell.flagged
        self.update_board()

    def flood_fill(self, r, c):
        if not (0 <= r < self.height and 0 <= c < self.width):
            return
        cell = self.cells[r][c]
        if cell.revealed or cell.flagged:
            return
        cell.revealed = True
        if cell.type == "empty":
            for dr in [-1, 0, 1]:
                for dc in [-1, 0, 1]:
                    if dr == 0 and dc == 0:
                        continue
                    nr = r + dr
                    nc = c + dc
                    if 0 <= nr < self.height and 0 <= nc < self.width:
                        neighbor = self.cells[nr][nc]
                        if not neighbor.revealed and neighbor.type != "mine":
                            self.flood_fill(nr, nc)

    def reveal_all_mines(self):
        for r in range(self.height):
            for c in range(self.width):
                cell = self.cells[r][c]
                if cell.type == "mine":
                    cell.revealed = True

    def check_win_condition(self):
        for r in range(self.height):
            for c in range(self.width):
                cell = self.cells[r][c]
                if cell.type != "mine" and not cell.revealed:
                    return
        self.game_over = True
        messagebox.showinfo("恭喜", "你贏了！")

    def update_board(self):
        for r in range(self.height):
            for c in range(self.width):
                cell = self.cells[r][c]
                btn = self.buttons[r][c]
                if cell.revealed:
                    if cell.type == "mine":
                        if cell.exploded:
                            img = self.tile_images["TileExploded"]
                        else:
                            img = self.tile_images["TileMine"]
                    elif cell.type == "number":
                        key = "Tile" + str(cell.number)
                        img = self.tile_images.get(key, self.tile_images["TileEmpty"])
                    else:
                        img = self.tile_images["TileEmpty"]
                else:
                    if cell.flagged:
                        img = self.tile_images["TileFlag"]
                    else:
                        img = self.tile_images["TileUnknown"]
                btn.config(image=img)
                
if __name__ == "__main__":
    mainTk = tk.Tk()
    mainTk.title("踩地雷")
    game = MinesweeperGame(mainTk)
    mainTk.mainloop()
