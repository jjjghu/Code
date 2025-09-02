#include <iostream>
#include <vector>
using namespace std;

vector<int> dx = {-1, -1, -1, 0, 0, 1, 1, 1};
vector<int> dy = {-1, 0, 1, -1, 1, -1, 0, 1};

void solve(vector<vector<int>>& grid)
{
    int n = grid.size(), m = grid[0].size();
    for(int x = 0; x < n; ++x)
    {
        for(int y = 0; y < m; ++y)
        {
            if(grid[x][y] == -1)
            {
                int cnt = 0;
                for(int k = 0; k < 8; ++k)
                {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] == -1)
                        continue;
                    grid[nx][ny] += 1;
                }
            }
        }
    }
}
int main(void)
{
    int n, m, t = 0;
    char ch;
    while(cin >> n >> m)
    {
        if(n == 0 && m == 0)
            break;
        ++t;

        vector<vector<int>> grid(n, vector<int>(m, 0));
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                cin >> ch;
                if(ch == '*')
                    grid[i][j] = -1;
            }
        }
        solve(grid);
        cout << "Field #" << t << ":" << endl;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == -1)
                    cout << '*';
                else
                    cout << grid[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
