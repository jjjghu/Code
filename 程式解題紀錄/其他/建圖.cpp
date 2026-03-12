#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 11, MAXM = 21; // 如果無向圖的最大數量是 m 條邊，數量要準備 m * 2

// 鄰接矩陣建圖
int graph1[MAXN][MAXN];

// 鄰接表方式建圖
vector<vector<pair<int,int>>> graph2;

// 鏈式前向星
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

void build(int n){
    // 鄰接矩陣清空
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            graph1[i][j] = 0;
        }
    }

    // 鄰接表
    graph2.clear();
    graph2.resize(n + 1);

    // 鏈式前向星
    cnt = 1;
    fill(head, head + n + 1, 0);
}

// 鏈式前向星加邊
void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
    weight[cnt] = w;
    cnt++;
}
void directGraph(vector<vector<int>> edges) {
    // from = edge[0], to = edge[1], weight = edge[2]
    // 鄰接矩陣建圖
    for(auto& edge : edges) {
        graph1[edge[0]][edge[1]] = edge[2];
    }
    // 鄰接表建圖
    for(auto& edge : edges) {
        graph2[edge[0]].push_back({edge[1], edge[2]});
    }
    // 鏈式前向星建圖
    for(auto& edge : edges) {
        addEdge(edge[0], edge[1], edge[2]);
    }
}
void undirectGraph(vector<vector<int>> edges) {
    // from = edge[0], to = edge[1], weight = edge[2]
    // 鄰接矩陣建圖
    for(auto& edge : edges) {
        graph1[edge[0]][edge[1]] = edge[2];
        graph1[edge[1]][edge[0]] = edge[2];
    }
    // 鄰接表建圖
    for(auto& edge : edges) {
        graph2[edge[0]].push_back({edge[1], edge[2]});
        graph2[edge[1]].push_back({edge[0], edge[2]});
    }
    // 鏈式前向星建圖
    for(auto& edge : edges) {
        addEdge(edge[0], edge[1], edge[2]);
        addEdge(edge[1], edge[0], edge[2]);
    }
}
void traversal(int n) {
    cout << "鄰接矩陣遍歷：" << endl;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cout << graph1[i][j] << " ";
        }
        cout << endl;
    }
    cout << "鄰接表遍歷：" << endl;
    for(int i = 1; i <= n; i++) {
        cout << i << "(鄰居、邊權)：";
        for(auto& neighbor : graph2[i]) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }
    cout << "鏈式前向星：" << endl;
    for(int i = 1; i <= n; i++) {
        cout << i << "(鄰居、邊權)：";
        for(int ei = head[i]; ei > 0; ei = Next[ei]) { // edgeIndex: 邊的編號
             cout << "(" << to[ei] << ", " << weight[ei] << ") ";
        }
        cout << endl;
    }
}

int main(void) {
    int n1 = 4;
    vector<vector<int>> edges1 = { { 1, 3, 6 }, { 4, 3, 4 }, { 2, 4, 2 }, { 1, 2, 7 }, { 2, 3, 5 }, { 3, 1, 1 } };
    build(n1);
    directGraph(edges1);
    traversal(n1);
    cout << "==============================" << endl;
    int n2 = 5;
    vector<vector<int>> edges2 = { { 3, 5, 4 }, { 4, 1, 1 }, { 3, 4, 2 }, { 5, 2, 4 }, { 2, 3, 7 }, { 1, 5, 5 }, { 4, 2, 6 } };
    build(n2);
    undirectGraph(edges2);
    traversal(n2);
}