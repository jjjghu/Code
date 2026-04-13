#include <iostream>
#include <vector>
#include <array>
#include <random>
using namespace std;
class Solution {
private:
    const int n = 4; // 邊界
    static const int actionSize = 4; // 可選動作數目
    const int dx[actionSize] = {-1, 1, 0, 0};
    const int dy[actionSize] = {0, 0, -1, 1};
    const char* arrows[4] = {" ^ ", " v ", " < ", " > ",};

    int startX = 3, startY = 1; // 起始位置
    int targetX = 0, targetY = 3; // 目標位置
    
    double learningRate = 0.1; // 學習率
    double gamma = 0.9; // 折扣因子
    double epsilon = 0.1; // 10% 的時間亂走

    vector<vector<array<double, actionSize>>> grid; // grid[x][y][action], Q(s,a)
    
    int MX = 1e6; // 大數
    static const int MXStep = 10; // 每次亂走最多 10 步，驗證收斂速度的快慢

    bool isOutOfBound(int x, int y) { // 判斷越界
        return x < 0 || x >= n || y < 0 || y >= n;
    }

    int epsilonGreedy(int x, int y) {
        if((rand() % 100) < (epsilon * 100)) { // 亂走探索新方向
            return rand() % actionSize;
        }
        int bestAction = rand() % actionSize;
        double mxVal = -1e18;
        for(int i = 0; i < actionSize; i++) { // 從四種方向的行動當中，選出預期價值最高的那一個
            if(grid[x][y][i] > mxVal) { // 選擇最好的動作
                mxVal = grid[x][y][i];
                bestAction = i;
            }
        }
        return bestAction;
    }

    void wondering(int x, int y) {        
        for(int step = 0; step < MXStep; step++) {
            int action = epsilonGreedy(x, y);
            
            int nx = x + dx[action];
            int ny = y + dy[action];
            
            double reward;
            if(isOutOfBound(nx, ny)) {
                // 撞到牆壁，越界扣十分，結束。
                reward = -10;
                grid[x][y][action] += learningRate * (reward - grid[x][y][action]);
                break;
            }
            if(nx == targetX && ny == targetY) {
                // grid[x][y][action] = 100; // 抵達終點，獲得大獎
                grid[x][y][action] += learningRate * (reward - grid[x][y][action]);
            }
            else {
                reward = -1;
                double nextValue = grid[nx][ny][action];
                for(int i = 0; i < actionSize; i++) {
                    if(grid[nx][ny][i] > nextValue) {
                        nextValue = grid[nx][ny][i];
                    }
                }
                grid[x][y][action] += learningRate * (reward + gamma * nextValue - grid[x][y][action]); // 正常走路，消耗步數。
            }
            x = nx; 
            y = ny;
        }
    }
public:
    Solution() : grid(n, vector<array<double, actionSize>>(n)) {
        srand(time(NULL));
    }
    void QLearning() {
        // 總共採樣 MX 次
        for(int i = 0; i < MX; i++) {
            wondering(startX, startY);
        }
    }
    void printResult() {
        for(int x = 0; x < n; x++) {
            for(int y = 0; y < n; y++) {
                if(x == targetX && y == targetY) {
                    cout << " GOAL "; continue;
                }
                // 找上下左右哪一格的 grid 分數最高
                int bestAction = -1;
                double mx = -1e18;
                for(int i = 0; i < actionSize; i++) {
                    if(grid[x][y][i] > mx) {
                        mx = grid[x][y][i];
                        bestAction = i;
                    }
                }
                if(bestAction != -1) cout << arrows[bestAction];
                else cout << "  ?  "; // 這個格子還沒踩過
            }
            cout << endl;
        }
    }
};
int main(void) {
    Solution sol;
    sol.QLearning();
    sol.printResult();
}