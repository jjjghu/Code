#include <iostream>
#include <vector>
#include <random>
using namespace std;
class Solution {
private:
    const int n = 4; // 邊界
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};
    const char* arrows[4] = {" ^ ", " v ", " < ", " > ",};

    int startX = 3, startY = 1; // 起始位置
    int targetX = 0, targetY = 3; // 目標位置
    
    double learningRate = 0.1; // 學習率
    double gamma = 0.9; // 折扣因子
    double epsilon = 0.1; // 10% 的時間亂走

    vector<vector<double>> grid;
    
    int MX = 1e6; // 大數
    static const int MXStep = 10; // 每次亂走最多 10 步，驗證收斂速度的快慢

    bool isOutOfBound(int x, int y) { 
        return x < 0 || x >= n || y < 0 || y >= n;
    }
    int epsilonGreedy(int x, int y) {
        if((rand() % 100) < (epsilon * 100)) {
            return rand() % 4;
        }
        int bestAction = rand() % 4; // 隨機一個，避免四個方向都無法選擇
        double mxVal = -1e18;
        for(int i = 0; i < 4; i++) { // 嘗試四個方向，找出最佳的行動
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(isOutOfBound(nx, ny)) continue; // 出界，不該選
            if(grid[nx][ny] > mxVal) {
                mxVal = grid[nx][ny];
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
            double nextValue; 
            if(isOutOfBound(nx, ny)) {
                // 撞到牆壁，越界扣十分，結束。
                reward = -10;
                grid[x][y] += learningRate * (reward - grid[x][y]);
                break;
            }
            if(nx == targetX && ny == targetY) {
                grid[x][y] = 100; // 抵達終點，獲得大獎
            }
            else {
                reward = -1;
                nextValue = grid[nx][ny];
                grid[x][y] += learningRate * (reward + gamma * nextValue - grid[x][y]); // 正常走路，消耗步數。
            }
            x = nx; 
            y = ny;
        }
    }
public:
    Solution() : grid(n, vector<double>(n, 0.0)) {
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
                int bestDir = -1;
                double maxVal = -1e9;
                for(int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
                        if(grid[nx][ny] > maxVal) {
                            maxVal = grid[nx][ny];
                            bestDir = i;
                        }
                    }
                }
                if(bestDir != -1) cout << arrows[bestDir];
                else cout << "  ?  ";
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