import random
from MineSweeper_Cell import Cell
class GameBoard:
    """遊戲初始化"""
    def __init__(self, board_width: int, board_height: int, mine_count: int):
        self.width = board_width
        self.height = board_height
        self.mine_count = mine_count
        self.cells: list[list[Cell]] = []
        self.reset()
    
    def reset(self):
        """重置, 沒什麼好說的"""
        self.cells = [[Cell(r, c) for c in range(self.width)] 
                     for r in range(self.height)]
    
    def place_mines(self, first_r: int, first_c: int):
        """放地雷, 確保第一次按下, 該位置八方位領域展開的區域不會爆炸"""
        safe_cells = set()
        for dr in [-1, 0, 1]:
            for dc in [-1, 0, 1]:
                nr = first_r + dr
                nc = first_c + dc
                if 0 <= nr < self.height and 0 <= nc < self.width:
                    safe_cells.add((nr, nc))
                    
        count = 0
        while count < self.mine_count:
            r = random.randrange(self.height)
            c = random.randrange(self.width)
            if (r, c) not in safe_cells and not self.cells[r][c].is_mine():
                self.cells[r][c].set_mine()
                count += 1
    
    def calculate_numbers(self):
        """計算每個格子周圍的地雷數"""
        for r in range(self.height):
            for c in range(self.width):
                cell = self.cells[r][c]
                if cell.is_mine():
                    continue
                mine_count = sum(1
                    for dr in [-1, 0, 1]
                    for dc in [-1, 0, 1]
                    if 0 <= r + dr < self.height
                    and 0 <= c + dc < self.width
                    and self.cells[r + dr][c + dc].is_mine()
                )
                if mine_count > 0:
                    cell.set_number(mine_count)
    
    def get_cell(self, r: int, c: int) -> Cell:
        """指定位置的格子"""
        return self.cells[r][c]
    
    def is_valid_position(self, r: int, c: int) -> bool:
        """檢查座標有沒有超出世界之外"""
        return 0 <= r < self.height and 0 <= c < self.width
    
    def count_flags_around(self, r: int, c: int) -> int:
        """數數周圍的旗子"""
        flag_count = 0
        for dr in [-1, 0, 1]:
            for dc in [-1, 0, 1]:
                nr = r + dr
                nc = c + dc
                if self.is_valid_position(nr, nc) and self.cells[nr][nc].flagged:
                    flag_count += 1
        return flag_count