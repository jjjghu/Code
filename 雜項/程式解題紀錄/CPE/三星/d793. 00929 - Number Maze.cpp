#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using pii = pair<int,int>;
int solve(vector<vector<int>>& grid)
{
    int m = grid.size(), n = grid[0].size();
    int dir[5] = {-1, 0, 1, 0, -1};

    vector<vector<int>> dist(m, vector<int>(n, 2147483647));
    dist[0][0] = grid[0][0];
    
    priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<>> pq; // dist, {x, y} 
    pq.push({dist[0][0], {0, 0}});
    
    while(!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        int d = cur.first;
        int x = cur.second.first;
        int y = cur.second.second;

        if(d > dist[x][y])
            continue;

        for(int i = 0; i < 4; ++i)
        {
            int nx = x + dir[i];
            int ny = y + dir[i + 1];
            // 越界
            if(nx < 0 || nx >= m || ny < 0 || ny >= n)
            {
                continue;
            }
            // 現在找到的走法(走到coord的最短距離 + 從 coord 走道下格的距離) 比較好
            if(dist[nx][ny] > dist[x][y] + grid[nx][ny])
            {
                // 更新
                dist[nx][ny] = dist[x][y] + grid[nx][ny];
                pq.push({dist[nx][ny], {nx, ny}});
            }
        }
    }
    return dist[m - 1][n - 1];
}
int main(void)
{
    int t;
    cin >> t;
    while(t--)
    {
        int m, n;
        cin >> m >> n;
        vector<vector<int>> grid(m, vector<int>(n));
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                cin >> grid[i][j];
            }
        }
        cout << solve(grid) << endl;
    }
}