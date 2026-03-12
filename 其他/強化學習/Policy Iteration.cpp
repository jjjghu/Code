#include <iostream>
#include <vector>
using namespace std;
class Solution {
private:
    static const int n = 4;
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};
    const char* arrows[4] = {" ^ ", " v ", " < ", " > ",};

    int startX = 3, startY = 1; // 起始位置
    int targetX = 0, targetY = 3; // 目標位置
    
    // 馬可夫參數
    double gamma = 0.9; // 折扣因子
    double threshold = 0.01; // 當變化量小於閾值時，停止更新

    vector<vector<double>> grid;
    vector<vector<int>> policy; // 每一個格子的最佳移動方向
    
    void policyEvaluation() {
        while(true) {
            vector<vector<double>> nextGrid = grid;
            double mxDiff = 0;
            for(int x = 0; x < n; x++) {
                for(int y = 0; y < n; y++) {
                    if(x == targetX && y == targetY) continue;
                    int action = policy[x][y]; // 根據當前的策略去走
                    int nx = x + dx[action];
                    int ny = y + dy[action];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                    double reward = (nx == targetX  && ny == targetY) ? 10.0 : -1.0;
                    nextGrid[x][y] = reward + gamma * grid[nx][ny];
                    mxDiff = max(mxDiff, abs(nextGrid[x][y] - grid[x][y]));
                }
                if(mxDiff < threshold) break;
            }
            grid = nextGrid;
        }
    }
    bool policyImprovement() {
        bool stable = true;
        for(int x = 0; x < n; x++) {
            for(int y = 0; y < n; y++) {
                if(x == targetX && y == targetY) continue;
                int oldAction = policy[x][y];
                int bestAction = oldAction;
                double mx = -1e9;
                for(int i = 0; i < 4; i++) { // 在四個方向當中，選出能最大化獎勵的方向
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                    double reward = (nx == targetX  && ny == targetY) ? 10.0 : -1.0;
                    double cur = reward + gamma * grid[nx][ny];
                    if(cur > mx) {
                        mx = cur;
                        bestAction = i;
                    }
                }
                policy[x][y] = bestAction;
                if(oldAction != bestAction) stable = false;
            }
        } 
        return stable;
    }
    void printPolicy() {
        for(int x = 0; x < n; x++) {
            for(int y = 0; y < n; y++) {
                if(x == targetX && y == targetY) {
                    cout << " GOAL ";
                    continue;
                }
                cout << arrows[policy[x][y]];
            }
            cout << endl;
        }
        cout << endl;
    }
public:
    Solution() : grid(n, vector<double>(n, 0.0)), policy(n, vector<int>(n, 0)) {}
    void policyIteration() {
        printPolicy();
        while(!policyImprovement()) {
            policyEvaluation();
            printPolicy();
        }
    }
};
int main(void) {
    Solution sol;
    sol.policyIteration();
}