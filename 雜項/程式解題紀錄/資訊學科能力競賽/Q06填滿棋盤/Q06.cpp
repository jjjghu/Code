#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Point
{
    int x, y, dist;
    Point(int x, int y, int dist) : x(x), y(y), dist(dist) {}
};

int bfs(const vector<vector<int>> &board, vector<vector<bool>> visited, int startX, int startY, int endX, int endY)
{
    int m = board.size() - 1, n = board[0].size() - 1;
    queue<Point> q;
    q.push(Point(startX, startY, 0));
    visited[startX][startY] = true;

    int dir[] = {1, 0, -1, 0, 1};
    while (!q.empty())
    {
        Point current = q.front();
        q.pop();
        if (current.x == endX && current.y == endY)
        {
            return current.dist;
        }
        for (int i = 0; i < 4; ++i)
        {
            int nextX = current.x + dir[i];
            int nextY = current.y + dir[i + 1];
            if (nextX >= 1 && nextX <= m && nextY >= 1 && nextY <= n && !visited[nextX][nextY] && board[nextX][nextY] != -1)
            {
                visited[nextX][nextY] = true;
                q.push(Point(nextX, nextY, current.dist + 1));
            }
        }
    }
    return INT_MAX;
}

int main()
{
    int m, n, currentX, currentY;
    cin >> m >> n >> currentX >> currentY;
    vector<vector<int>> board(m + 1, vector<int>(n + 1, 0));
    vector<vector<bool>> visited(m + 1, vector<bool>(n + 1, false));
    board[currentX][currentY] = 1;
    visited[currentX][currentY] = true;
    int step = 2;

    int x, y;
    while (cin >> x >> y)
    {
        board[x][y] = -1;
        visited[x][y] = true;
    }

    while (true)
    {
        int maxDist = -1;
        int nextX = -1, nextY = -1;
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (board[i][j] == 0)
                {
                    int dist = bfs(board, visited, currentX, currentY, i, j);
                    if (dist < INT_MAX && (dist > maxDist || (dist == maxDist && (i > nextX || (i == nextX && j > nextY)))))
                    {
                        maxDist = dist;
                        nextX = i;
                        nextY = j;
                    }
                }
            }
        }
        // 沒有可標記的格子了
        if (nextX == -1 && nextY == -1)
            break;
        board[nextX][nextY] = step++;
        visited[currentX][currentY] = true;
        currentX = nextX;
        currentY = nextY;
    }

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (board[i][j] == -1 || board[i][j] == 0)
            {
                cout << "0 ";
            }
            else
            {
                cout << board[i][j] << " ";
            }
        }
        // cout << endl;
    }
    return 0;
}