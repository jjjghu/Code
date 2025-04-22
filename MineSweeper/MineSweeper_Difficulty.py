from enum import auto, Enum

class Difficulty(Enum):
    EASY = auto()
    NORMAL = auto() 
    HARD = auto() 
    
class DifficultyConfig(): 
    CONFIGS = {
        Difficulty.EASY:{
            "board_width": 9,
            "board_height": 9,
            "mine_count": 10,
            "name": "簡單"
        },
        Difficulty.NORMAL:{
            "board_width": 16,
            "board_height": 16,
            "mine_count": 40,
            "name": "普通"
        },
        Difficulty.HARD:{
            "board_width": 30,
            "board_height": 16,
            "mine_count": 99,
            "name": "困難"
        }
    }
    def __init__(self, difficulty: Difficulty):
        config = self.CONFIGS[difficulty]
        self.board_width:int = config["board_width"]
        self.board_height:int = config["board_height"]
        self.mine_count:int = config["mine_count"]
        self.name:str = config["name"]