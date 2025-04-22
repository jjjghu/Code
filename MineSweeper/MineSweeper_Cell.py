from enum import auto, Enum

class CellType(Enum):
    EMPTY = auto()
    MINE = auto()
    NUMBER = auto()
    
class Cell:
    def __init__(self, row, col):
        self.row:int        = row 
        self.col:int        = col     
        self.type:CellType  = CellType.EMPTY
        self.number:int     = 0
        self.revealed:bool  = False
        self.flagged:bool   = False
        self.exploded:bool  = False
    
    def reset(self):
        self.type = CellType.EMPTY
    
    def is_mine(self):
        return self.type == CellType.MINE

    def is_number(self):
        return self.type == CellType.NUMBER
    
    def is_empty(self):
        return self.type == CellType.EMPTY
    
    def set_mine(self):
        self.type = CellType.MINE
    
    def set_number(self, number:int):
        self.type = CellType.NUMBER
        self.number = number