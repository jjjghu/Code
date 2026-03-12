#include <iostream>
#include <vector>
#include <deque>
using namespace std;
class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        dist[0][0] = 0;
        
        deque<pair<int,int>> dq;
        dq.emplace_back(0, 0);

        int dir[5] = {-1, 0, 1, 0, -1};
        while(!dq.empty()) {
            auto [x, y] = dq.front(); dq.pop_front();
            for(int i = 0; i < 4; i++) {
                int nx = x + dir[i];
                int ny = y + dir[i + 1];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                int curDist = dist[x][y] + grid[nx][ny];
                if(dist[nx][ny] > curDist) {
                    dist[nx][ny] = curDist;
                    if(grid[nx][ny] == 1) {
                        dq.emplace_back(nx, ny);
                    }
                    else {
                        dq.emplace_front(nx, ny);
                    }
                }
            }
        }
        return dist[n - 1][m - 1];
    }
};
int main() {
    Solution sol;
    vector<vector<int>> obstacles = {{0,1,1},{1,1,0},{1,1,0}};
    cout << sol.minimumObstacles(obstacles) << endl;
    obstacles = {{0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}};
    cout << sol.minimumObstacles(obstacles) << endl;
}