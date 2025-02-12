#include <iostream>
#include <vector>
#include <queue>
using namespace std;
void bfs(vector<vector<int>> &graph, int from, int to, const int n)
{
    if (from == to)
    {
        cout << "Yes!!!\n";
        return;
    }
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(from);
    visited[from] = true;
    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        for (int &neighbor : graph[current])
        {
            if (!visited[neighbor])
            {
                if (neighbor == to)
                {
                    cout << "Yes!!!\n";
                    return;
                }
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << "No!!!\n";
    return;
}
int main(void)
{
    int n, m;
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    while (cin >> n >> m)
    {
        int from, to;
        vector<vector<int>> graph(n + 1);
        for (int i = 0; i < m; ++i)
        {
            cin >> from >> to;
            graph[from].push_back(to);
        }
        cin >> from >> to;
        bfs(graph, from, to, n);
    }
}
/*
廣度優先搜尋七步法

1. 構造題目: 判斷城市 A 能不能到達城市 B
2. 定義狀態: graph[from] = {from 能到達的城市}

執行 BFS 步驟
4. 產生一個初始狀態，加入到 queue 當中 (在此題中是 from)
5. 檢查 queue 的首項(q.front)是不是目標狀態，是就停，否則繼續 (這裡是 to)
6. 將首項去除(q.pop)，加入首項衍生出的後續狀態到裡面去 (在此題中是 graph[from] 的所有元素)
7. 假如 queue 為空，表示沒找到目標，非空則回到第 2 步驟

DFS 和 DFS 的差別在於使用的是 queue 還是 stack, 如果會衍生出的狀態可能會回到初始的地方, 使用 visited 陣列紀錄是否走訪過
*/