#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
using namespace std;
struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator<(const Edge& other) {
        return this->w < other.w;
    }
};
class Solution {
private:
    static const int MX = 1e5+1;
    int parent[MX];
    int find(int x) {
        if(x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    bool isSameSet(int x, int y) {
        return find(x) == find(y);
    }
    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        iota(parent, parent + n, 0);
        int edgeCount = 0;
        int res = INT_MAX;
        vector<Edge> sortedEdges; // 每次取出權重最大的邊
        for(int i = 0; i < edges.size(); i++) {
            auto edge = edges[i];
            if(edge.back() ) { // 如果是必須要被加入的邊，事先加入。
                if(isSameSet(edge[0], edge[1])) { // 已經在同一個集合當中，表示這是多餘的邊
                    return -1;
                }
                res = min(res, edge[2]);
                unite(edge[0], edge[1]);
            }
            else { // 沒有必須要被加入的邊，紀錄到 pq 當中
                sortedEdges.push_back(Edge(edge[0], edge[1], edge[2]));
            }
        }
        sort(sortedEdges.begin(), sortedEdges.end());
        
        vector<int> chosenWeights; // 被選擇到生成樹當中，可以強化的邊權。
        for(int i = 0; i < sortedEdges.size(); i++) {
            Edge edge = sortedEdges[i];
            if(isSameSet(edge.u, edge.v)) continue;
            res = min(res, (edge.w << 1));
            unite(edge.u, edge.v);
            chosenWeights.push_back(edge.w);
            if(++edgeCount == n - 1) break;
        }
        if(edgeCount != n - 1) return -1;
        for(int i = 0; i < chosenWeights.size(); i++) {
            if(i < k) {
                res = min(res, (chosenWeights[i] << 1));
            }
            else {
                res = min(res, chosenWeights[i]);
            }
        }
        return res;
    }
};
int main(void) {
    Solution sol;
    int n = 3, k = 1;
    vector<vector<int>> edges = {{0,1,2,1}, {1,2,3,0}};
    cout << sol.maxStability(n, edges, k);
}