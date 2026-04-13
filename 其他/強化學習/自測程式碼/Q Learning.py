import random

class Solution:
    def __init__(self):
        self.n = 4  # 邊界
        self.actionSize = 4  # 可選動作數目
        self.dx = [-1, 1, 0, 0]
        self.dy = [0, 0, -1, 1]
        self.arrows = [" ^ ", " v ", " < ", " > "]

        self.startX = 3
        self.startY = 1  # 起始位置
        self.targetX = 0
        self.targetY = 3  # 目標位置
        
        self.learningRate = 0.1  # 學習率
        self.gamma = 0.9  # 折扣因子
        self.epsilon = 0.1  # 10% 的時間亂走

        self.grid = [[[0.0 for _ in range(self.actionSize)] for _ in range(self.n)] for _ in range(self.n)]  # grid[x][y][action], Q(s,a)
        
        self.MX = 1000000  # 大數
        self.MXStep = 10  # 每次亂走最多 10 步，驗證收斂速度的快慢

        random.seed()

    def isOutOfBound(self, x, y):  # 判斷越界
        return x < 0 or x >= self.n or y < 0 or y >= self.n

    def epsilonGreedy(self, x, y):
        if random.random() < self.epsilon:  # 亂走探索新方向
            return random.randint(0, self.actionSize - 1)
        bestAction = 0
        mxVal = float('-inf')
        for i in range(self.actionSize):  # 從四種方向的行動當中，選出預期價值最高的那一個
            if self.grid[x][y][i] > mxVal:  # 選擇最好的動作
                mxVal = self.grid[x][y][i]
                bestAction = i
        return bestAction

    def wondering(self, x, y):        
        for step in range(self.MXStep):
            action = self.epsilonGreedy(x, y)
            
            nx = x + self.dx[action]
            ny = y + self.dy[action]
            
            if self.isOutOfBound(nx, ny):
                # 撞到牆壁，越界扣十分，結束。
                reward = -10
                self.grid[x][y][action] += self.learningRate * (reward - self.grid[x][y][action])
                break
            if nx == self.targetX and ny == self.targetY:
                # 抵達終點，獲得大獎
                reward = 100
                self.grid[x][y][action] += self.learningRate * (reward - self.grid[x][y][action])
                break
            else:
                reward = -1
                nextValue = max(self.grid[nx][ny])  # 從下一個狀態的所有動作中選出最大的 Q 值
                self.grid[x][y][action] += self.learningRate * (reward + self.gamma * nextValue - self.grid[x][y][action])  # 正常走路，消耗步數。
            x = nx 
            y = ny

    def QLearning(self):
        # 總共採樣 MX 次
        for i in range(self.MX):
            self.wondering(self.startX, self.startY)

    def printResult(self):
        for x in range(self.n):
            for y in range(self.n):
                if x == self.targetX and y == self.targetY:
                    print(" GOAL ", end="")
                    continue
                # 找上下左右哪一格的 grid 分數最高
                bestAction = -1
                mx = float('-inf')
                for i in range(self.actionSize):
                    if self.grid[x][y][i] > mx:
                        mx = self.grid[x][y][i]
                        bestAction = i
                if bestAction != -1:
                    print(self.arrows[bestAction], end="")
                else:
                    print("  ?  ", end="")  # 這個格子還沒踩過
            print()

if __name__ == "__main__":
    sol = Solution()
    sol.QLearning()
    sol.printResult()
        