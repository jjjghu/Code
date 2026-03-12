#include <iostream>
#include <numeric>
#include <algorithm>
using namespace std;
const int MAXN = 5002;
const int MAXM = 2e5+1;
int parent[MAXN];
struct Edge {
    int u, v, w;
    bool operator<(const Edge& other){
        return this->w < other.w;
    }
};
Edge edges[MAXM];
int find(int x) {
    if(parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    iota(parent, parent + n + 1, 0);
    for(int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    sort(edges, edges + m);
    int res = 0, cnt = 0;
    for(int i = 0; i < m; i++) {
        int rootU = find(edges[i].u);
        int rootV = find(edges[i].v);
        if(rootU != rootV) {
            parent[rootU] = rootV;
            res += edges[i].w;
            if(++cnt == n - 1) {
                cout << res;
                return 0;
            }
        }
    }
    cout << "orz";
}