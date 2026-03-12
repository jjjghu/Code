#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    Edge(const vector<int>& vec) : u(vec[0]), v(vec[1]), w(vec[2]) {}
    bool operator<(const Edge& other) {
        return this->w < other.w;
    }
};
class Solution {
private:
    static const int MX = 1e4+5;
    int parent[MX];
    int find(int x) {
        if(parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    bool isSameSet(int x, int y) {
        return find(x) == find(y);
    }
    void unite(int x, int y) {
        parent[find(x)] = parent[find(y)];
    }
public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        // 節點 0 代表水源，一個虛擬節點。
        iota(parent, parent + n + 1, 0);
        vector<Edge> edges;
        for(int i = 1; i <= n; i++) {
            edges.push_back(Edge(0, i, wells[i - 1]));
        }
        for(auto& vec : pipes) {
            edges.push_back(Edge(vec));
        }
        sort(edges.begin(), edges.end());
        int res = 0;
        int edgeCnt = 0;
        for(Edge& edge : edges) {
            if(!isSameSet(edge.u, edge.v)) {
                res += edge.w;
                unite(edge.u, edge.v);
                if(++edgeCnt == n) { // 共 n + 1 個點
                    break;
                }
            }
        }
        return res;
    }
};
int main(void) {
    Solution sol;
    int n = 3;
    vector<int> wells = {1, 2, 2};
    vector<vector<int>> pipes = {{1, 2, 1}, {2, 3, 1}};
    cout << sol.minCostToSupplyWater(n, wells, pipes);
}