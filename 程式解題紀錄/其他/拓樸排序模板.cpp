#include <iostream>
#include <queue>
using namespace std;
const int MX = 1e5+1;
int cnt;
int head[MX];
int Next[MX];
int to[MX];

int indegree[MX];

int pq[MX]; 
int pqSize;
void push(int x) {
    int i = pqSize++;
    pq[i] = x;
    // 向上調整
    while(pq[i] < pq[(i - 1) / 2]) {
        swap(pq[i], pq[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
int pop() {
    int res = pq[0];
    pq[0] = pq[--pqSize];
    int i = 0, l = 1;
    while(l < pqSize) {
        int best = l + 1 < pqSize && pq[l + 1] < pq[l] ? l + 1 : l;
        best = pq[best] < pq[i] ? best : i;
        if(best == i) break;
        swap(pq[best], pq[i]);
        i = best;
        l = i * 2 + 1;
    }
    return res;
}
bool isEmpty() {
    return pqSize == 0;
}

void build(int n) {
    cnt = 1;
    pqSize = 0;
    fill(head, head + n + 1, 0);
    fill(indegree, indegree + n + 1, 0);
}
void addEdge(int u, int v) {
    to[cnt] = v;
    Next[cnt] = head[u];
    head[u] = cnt++;
}
int n, m, u, v;
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    build(n);
    for(int i = 0; i < m; i++) {
        cin >> u >> v;        
        indegree[v]++;
        addEdge(u, v);
    }
    
    for(int i = 1; i <= n; i++) {
        if(indegree[i] == 0) {
            push(i);
        }
    }
    while(!isEmpty()) {
        int top = pop();
        cout << top << " ";
        for(int ei = head[top]; ei != 0; ei = Next[ei]) {
            if(--indegree[to[ei]] == 0) {
                push(to[ei]);
            }
        }
    }
}