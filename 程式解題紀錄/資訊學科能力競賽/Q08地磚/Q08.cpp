#include <iostream>
#include <vector>
using namespace std;
void dfs(const vector<vector<int>> &grid, vector<vector<bool>> &visited, int x, int y, const int &value)
{
    int n = grid.size();
    if (x < 0 || x >= n || y < 0 || y >= n || visited[x][y] || grid[x][y] != value)
    {
        return;
    }
    visited[x][y] = true;
    dfs(grid, visited, x + 1, y, value);
    dfs(grid, visited, x, y + 1, value);
    dfs(grid, visited, x - 1, y, value);
    dfs(grid, visited, x, y - 1, value);
}
int main()
{
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> grid[i][j];
            if (grid[i][j] == 2)
            {
                visited[i][j] = true;
            }
        }
    }

    int white, grey;
    white = grey = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (!visited[i][j])
            {
                if (grid[i][j] == 0)
                {
                    white++;
                }
                if (grid[i][j] == 1)
                {
                    grey++;
                }
                dfs(grid, visited, i, j, grid[i][j]);
            }
        }
    }

    cout << grey << " " << white;
}