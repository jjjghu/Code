#include <iostream>
#include <queue>
using namespace std;
#define pii pair<int,int>
const int MAXN = 5001;
const int MAXM = 4e5+1; // 雙向邊最多的數量
// 鏈式前向星
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int id = 1;
// 判斷哪些邊已經觸碰到
bool used[MAXN];
void build(int n) {
    fill(head, head + n + 1, 0);
    id = 1;
    fill(used, used + n + 1, false);
}
void addEdge(int u, int v, int w) {
    Next[id] = head[u];
    to[id] = v;
    weight[id] = w;
    head[u] = id++;
}
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, x, y, z;
    cin >> n >> m;
    build(n);
    for(int i = 0; i < m; i++) {
        cin >> x >> y >> z;
        addEdge(x, y, z);
        addEdge(y, x, z);
    }
    priority_queue<pii, vector<pii>, greater<pii>> pq; // 存放權重, 鄰居
    for(int ei = head[1]; ei > 0; ei = Next[ei]) {
        pq.push({weight[ei], to[ei]});
    }
    used[1] = true;
    int cnt = 1; // 當前觸碰到的點數量
    int cost = 0;
    while(!pq.empty()) {
        pii cur = pq.top(); pq.pop();
        if(!used[cur.second]) {// 沒有觸碰過這個節點
            used[cur.second] = true;
            cnt++;
            cost += cur.first;
            for(int ei = head[cur.second]; ei > 0; ei = Next[ei]) { // 加入新的邊
                pq.push({weight[ei], to[ei]});
            }
            if(cnt == n) {
                break;
            }
        }
    }
    if(cnt != n) {
        cout << "orz";
    }
    else {
        cout << cost; 
    }
}