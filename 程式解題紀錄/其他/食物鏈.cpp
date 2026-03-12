#include <iostream>
using namespace std;
const int MAXN = 5e3+2;
const int MAXM = 5e5+2;

// 鏈式前向星
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt;

// 入度
int indegree[MAXN];

// 記錄走到這個位置的路徑有多少條
int path[MAXN];

// 隊列
int q[MAXN];

void build(int n) {
    // 鏈式前向星初始化
    cnt = 1;
    fill(head, head + n + 1, 0);
    fill(indegree, indegree + n + 1, 0); 
    // 預設路徑數量為 0
    fill(path, path + n + 1, 0);
}

void addEdge(int u, int v) {
    Next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int MOD = 80112002;
    int n, m, eaten, eater;
    cin >> n >> m;
    build(n);
    for(int i = 0; i < m; i++) {
        cin >> eaten >> eater;
        indegree[eater]++;
        addEdge(eaten, eater);
    }
    int l = 0, r = 0;
    for(int i = 1; i <= n; i++) {
        if(indegree[i] == 0) {
            path[i] = 1; // 路徑起點，有一條路
            q[r++] = i;
        }
    }
    int res = 0;
    while(l != r) {
        int cur = q[l++];
        if(head[cur] == 0) { // 沒有鄰居存在，表示自己是最強捕食者
            res = (res + path[cur]) % MOD;
        }
        else {
            for(int ei = head[cur]; ei > 0; ei = Next[ei]) {
                path[to[ei]] = (path[to[ei]] + path[cur]) % MOD;
                if(--indegree[to[ei]] == 0) {
                    q[r++] = to[ei];
                }
            }
        }
    }
    cout << res;
}