#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;
int n, m, a, b, c, d;
void bfs(vector<vector<int>> &graph, vector<vector<bool>> &visited)
{
    queue<pair<int, int>> q;
    q.push({a, b});
    vector<int> dir = {0, 1, 0, -1, 0};
    int step = 0;
    while (!q.empty())
    {
        int size = q.size();
        ++step;
        for (int i = 0; i < size; ++i)
        {
            auto [x, y] = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dir[i];
                int ny = y + dir[i + 1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && graph[nx][ny] == 0 && !visited[nx][ny])
                {
                    visited[nx][ny] = true;
                    if (nx == c && ny == d)
                    {
                        cout << step << "\n";
                        return;
                    }
                    q.push({nx, ny});
                }
            }
        }
    }
    cout << "0\n";
}
int main(void)
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
    {
        string s;
        cin >> n >> m >> a >> b >> c >> d;
        --a, --b, --c, --d;
        vector<vector<int>> graph(n, vector<int>(m));
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; ++i)
        {
            cin >> s;
            for (int j = 0; j < m; ++j)
            {
                graph[i][j] = s[j] - '0';
                if (graph[i][j] == 1)
                {
                    visited[i][j] = true;
                }
            }
        }
        bfs(graph, visited);
    }
}
