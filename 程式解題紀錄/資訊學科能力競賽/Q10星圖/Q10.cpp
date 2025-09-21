#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

int bfs(const string &start, const string &end, int n)
{
    if (start == end)
    {
        return 0;
    }
    unordered_map<string, int> visitedStart, visitedEnd; // visited[s] = 到 s 的最短距離
    queue<string> qStart, qEnd;
    visitedStart[start] = 0;
    visitedEnd[end] = 0;
    qStart.push(start);
    qEnd.push(end);
    while (!qStart.empty() && !qEnd.empty())
    {
        if (!qStart.empty())
        {
            string current = qStart.front();
            qStart.pop();
            // 交換得出下一步
            for (int d = 1; d < n; ++d)
            {
                string s = current;
                if (s[0] == s[d])
                {
                    continue;
                }
                swap(s[0], s[d]);
                // 沒有走訪
                if (visitedStart.find(s) == visitedStart.end())
                {
                    // 標記
                    visitedStart[s] = visitedStart[current] + 1;
                    // parentStart[s] = current; // 記錄節點
                    qStart.push(s);
                    // 另一邊有走訪過, 表示連接成功
                    if (visitedEnd.find(s) != visitedEnd.end())
                    {
                        return visitedStart[s] + visitedEnd[s];
                    }
                }
            }
        }
        if (!qEnd.empty())
        {
            string current = qEnd.front();
            qEnd.pop();
            for (int d = 1; d < n; ++d)
            {
                string s = current;
                if (s[0] == s[d])
                {
                    continue;
                }
                swap(s[0], s[d]);
                qEnd.push(s);
                if (visitedEnd.find(s) == visitedEnd.end())
                {
                    visitedEnd[s] = visitedEnd[current] + 1;
                    // parentEnd[s] = current;
                    if (visitedStart.find(s) != visitedStart.end())
                    {
                        return visitedStart[s] + visitedEnd[s];
                    }
                }
            }
        }
    }
    return -1;
}
int main(void)
{
    int n;
    cin >> n;
    for (int i = 0; i < 5; ++i)
    {
        string start, end;
        cin >> start >> end;
        cout << bfs(start, end, n) << "\n";
    }
}