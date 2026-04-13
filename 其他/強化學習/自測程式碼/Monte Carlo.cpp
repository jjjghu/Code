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

    vector<vector<double>> grid;
    
    int MX = 1e6; // 大數
    static const int MXStep = 100; // 每次亂走最多 100 步
    int path[MXStep][2]; // 紀錄每次經過的步數
    int rewards[MXStep]; // 紀錄每步獲得的獎勵

    int wondering(int x, int y) {
        // 亂走階段
        int step; 
        for(step = 0; step < MXStep; step++) {
            int action = rand() % 4;
            int nx = x + dx[action];
            int ny = y + dy[action];
            path[step][0] = nx;
            path[step][1] = ny;
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) {
                // 撞到牆壁，越界扣十分，結束。
                rewards[step] -= 10; 
                break;
            }
            if(nx == targetX && ny == targetY) {
                rewards[step] = 100; break; // 抵達終點，獲得大獎
            }
            else {
                rewards[step] = -1; // 正常走路，消耗步數。
            }
            x = nx; 
            y = ny;
        }
        return step;
    }
    void updateValue(int step) {
        // 更新階段，將行經的狀態的價值更新。
        double G = 0;
        for(int s = step - 1; s >= 0; s--) {
            G = rewards[s] + G * gamma;
            int px = path[s][0]; // path 不會越界
            int py = path[s][1];
            if(px < 0 || px >= n || py < 0 || py >= n) continue;
            grid[px][py] += learningRate *(G - grid[px][py]);
        }
    }
public:
    Solution() : grid(n, vector<double>(n, 0.0)) {
        srand(time(NULL));
    }
    void QLearning() {
        // 總共採樣 MX 次
        for(int i = 0; i < MX; i++) {
            int step = wondering(startX, startY);
            updateValue(step);
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