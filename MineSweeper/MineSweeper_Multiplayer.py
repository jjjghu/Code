from tkinter import *
from tkinter import messagebox, simpledialog
import time
import threading
import socket
import os

from MineSweeper_Cell import CellType, Cell
from MineSweeper_Difficulty import DifficultyConfig, Difficulty
from MineSweeper_MultiplayerGameBoard import MultiplayerGameBoard
from MineSweeper_Network import NetworkManager, NetworkMessage

class MineSweeperMultiplayer:
    """Two-player competitive Minesweeper game"""
    def __init__(self, window: Tk, difficulty: Difficulty=Difficulty.NORMAL):
        # Initialize game configuration
        self.config = DifficultyConfig(difficulty)
        self.gameBoard = MultiplayerGameBoard(
            self.config.board_width,
            self.config.board_height,
            self.config.mine_count
        )
        
        # UI elements
        self.window = window
        self.player_buttons = []  # Left side (player)
        self.opponent_buttons = []  # Right side (opponent)
        
        # Game state variables
        self.is_host = False
        self.network = None
        self.connected = False
        self.game_started = False
        self.first_click = True
        self.opponent_first_click = True
        
        # Create UI and load resources
        self.create_variables()
        self.load_images()
        self.create_widgets()
        self.center_window()
        
        # Update timer every second
        self.update_timer()
    
    def start(self):
        """Start the game window"""
        self.window.mainloop()
    
    def create_variables(self):
        """Initialize game variables"""
        self.player_flagged_count = IntVar(value=0)
        self.opponent_flagged_count = IntVar(value=0)
        self.player_time = StringVar(value="00:00")
        self.opponent_time = StringVar(value="00:00")
        self.connection_status = StringVar(value="未連接")
        self.game_status = StringVar(value="等待開始")
        self.is_game_over = False
        self.chord_holding = False
        self.debug_mode = False
    
    def load_images(self):
        """Load tile images"""
        base_path = os.path.join(os.path.dirname(__file__), "Images")
        self.tile_images = {}
        for i in range(1, 9):
            self.tile_images[f"Tile{i}"] = PhotoImage(file=os.path.join(base_path, f"Tile{i}.png"))
        self.tile_images["TileEmpty"] = PhotoImage(file=os.path.join(base_path, "TileEmpty.png"))
        self.tile_images["TileExploded"] = PhotoImage(file=os.path.join(base_path, "TileExploded.png"))
        self.tile_images["TileFlag"] = PhotoImage(file=os.path.join(base_path, "TileFlag.png"))
        self.tile_images["TileUnknown"] = PhotoImage(file=os.path.join(base_path, "TileUnknown.png"))
        self.tile_images["TileMine"] = PhotoImage(file=os.path.join(base_path, "TileMine.png"))
    
    def create_widgets(self):
        """Create all UI elements"""
        # Main frame
        self.main_frame = Frame(self.window)
        self.main_frame.pack(padx=20, pady=20)
        
        # Game boards container (side by side)
        self.boards_frame = Frame(self.main_frame)
        self.boards_frame.pack(pady=10)
        
        # Player board (left side)
        self.player_frame = LabelFrame(self.boards_frame, text="你的遊戲", padx=5, pady=5)
        self.player_frame.pack(side=LEFT, padx=10)
        
        self.player_board_frame = Frame(self.player_frame)
        self.player_board_frame.pack()
        
        # Create player board buttons
        for r in range(self.gameBoard.height):
            row_buttons = []
            for c in range(self.gameBoard.width):
                btn = Button(
                    self.player_board_frame,
                    image=self.tile_images["TileUnknown"],
                    relief="flat",
                    borderwidth=0,
                    highlightthickness=0,
                    command=lambda r=r, c=c: self.on_left_click(r, c)
                )
                btn.bind("<Button-3>", lambda event, r=r, c=c: self.on_right_click(r, c))
                btn.bind("<Button-1>", lambda event, r=r, c=c: self.on_chord_press(r, c))
                btn.bind("<ButtonRelease-1>", lambda event, r=r, c=c: self.on_chord_release(r, c))
                btn.grid(row=r, column=c, padx=0, pady=0)
                row_buttons.append(btn)
            self.player_buttons.append(row_buttons)
        
        # Player info frame
        self.player_info_frame = Frame(self.player_frame)
        self.player_info_frame.pack(fill=X, pady=5)
        
        Label(self.player_info_frame, text="時間:").pack(side=LEFT)
        Label(self.player_info_frame, textvariable=self.player_time).pack(side=LEFT, padx=5)
        
        # Opponent board (right side)
        self.opponent_frame = LabelFrame(self.boards_frame, text="對手的遊戲", padx=5, pady=5)
        self.opponent_frame.pack(side=LEFT, padx=10)
        
        self.opponent_board_frame = Frame(self.opponent_frame)
        self.opponent_board_frame.pack()
        
        # Create opponent board buttons (display only, no interaction)
        for r in range(self.gameBoard.height):
            row_buttons = []
            for c in range(self.gameBoard.width):
                btn = Button(
                    self.opponent_board_frame,
                    image=self.tile_images["TileUnknown"],
                    relief="flat",
                    borderwidth=0,
                    highlightthickness=0,
                    state=DISABLED  # Opponent board is view-only
                )
                btn.grid(row=r, column=c, padx=0, pady=0)
                row_buttons.append(btn)
            self.opponent_buttons.append(row_buttons)
        
        # Opponent info frame
        self.opponent_info_frame = Frame(self.opponent_frame)
        self.opponent_info_frame.pack(fill=X, pady=5)
        
        Label(self.opponent_info_frame, text="時間:").pack(side=LEFT)
        Label(self.opponent_info_frame, textvariable=self.opponent_time).pack(side=LEFT, padx=5)
        
        # Control panel
        self.create_control_panel()
        
        # Status bar
        self.status_frame = Frame(self.main_frame)
        self.status_frame.pack(fill=X, pady=5)
        
        Label(self.status_frame, text="連接狀態:").pack(side=LEFT)
        Label(self.status_frame, textvariable=self.connection_status).pack(side=LEFT, padx=5)
        
        Label(self.status_frame, text="遊戲狀態:").pack(side=LEFT, padx=(20, 0))
        Label(self.status_frame, textvariable=self.game_status).pack(side=LEFT, padx=5)
    
    def create_control_panel(self):
        """Create control panel with game options"""
        control_frame = Frame(self.main_frame)
        control_frame.pack(pady=10)
        
        # Network controls
        network_frame = LabelFrame(control_frame, text="網路", padx=5, pady=5)
        network_frame.pack(side=TOP, fill=X, pady=5)
        
        self.host_button = Button(network_frame, text="建立遊戲", command=self.host_game)
        self.host_button.pack(side=LEFT, padx=5)
        
        self.join_button = Button(network_frame, text="加入遊戲", command=self.join_game)
        self.join_button.pack(side=LEFT, padx=5)
        
        self.disconnect_button = Button(network_frame, text="中斷連接", command=self.disconnect, state=DISABLED)
        self.disconnect_button.pack(side=LEFT, padx=5)
        
        # Game controls
        game_frame = LabelFrame(control_frame, text="遊戲", padx=5, pady=5)
        game_frame.pack(side=TOP, fill=X, pady=5)
        
        # Difficulty buttons
        for diff in Difficulty:
            Button(
                game_frame,
                text=DifficultyConfig.CONFIGS[diff]["name"],
                command=lambda d=diff: self.change_difficulty(d)
            ).pack(side=LEFT, padx=5)
        
        self.reset_button = Button(game_frame, text="重置遊戲", command=self.new_game)
        self.reset_button.pack(side=LEFT, padx=5)
        
        self.debug_button = Button(game_frame, text="Debug 模式：關閉", command=self.toggle_debug_mode)
        self.debug_button.pack(side=LEFT, padx=5)
    
    def center_window(self):
        """Center the window on screen and set appropriate size"""
        self.window.update_idletasks()
        
        # Calculate window size based on two game boards side by side
        width = self.gameBoard.width * 32 * 2 + 120  # Two boards plus padding
        height = self.gameBoard.height * 32 + 300  # Add space for controls and status
        
        screen_width = self.window.winfo_screenwidth()
        screen_height = self.window.winfo_screenheight()
        x = (screen_width - width) // 2
        y = (screen_height - height) // 2
        self.window.geometry(f"{width}x{height}+{x}+{y}")
    
    def toggle_debug_mode(self):
        """Toggle debug mode to show mines"""
        self.debug_mode = not self.debug_mode
        self.debug_button.config(text=f"Debug 模式：{'開啟' if self.debug_mode else '關閉'}")
        self.update_board()
    
    def update_timer(self):
        """Update the game timer every second"""
        if self.gameBoard.game_started and not self.is_game_over:
            player_time = self.gameBoard.get_current_time(True)
            opponent_time = self.gameBoard.get_current_time(False)
            
            # Format time as MM:SS
            player_minutes = int(player_time) // 60
            player_seconds = int(player_time) % 60
            self.player_time.set(f"{player_minutes:02d}:{player_seconds:02d}")
            
            opponent_minutes = int(opponent_time) // 60
            opponent_seconds = int(opponent_time) % 60
            self.opponent_time.set(f"{opponent_minutes:02d}:{opponent_seconds:02d}")
        
        # Schedule next update
        self.window.after(1000, self.update_timer)
    
    def host_game(self):
        """Host a new multiplayer game"""
        # Get local IP address
        hostname = socket.gethostname()
        local_ip = socket.gethostbyname(hostname)
        
        # Ask for port number
        port = simpledialog.askinteger("Host Game", f"Your IP: {local_ip}\nEnter port number:", initialvalue=5555)
        if not port:
            return
        
        # Initialize network as host
        self.is_host = True
        self.network = NetworkManager(is_host=True, host_ip="0.0.0.0", port=port)
        self.network.set_callback(self.handle_network_message)
        
        if self.network.start_server():
            self.connection_status.set(f"等待對手連接 (IP: {local_ip}, 端口: {port})")
            self.host_button.config(state=DISABLED)
            self.join_button.config(state=DISABLED)
            self.disconnect_button.config(state=NORMAL)
    
    def join_game(self):
        """Join an existing multiplayer game"""
        # Ask for host IP and port
        host_ip = simpledialog.askstring("Join Game", "Enter host IP address:", initialvalue="localhost")
        if not host_ip:
            return
        
        port = simpledialog.askinteger("Join Game", "Enter port number:", initialvalue=5555)
        if not port:
            return
        
        # Initialize network as client
        self.is_host = False
        self.network = NetworkManager(is_host=False, host_ip=host_ip, port=port)
        self.network.set_callback(self.handle_network_message)
        
        if self.network.connect_to_server():
            self.connection_status.set(f"已連接到 {host_ip}:{port}")
            self.connected = True
            self.host_button.config(state=DISABLED)
            self.join_button.config(state=DISABLED)
            self.disconnect_button.config(state=NORMAL)
            
            # Notify host that we're ready
            self.network.send_message(NetworkMessage.PLAYER_READY, {
                "difficulty": self.config.name
            })
    
    def disconnect(self):
        """Disconnect from the current game"""
        if self.network:
            self.network.close()
            self.network = None
        
        self.connected = False
        self.connection_status.set("未連接")
        self.host_button.config(state=NORMAL)
        self.join_button.config(state=NORMAL)
        self.disconnect_button.config(state=DISABLED)
        
        # Stop the game and reset
        self.is_game_over = True
        self.game_status.set("連接已中斷")
        self.game_started = False
        
        # Reset the game
        self.new_game()
    
    def handle_network_message(self, message):
        """Handle incoming network messages"""
        message_type = message["type"]
        data = message["data"]
        
        # Handle disconnection message from NetworkManager
        if message_type == "disconnected":
            self.connected = False
            self.connection_status.set("連接已中斷")
            self.host_button.config(state=NORMAL)
            self.join_button.config(state=NORMAL)
            self.disconnect_button.config(state=DISABLED)
            
            # Stop the game
            self.is_game_over = True
            self.game_status.set("連接已中斷")
            self.game_started = False
            return
            
        if message_type == NetworkMessage.PLAYER_READY:
            # Other player is ready, start the game
            if self.is_host:
                self.connection_status.set("對手已連接")
                self.connected = True
                
                # Start the game for the host
                self.gameBoard.start_game()
                self.game_started = True
                self.game_status.set("遊戲開始")
                
                # Send initial game state
                self.network.send_message(NetworkMessage.GAME_START, {
                    "difficulty": self.config.name,
                    "board_state": self.gameBoard.get_serializable_state(False)
                })
        
        elif message_type == NetworkMessage.GAME_START:
            # Host started the game
            if not self.is_host:
                self.game_status.set("遊戲開始")
                self.gameBoard.start_game()
                self.game_started = True
                
                # Update opponent's board
                opponent_state = data["board_state"]
                self.gameBoard.update_from_serialized_state(False, opponent_state)
                self.update_board()
        
        elif message_type == NetworkMessage.CELL_REVEAL:
            # Opponent revealed a cell
            r = data["row"]
            c = data["col"]
            is_first_click = data.get("is_first_click", False)
            
            # If this is the opponent's first click, place mines on their board
            if is_first_click:
                if self.opponent_first_click:
                    self.opponent_first_click = False
                    self.gameBoard.place_mines(False, r, c)
                    self.gameBoard.calculate_numbers(False)
                    
                    # If we're the host, send our board state to the client
                    if self.is_host and self.connected:
                        self.network.send_message(NetworkMessage.GAME_STATE, {
                            "player_board": self.gameBoard.get_serializable_state(True),
                            "opponent_board": self.gameBoard.get_serializable_state(False)
                        })
            
            # Process the cell reveal on the opponent's board (right side)
            cell = self.gameBoard.get_cell(False, r, c)
            
            if cell.is_mine():
                # Only add penalty if this mine wasn't already revealed
                if not cell.revealed:
                    cell.exploded = True
                    cell.revealed = True
                    self.gameBoard.add_penalty(False)
                    
                    # Send mine hit notification
                    if self.connected:
                        self.network.send_message(NetworkMessage.MINE_HIT, {
                            "is_player": False
                        })
            elif cell.is_number():
                cell.revealed = True
            elif cell.is_empty():
                self.gameBoard.flood_fill(False, r, c)
            
            self.update_board()
            
            # Only check win condition if the game has started
            # Note: We don't check win condition here because this is the opponent's move
            # The opponent will check their own win condition and notify us if they win
        
        elif message_type == NetworkMessage.CELL_FLAG:
            # Opponent flagged a cell on their board (our right side)
            r = data["row"]
            c = data["col"]
            flagged = data["flagged"]
            
            cell = self.gameBoard.get_cell(False, r, c)
            cell.flagged = flagged
            
            self.update_board()
        
        elif message_type == NetworkMessage.MINE_HIT:
            # Opponent hit a mine
            is_player = data["is_player"]
            if is_player:
                self.game_status.set("對手踩到地雷！+10秒")
            else:
                self.game_status.set("你踩到地雷！+10秒")
        
        elif message_type == NetworkMessage.GAME_WIN:
            # Opponent won the game
            self.game_over(False)
        
        elif message_type == NetworkMessage.GAME_OVER:
            # Game ended
            self.is_game_over = True
            self.game_status.set("遊戲結束")
    
        elif message_type == NetworkMessage.GAME_STATE:
            # Full game state update
            if "player_board" in data and "opponent_board" in data:
                # Update both boards
                self.gameBoard.update_from_serialized_state(True, data["player_board"])
                self.gameBoard.update_from_serialized_state(False, data["opponent_board"])
                self.update_board()
    
    def new_game(self):
        """Start a new game"""
        self.gameBoard.reset()
        self.is_game_over = False
        self.first_click = True
        self.opponent_first_click = True
        self.player_time.set("00:00")
        self.opponent_time.set("00:00")
        self.game_status.set("等待開始")
        
        if self.connected:
            self.game_status.set("遊戲準備中")
            
            # If host, send game start message
            if self.is_host and self.network:
                # Start the game for the host
                self.gameBoard.start_game()
                self.game_started = True
                self.game_status.set("遊戲開始")
                
                self.network.send_message(NetworkMessage.GAME_START, {
                    "difficulty": self.config.name,
                    "board_state": self.gameBoard.get_serializable_state(False)
                })
        
        self.update_board()
    
    def game_over(self, player_won):
        """Handle game over state"""
        self.is_game_over = True
        
        if player_won:
            self.game_status.set("恭喜！你贏了！")
            messagebox.showinfo("遊戲結束", "恭喜！你贏了！")
            
            # Notify opponent
            if self.connected:
                self.network.send_message(NetworkMessage.GAME_WIN, {
                    "winner": "player"
                })
        else:
            self.game_status.set("對手贏了！")
            messagebox.showinfo("遊戲結束", "對手贏了！")
    
    def on_left_click(self, r, c):
        """Handle left click on player's board"""
        if self.is_game_over or not self.connected:
            return
        
        # Start game on first click
        if self.first_click:
            self.first_click = False
            self.gameBoard.place_mines(True, r, c)
            self.gameBoard.calculate_numbers(True)
            
            # If we're not the host, the game might not have started yet
            if not self.game_started:
                self.gameBoard.start_game()
                self.game_started = True
                self.game_status.set("遊戲進行中")
        
        # Don't reveal flagged cells
        cell = self.gameBoard.get_cell(True, r, c)
        if not cell.revealed and cell.flagged:
            return
        
        # Reveal the cell
        if cell.is_mine():
            # Only add penalty if this mine wasn't already revealed
            if not cell.revealed:
                cell.exploded = True
                cell.revealed = True
                self.gameBoard.add_penalty(True)
                
                # Notify opponent
                if self.connected:
                    self.network.send_message(NetworkMessage.MINE_HIT, {
                        "is_player": True
                    })
                    
                self.game_status.set("你踩到地雷！+10秒")
        elif cell.is_number():
            cell.revealed = True
        elif cell.is_empty():
            self.gameBoard.flood_fill(True, r, c)
        
        # Update UI
        self.update_board()
        
        # Send move to opponent
        if self.connected:
            self.network.send_message(NetworkMessage.CELL_REVEAL, {
                "row": r,
                "col": c,
                "is_first_click": self.first_click
            })
            
            # If this is the first click, also send the full game state
            if self.first_click == False and self.opponent_first_click == True:
                self.network.send_message(NetworkMessage.GAME_STATE, {
                    "player_board": self.gameBoard.get_serializable_state(True),
                    "opponent_board": self.gameBoard.get_serializable_state(False)
                })
        
        # Check win condition
        if self.game_started and self.gameBoard.check_win_condition(True):
            self.game_over(True)
    
    def on_right_click(self, r, c):
        """Handle right click (flag) on player's board"""
        if self.is_game_over or not self.connected:
            return
        
        # Can't flag revealed cells
        cell = self.gameBoard.get_cell(True, r, c)
        if cell.revealed:
            return
        
        # Toggle flag
        cell.flagged = not cell.flagged
        
        # Update UI
        self.update_board()
        
        # Send flag update to opponent
        if self.connected:
            self.network.send_message(NetworkMessage.CELL_FLAG, {
                "row": r,
                "col": c,
                "flagged": cell.flagged
            })
    
    def on_chord_press(self, r, c):
        """Handle chord press (middle click preview)"""
        if self.is_game_over or not self.connected:
            return
        
        cell = self.gameBoard.get_cell(True, r, c)
        if not cell.revealed or not cell.is_number():
            return
        
        flag_count = self.gameBoard.count_flags_around(True, r, c)
        if flag_count != cell.number:
            return
        
        self.chord_holding = True
        
        # Show preview of surrounding cells
        for dr in [-1, 0, 1]:
            for dc in [-1, 0, 1]:
                if dr == 0 and dc == 0:
                    continue
                nr = r + dr
                nc = c + dc
                if self.gameBoard.is_valid_position(nr, nc):
                    neighbor = self.gameBoard.get_cell(True, nr, nc)
                    if not neighbor.flagged and not neighbor.revealed:
                        btn = self.player_buttons[nr][nc]
                        btn.config(image=self.tile_images["TileEmpty"])
    
    def on_chord_release(self, r, c):
        """Handle chord release (middle click)"""
        if not self.chord_holding:
            return
        
        self.chord_holding = False
        self.update_board()
        self.on_chord_click(r, c)
    
    def on_chord_click(self, r, c):
        """Handle chord click (middle click) to reveal surrounding cells"""
        if self.is_game_over or not self.connected:
            return
        
        cell = self.gameBoard.get_cell(True, r, c)
        if not cell.revealed or not cell.is_number():
            return
        
        flag_count = self.gameBoard.count_flags_around(True, r, c)
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
                    neighbor = self.gameBoard.get_cell(True, nr, nc)
                    if not neighbor.flagged and not neighbor.revealed:
                        if neighbor.is_mine():
                            # Only add penalty if this mine wasn't already revealed
                            if not neighbor.revealed:
                                neighbor.exploded = True
                                neighbor.revealed = True
                                exploded = True
                                self.gameBoard.add_penalty(True)
                                
                                # Notify opponent
                                if self.connected:
                                    self.network.send_message(NetworkMessage.MINE_HIT, {
                                        "is_player": True
                                    })
                        elif neighbor.is_number():
                            neighbor.revealed = True
                        else:  # empty
                            self.gameBoard.flood_fill(True, nr, nc)
                        
                        # Send move to opponent
                        if self.connected:
                            self.network.send_message(NetworkMessage.CELL_REVEAL, {
                                "row": nr,
                                "col": nc,
                                "is_first_click": False
                            })
        
        if exploded:
            self.game_status.set("你踩到地雷！+10秒")
        
        self.update_board()
        
        # Check win condition
        if self.gameBoard.check_win_condition(True):
            self.game_over(True)
    
    def update_board(self):
        """Update both game boards UI"""
        # Update player board
        for r in range(self.gameBoard.height):
            for c in range(self.gameBoard.width):
                cell = self.gameBoard.get_cell(True, r, c)
                btn = self.player_buttons[r][c]
                
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
        
        # Update opponent board
        for r in range(self.gameBoard.height):
            for c in range(self.gameBoard.width):
                cell = self.gameBoard.get_cell(False, r, c)
                btn = self.opponent_buttons[r][c]
                
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
        """Change game difficulty"""
        if self.connected:
            messagebox.showinfo("無法更改", "連接中無法更改難度")
            return
            
        self.config = DifficultyConfig(difficulty)
        self.gameBoard = MultiplayerGameBoard(
            self.config.board_width,
            self.config.board_height,
            self.config.mine_count
        )
        
        # Recreate UI
        self.player_buttons = []
        self.opponent_buttons = []
        self.main_frame.destroy()
        self.create_widgets()
        self.center_window()
        self.new_game()

# Main entry point
if __name__ == "__main__":
    window = Tk()
    window.title("雙人對戰踩地雷")
    game = MineSweeperMultiplayer(window)
    game.start()
