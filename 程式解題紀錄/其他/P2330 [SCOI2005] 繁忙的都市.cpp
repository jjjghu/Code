#include <iostream>
#include <array>
#include <numeric>
#include <algorithm>
using namespace std;
const int MAXN = 301;
const int MAXM = 8001;
int n, m;
int parent[MAXN];
array<int, 3> edges[MAXM]; // 為了排序，用 array
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
void build() {
    iota(parent, parent + n, 0);
}
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    build();
    for(int i = 0; i < m; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }
    sort(edges, edges + m, [&](const auto& a, const auto& b){
        return a[2] < b[2];
    });
    int edgeCnt = 0;
    for(int i = 0; i < m; i++) {
        auto& edge = edges[i];
        if(!isSameSet(edge[0], edge[1])) {
            unite(edge[0], edge[1]);
            if(++edgeCnt == n - 1) {
                cout << edgeCnt << " " << edge[2];
                break;
            }
        }
    }
}