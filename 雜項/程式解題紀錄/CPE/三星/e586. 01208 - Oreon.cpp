#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <functional>
using namespace std;
struct Edge
{
    int x, y, w;
    bool operator<(const Edge& other)
    {
        if(w != other.w) return w < other.w;
        else if(x != other.x) return x < other.x;
        else return y < other.y;
    }
};
int convert(string& s)
{
    int num = 0;
    for(int i = 0; i < s.length(); ++i)
    {
        if(isdigit(s[i]))
        {
            num *= 10;
            num += s[i] - '0';
            continue;
        }
        break;
    }
    return num;
}
int find_parent(vector<int>& parent, int x)
{
    if(x != parent[x])
    {
        parent[x] = find_parent(parent, parent[x]);
    }
    return parent[x];
}
int main(void)
{
    int t, n;
    string s;
    cin >> t;
    for(int c = 1; c <= t; ++c)
    {
        vector<Edge> edge;
        cin >> n;

        // UnionFind
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);

        // 輸入
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                cin >> s;
                int temp = convert(s);
                if(temp == 0) // 沒有連接
                {
                    // can't use INT_MAX in zerojudge, which is sucks 
                    edge.push_back({i, j, 2147483647}); 
                    continue;
                }
                edge.push_back({i, j, temp});
                
            }
        }

        // 每次選權重最小的合併
        sort(edge.begin(), edge.end());
        cout << "Case " << c << ":" << endl;
        for(Edge e : edge)
        {
            int rootX = find_parent(parent, e.x);
            int rootY = find_parent(parent, e.y);
            if(rootX == rootY) continue;
            parent[rootX] = rootY;
            cout << (char)('A' + e.x) << "-" << (char)('A' + e.y) << " " << e.w << endl;
        }
        
    }
    return 0;
}