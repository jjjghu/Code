from MineSweeper_GameBoard import GameBoard
from MineSweeper_Cell import Cell, CellType
import time

class MultiplayerGameBoard:
    """管理兩個玩家的遊戲狀態"""
    def __init__(self, board_width, board_height, mine_count):
        
        # 創建兩個遊戲場地
        self.player_board = GameBoard(board_width, board_height, mine_count)
        self.opponent_board = GameBoard(board_width, board_height, mine_count)
        
        # 遊戲變數
        self.width = board_width
        self.height = board_height
        self.mine_count = mine_count
        self.game_started = False
        self.game_over = False
        self.winner = None
        
        # 計時器
        self.start_time = 0
        self.player_time = 0
        self.opponent_time = 0
        self.player_penalty = 0
        self.opponent_penalty = 0
        
        # 踩到地雷爆炸的懲罰時間
        self.mine_penalty = 10
    
    def start_game(self):
        """開始遊戲, 開始計時"""
        self.game_started = True
        self.start_time = time.time()
    
    def reset(self):
        """重置兩個玩家的遊戲版"""
        self.player_board.reset()
        self.opponent_board.reset()
        self.game_started = False
        self.game_over = False
        self.winner = None
        self.start_time = 0
        self.player_time = 0
        self.opponent_time = 0
        self.player_penalty = 0
        self.opponent_penalty = 0
    
    def place_mines(self, is_player, first_r, first_c):
        """在兩個板子上擺放地雷"""
        if is_player:
            self.player_board.place_mines(first_r, first_c)
            self.player_board.calculate_numbers()
        else:
            # Mirror the column for opponent board
            mirrored_c = self.width - 1 - first_c
            self.opponent_board.place_mines(first_r, mirrored_c)
            self.opponent_board.calculate_numbers()
    
    def calculate_numbers(self, is_player):
        """計算玩家版面上的數字應該怎麼擺"""
        if is_player:
            self.player_board.calculate_numbers()
        else:
            self.opponent_board.calculate_numbers()
    
    def get_cell(self, is_player, r, c):
        """獲取特定玩家的 cell"""
        if is_player:
            return self.player_board.get_cell(r, c)
        else:
            # For opponent board, we need to mirror the column to correctly map
            # player A's left side to player B's right side
            mirrored_c = self.width - 1 - c
            return self.opponent_board.get_cell(r, mirrored_c)
    
    def is_valid_position(self, r, c):
        """Check if a position is valid on the board"""
        return self.player_board.is_valid_position(r, c)
    
    def count_flags_around(self, is_player, r, c):
        """計算旗子的數量"""
        if is_player:
            return self.player_board.count_flags_around(r, c)
        else:
            # Mirror the column for opponent board
            mirrored_c = self.width - 1 - c
            return self.opponent_board.count_flags_around(r, mirrored_c)
    
    def add_penalty(self, is_player):
        """增加時間懲罰"""
        if is_player:
            self.player_penalty += self.mine_penalty
        else:
            self.opponent_penalty += self.mine_penalty
    
    def get_current_time(self, is_player):
        """獲取當前經過的時間(加入懲罰)"""
        if not self.game_started:
            return 0
        
        elapsed = time.time() - self.start_time
        if is_player:
            return elapsed + self.player_penalty
        else:
            return elapsed + self.opponent_penalty
    
    def check_win_condition(self, is_player):
        """檢查你贏沒贏"""
        board = self.player_board if is_player else self.opponent_board
        
        # 檢查是不是所有非地雷的方格都被展開
        for r in range(board.height):
            for c in range(board.width):
                cell = board.get_cell(r, c)
                if not cell.is_mine() and not cell.revealed:
                    return False
        
        # 遊戲結束
        self.game_over = True
        self.winner = "player" if is_player else "opponent"
        return True
    
    def flood_fill(self, is_player, r, c):
        """炫酷的塌陷"""
        if is_player:
            board = self.player_board
            actual_c = c
        else:
            board = self.opponent_board
            # Mirror the column for opponent board
            actual_c = self.width - 1 - c
        
        if not board.is_valid_position(r, actual_c):
            return
            
        cell = board.get_cell(r, actual_c)
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
                    # For opponent board, we need to check if the mirrored position is valid
                    if is_player:
                        if board.is_valid_position(nr, nc):
                            self.flood_fill(is_player, nr, nc)
                    else:
                        # For opponent board, we need to mirror the column
                        if board.is_valid_position(nr, self.width - 1 - nc):
                            self.flood_fill(is_player, nr, nc)
    
    def get_serializable_state(self, is_player):
        """將資料轉換為序列化的數據, 用於網路通訊"""
        board = self.player_board if is_player else self.opponent_board
        cells_data = []
        
        for r in range(board.height):
            row_data = []
            for c in range(board.width):
                cell = board.get_cell(r, c)
                cell_data = {
                    "row": cell.row,
                    "col": cell.col,
                    "type": cell.type.name,
                    "number": cell.number,
                    "revealed": cell.revealed,
                    "flagged": cell.flagged,
                    "exploded": cell.exploded
                }
                row_data.append(cell_data)
            cells_data.append(row_data)
        
        return {
            "cells": cells_data,
            "width": board.width,
            "height": board.height,
            "mine_count": board.mine_count
        }
    
    def update_from_serialized_state(self, is_player, state_data):
        """從序列化的資料轉回版面的樣子"""
        board = self.player_board if is_player else self.opponent_board
        cells_data = state_data["cells"]
        
        for r in range(len(cells_data)):
            for c in range(len(cells_data[r])):
                cell_data = cells_data[r][c]
                cell = board.get_cell(r, c)
                
                # Update cell type
                if cell_data["type"] == "MINE":
                    cell.type = CellType.MINE
                elif cell_data["type"] == "NUMBER":
                    cell.type = CellType.NUMBER
                    cell.number = cell_data["number"]
                else:
                    cell.type = CellType.EMPTY
                
                # Update cell state
                cell.revealed = cell_data["revealed"]
                cell.flagged = cell_data["flagged"]
                cell.exploded = cell_data["exploded"]
