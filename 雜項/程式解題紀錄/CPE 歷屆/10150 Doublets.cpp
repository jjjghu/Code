#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> g;
vector<int> parent;
void BFS(const int &beg, const int &end)
{
    // parent 充當 visited
    parent.assign(g.size(), -1);
    queue<int> q;
    q.push(beg);
    parent[beg] = beg;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (auto &neighbor : g[cur])
        {
            if (parent[neighbor] == -1)
            {
                parent[neighbor] = cur;
                if (neighbor == end)
                {
                    return;
                }
                q.push(neighbor);
            }
        }
    }
}
int main(void)
{
    // 輸入字串
    string s;
    vector<string> v;
    while (getline(cin, s))
    {
        if (s == "")
            break;
        v.push_back(s);
    }
    sort(v.begin(), v.end());
    g.assign(v.size(), vector<int>());

    // 建立鄰接表，使用 index 紀錄，而不是字串
    for (int i = 0; i < v.size(); ++i)
    {
        string alpha = "abcdefghijklmnopqrstuvwxyz";
        for (int j = 0; j < v[i].size(); ++j)
        {
            for (char c : alpha)
            {
                string temp = v[i];
                if (temp[j] == c)
                    continue;
                temp[j] = c;

                // 轉換後的字存不存在於輸入當中
                auto it = lower_bound(v.begin(), v.end(), temp);
                if (it != v.end() && *it == temp)
                {
                    g[i].push_back(it - v.begin());
                    g[it - v.begin()].push_back(i);
                }
            }
        }
    }

    int t = 0;
    string beg, end;
    while (cin >> beg >> end)
    {
        if (t++)
            cout << endl;
        int b = find(v.begin(), v.end(), beg) - v.begin();
        int e = find(v.begin(), v.end(), end) - v.begin();
        BFS(b, e);

        // 回溯路徑
        vector<int> path;
        path.push_back(e);
        for (int cur = e; cur >= 0 && cur != parent[cur]; cur = parent[cur])
        {
            if (cur >= 0)
                path.push_back(parent[cur]);
        }
        reverse(path.begin(), path.end());
        if (path.size() && path[0] == b)
        {
            for (int &e : path)
                cout << v[e] << endl;
        }
        else
            cout << "No solution." << endl;
    }
}