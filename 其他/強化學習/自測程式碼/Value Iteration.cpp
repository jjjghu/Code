#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
const int dir[5] = {-1, 0, 1, 0, -1}; // 四個方向
void printGrid(vector<vector<double>>& grid) {
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            cout << setw(6) << fixed << setprecision(2) << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
int main(void) {
    const int n = 4;
    int startX = 3, startY = 1;
    int targetX = 0, targetY = 3;
    int maxRound = 6;
    vector<vector<double>> grid(n, vector<double>(n, 0.0));
    
    // 馬可夫參數
    double gamma = 0.9; // 折扣因子
    double threshold = 0.01; // 當變化量小於閾值時，停止更新
    
    int round = 0;
    while(round++ < maxRound) {
    // while(true) {
        printGrid(grid);
        vector<vector<double>> nextGrid = grid; // 存更新的結果
        double max_change = 0; // 記錄這一輪當中，變動最大的數值是多少
        for(int x = 0; x < n; x++) {
            for(int y = 0; y < n; y++) {
                if(x == targetX && y == targetY) {
                    continue;
                }
                vector<double> nums; // 紀錄四方向數值
                for(int i = 0; i < 4; i++) {
                    double reward = -1.0; // 走出一步的基本懲罰
                    int nx = x + dir[i];
                    int ny = y + dir[i + 1];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= n) {
                        // reward = -10.0;
                        // nx = x;
                        // ny = y;
                        continue;
                    }
                    else if(nx == targetX && ny == targetY) {
                        reward = 10.0;
                    }
                    // 貝爾曼公式：R + gamma * V(s')
                    // 因為 P(s'|s,a) = 1, 不需要 Sum
                    nums.push_back(reward + gamma * grid[nx][ny]);
                }
                nextGrid[x][y] = *max_element(nums.begin(), nums.end());
                max_change = max(max_change, abs(nextGrid[x][y] - grid[x][y]));
            }
        }
        grid = nextGrid;
        if(max_change < threshold) break;
    }
    printGrid(grid);
}