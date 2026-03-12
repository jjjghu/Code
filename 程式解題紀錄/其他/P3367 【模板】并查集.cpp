#include <iostream>
#include <numeric>
using namespace std;
int n, m;
const int MX = 2e5 + 1;
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
    int rootX = find(x);
    int rootY = find(y);
    parent[rootX] = rootY;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    iota(parent, parent + n, 0);
    int z, x, y;
    for(int i = 0; i < m; i++) {
        cin >> z >> x >> y;
        if(z == 2) cout << (isSameSet(x, y) ? "Y" : "N") << "\n";
        else unite(x, y);
    }
}