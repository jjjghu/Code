from tkinter import *
from tkinter import messagebox
import random
import os
from MineSweeper_Cell import CellType, Cell
from MineSweeper_Difficulty import DifficultyConfig, Difficulty
from MineSweeper_GameBoard import GameBoard
class MineSweeper:
    """初始化"""
    def __init__(self, window:Tk, difficulty: Difficulty=Difficulty.NORMAL):
        # 根據難度初始化遊戲場地
        self.config = DifficultyConfig(difficulty)
        self.gameBoard:GameBoard = GameBoard(
            self.config.board_width,
            self.config.board_height,
            self.config.mine_count
        )
        self.buttons: list[list[Button]] = []
                    
        self.window:Tk = window
        
        self.create_variable()
        self.load_images()
        self.create_widget()
        self.center_window()
        self.new_game()
    
    def start(self):
        """用 start 封裝 mainloop, 問就是這樣比較直觀"""
        self.window.mainloop()
        
    def load_images(self):
        """把圖片加載進來, 之後可透過環境變數簡化"""
        base_path = os.path.join(os.path.dirname(__file__), f"Images")
        self.tile_images = {}
        for i in range(1, 9):
            self.tile_images[f"Tile{i}"] = PhotoImage(file=os.path.join(base_path, f"Tile{i}.png"))
        self.tile_images["TileEmpty"]    = PhotoImage(file=os.path.join(base_path, "TileEmpty.png"))
        self.tile_images["TileExploded"] = PhotoImage(file=os.path.join(base_path, "TileExploded.png"))
        self.tile_images["TileFlag"]     = PhotoImage(file=os.path.join(base_path, "TileFlag.png"))
        self.tile_images["TileUnknown"]  = PhotoImage(file=os.path.join(base_path, "TileUnknown.png"))
        self.tile_images["TileMine"]     = PhotoImage(file=os.path.join(base_path, "TileMine.png"))

    def create_variable(self):
        """會用到的一些遊戲變數"""
        self.flagged_count:IntVar = IntVar(value=0)
        self.is_game_over:bool = False
        self.first_click:bool = True
        self.chord_holding:bool = False
        self.debug_mode:bool = False
        
    def create_widget(self):
        """創建你會看到的所有元素"""
        self.frame = Frame(self.window)
        self.frame.pack(padx=20, pady=20)
        self.board_frame = Frame(self.frame)
        self.board_frame.pack()
        for r in range(self.gameBoard.height):
            row_buttons = []
            for c in range(self.gameBoard.width):
                btn = Button(
                    self.board_frame,
                    image=self.tile_images["TileUnknown"],
                    relief="flat",
                    borderwidth=0,
                    highlightthickness=0,
                    command=lambda r=r, c=c: self.on_left_click(r, c)  # 左鍵點擊
                )
                btn.bind("<Button-3>", lambda event, r=r, c=c: self.on_right_click(r, c))  # 右鍵點擊
                btn.bind("<Button-1>", lambda event, r=r, c=c: self.on_chord_press(r, c)) # 左鍵點擊
                btn.bind("<ButtonRelease-1>", lambda event, r=r, c=c: self.on_chord_release(r, c)) # 左鍵放開
                btn.grid(row=r, column=c, padx=0, pady=0)
                row_buttons.append(btn)
            self.buttons.append(row_buttons)
        # 控制面板
        self.create_control_panel()
   
    def create_control_panel(self):
        """建立控制面板"""
        control_frame = Frame(self.frame)
        control_frame.pack(pady=5)
        
        # 難度按鈕
        difficulty_frame = Frame(control_frame)
        difficulty_frame.pack(side=TOP, pady=5)
        
        for diff in Difficulty: 
            Button(
                difficulty_frame,
                text=DifficultyConfig.CONFIGS[diff]["name"],
                command=lambda d=diff: self.change_difficulty(d)
            ).pack(side=LEFT, padx=5)
        
        self.reset_button = Button(control_frame, text="重置遊戲", command=self.new_game)
        self.reset_button.pack(side=LEFT, padx=5)
        
        self.debug_button = Button(control_frame, text="Debug 模式：關閉", command=self.toggle_debug_mode)
        self.debug_button.pack(side=LEFT, padx=5)

    def center_window(self):
        """讓視窗自適應大小, 然後置中"""
        self.window.update_idletasks()

        # 每個方塊的大小是 32 
        width = self.gameBoard.width * 32 + 40  # 左右各加 20 像素邊距
        height = self.gameBoard.height * 32 + 120  # 加入控制面板高度
        
        screen_width = self.window.winfo_screenwidth()
        screen_height = self.window.winfo_screenheight()
        x = (screen_width - width) // 2
        y = (screen_height - height) // 2
        self.window.geometry(f"{width}x{height}+{x}+{y}")
        
    def toggle_debug_mode(self):
        """作弊是一定要有的, 開發者很累的"""
        self.debug_mode = not self.debug_mode
        self.debug_button.config(text=f"Debug 模式：{'開啟' if self.debug_mode else '關閉'}")
        self.update_board()
        
    """遊戲邏輯"""
    def flood_fill(self, r, c):
        if not self.gameBoard.is_valid_position(r, c):
            return 
        cell = self.gameBoard.get_cell(r, c)
        if cell.revealed or cell.flagged:
            return
        cell.revealed = True
        if cell.is_empty():
            for dr in [-1, 0, 1]:
                for dc in [-1, 0, 1]:
                    if dr == 0 and dc == 0:
                        continue
                    nr = r + dr
                    nc = c + dc
                    if self.gameBoard.is_valid_position(nr, nc):
                        neighbor = self.gameBoard.get_cell(nr, nc)
                        if not neighbor.revealed and not neighbor.is_mine():
                            self.flood_fill(nr, nc)

    """遊戲狀態相關"""
    def new_game(self):
        """開始一場新遊戲"""
        self.is_game_over = False
        self.first_click = True
        self.gameBoard.reset()
        self.update_board()
        
    def game_over(self):
        """你爆炸了"""
        self.reveal_all_mines()
        messagebox.showinfo("遊戲結束", "你踩到地雷了！")
        
    def check_win_condition(self):
        """勝利唾手可得"""
        for r in range(self.gameBoard.height):
            for c in range(self.gameBoard.width):
                cell = self.gameBoard.get_cell(r, c)
                if not cell.is_mine() and not cell.revealed:
                    return
        self.is_game_over = True
        messagebox.showinfo("恭喜", "你贏了！")
    
    """滑鼠事件處理"""
    def on_left_click(self, r, c):
        """你按下了左鍵"""
        if self.is_game_over:
            return
        
        # 第一次按下的時候, 才擺放地雷
        if self.first_click:
            self.first_click = False
            self.gameBoard.place_mines(r, c)
            self.gameBoard.calculate_numbers()
            self.first_click = False

        # 旗標不會被展開
        cell = self.gameBoard.get_cell(r, c)
        if not cell.revealed and cell.flagged:
            return

        # 每次按下, 判斷是否為地雷
        if cell.is_mine():
            cell.exploded = True
            cell.revealed = True
            self.is_game_over = True
            self.game_over()
        elif cell.is_number():
            cell.revealed = True
        elif cell.is_empty():
            self.flood_fill(r, c)
        self.update_board()
        self.check_win_condition()

    def on_right_click(self, r, c):
        """你按下了右鍵插旗子"""
        # 遊戲已經結束, 你來太晚了
        if self.is_game_over:
            return
        
        # 你不能將旗子插在奇怪的位置
        cell = self.gameBoard.get_cell(r, c)
        if cell.revealed:
            return
        
        # 你插太多旗子了
        if self.flagged_count.get() >= self.gameBoard.mine_count: 
            return
        
        cell.flagged = not cell.flagged
        self.update_board()

    def on_chord_click(self, r, c):
        """你想要抄近路，玩的快一些"""
        if self.is_game_over:
            return
        
        # 只能在 revealed, 且為數字的時候觸發
        cell = self.gameBoard.get_cell(r, c)
        if not cell.revealed or not cell.is_number():
            return
        
        flag_count = self.gameBoard.count_flags_around(r, c)
        if flag_count != cell.number:
            return
        
        exploded = False
        for dr in [-1, 0, 1]:
            for dc in [-1, 0, 1]:
                if dr == 0 and dc == 0:
                    continue
                nr = r + dr
                nc = c + dc
                if self.gameBoard.is_valid_position(nr, nc):
                    neighbor = self.gameBoard.get_cell(nr, nc)
                    if not neighbor.flagged and not neighbor.revealed:
                        if neighbor.is_mine():
                            neighbor.exploded = True
                            neighbor.revealed = True
                            exploded = True
                        elif neighbor.is_number():
                            neighbor.revealed = True
                        else: # empty
                            self.flood_fill(nr, nc)
        if exploded:
            self.is_game_over = True
            self.game_over()
            
        self.update_board()
    
    def on_chord_press(self, r, c):
        """想要展開時的「預視」效果"""
        if self.is_game_over:
            return
        
        cell = self.gameBoard.get_cell(r, c)
        if not cell.revealed or not cell.is_number():
            return
            
        flag_count = self.gameBoard.count_flags_around(r, c)
        if flag_count != cell.number:
            return
            
        self.chord_holding = True
        # 臨時顯示周圍未標記格子的內容
        for dr in [-1, 0, 1]:
            for dc in [-1, 0, 1]:
                if dr == 0 and dc == 0:
                    continue
                nr = r + dr
                nc = c + dc
                if self.gameBoard.is_valid_position(nr, nc):
                    neighbor = self.gameBoard.get_cell(nr, nc)
                    if not neighbor.flagged and not neighbor.revealed:
                        btn = self.buttons[nr][nc]
                        btn.config(image=self.tile_images["TileEmpty"])

    def on_chord_release(self, r, c):
        """放開按鍵, 觸發 chord_click 的效果"""
        if not self.chord_holding:
            return
        self.chord_holding = False
        self.update_board()
        self.on_chord_click(r, c)
        
    """輔助方法"""
    def reveal_all_mines(self):
        for r in range(self.gameBoard.height):
            for c in range(self.gameBoard.width):
                cell = self.gameBoard.get_cell(r, c)
                if cell.is_mine():
                    cell.revealed = True
        self.update_board()

    def update_board(self):
        for r in range(self.gameBoard.height):
            for c in range(self.gameBoard.width):
                cell = self.gameBoard.get_cell(r, c)
                btn = self.buttons[r][c]
                
                if self.debug_mode and cell.is_mine() and not cell.revealed:
                    img = self.tile_images["TileMine"]
                elif cell.revealed:
                    if cell.is_mine():
                        if cell.exploded:
                            img = self.tile_images["TileExploded"]
                        else:
                            img = self.tile_images["TileMine"]
                    elif cell.is_number():
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

    def change_difficulty(self, difficulty):
        """切換難度"""
        self.config = DifficultyConfig(difficulty)
        self.gameBoard = GameBoard(
            self.config.board_width,
            self.config.board_height,
            self.config.mine_count
        )
        self.buttons:list[list[Button]] = []
        self.frame.destroy()
        self.create_widget()
        self.center_window()
        self.new_game()
        
# main
if __name__ == "__main__":
    window = Tk()
    window.title("踩地雷")
    game = MineSweeper(window)
    game.start()