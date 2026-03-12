#include <iostream>
using namespace std;
const int MAXN = 5002;
const int MAXM = 4e5+2;

// 題目輸入
int n, m, x, y, z;

// 鏈式前向星
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int id = 1;

// 小根堆
int heap[MAXN][2]; // 每個節點的紀錄最多進入一次，出去一次。
int where[MAXN]; // 紀錄節點在 heap 的位置。-2代表已經出去過，-1代表新節點
int heapSize; // 當前堆的大小

void build() {
    // 鏈式前向星初始化
    fill(head, head + n + 1, 0);
    id = 1;
    // 堆相關的反向索引表初始化
    fill(where, where + n + 1, -1);
    heapSize = 0;
}
// 鏈式前向星的相關函數
void addEdge(int u, int v, int w) {
    to[id] = v;
    weight[id] = w;
    Next[id] = head[u];
    head[u] = id++;
}

// 堆調整相關函數
void heapSwap(int i, int j) {
    swap(where[heap[i][0]], where[heap[j][0]]);
    swap(heap[i], heap[j]);
}
bool isEmpty() {
    return heapSize == 0;
}
// 向上調整
void heapInsert(int i) {
    while(heap[i][1] < heap[(i - 1) / 2][1]) {
        heapSwap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}
// 向下調整
void heapify(int i) {
    int l = i * 2 + 1;
    while(l < heapSize) {
        int best = l + 1 < heapSize && heap[l + 1][1] < heap[l][1] ? l + 1 : l;
        // 如果當前節點已經比最小的孩子還小（或相等），說明調整完畢
        if(heap[i][1] <= heap[best][1]) {
            break;
        }
        heapSwap(i, best);
        i = best;
        l = i * 2 + 1;
    }
}
// 丟掉最小節點
void pop() {
    int v = heap[0][0]; // 存頂端節點
    heapSwap(0, --heapSize); // 拿尾端補頂端
    heapify(0);
    where[v] = -2; // 標記為已經出過 heap
}
// 當前處理的是編號為 ei 的邊
void addOrUpdateOrIgnore(int ei) {
    int v = to[ei];
    int w = weight[ei];
    if(where[v] == -1) { // 沒有進入過，就進入
        heap[heapSize][0] = v;
        heap[heapSize][1] = w;
        where[v] = heapSize++;
        heapInsert(where[v]); // 調整這個位置的數值
    }
    else if(where[v] >= 0) { // 位於堆中
        if(heap[where[v]][1] > w) { // 更新數值
            heap[where[v]][1] = w;
            heapInsert(where[v]); // 向上調整
        }
    }
}
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    build();
    for(int i = 0; i < m; i++) {
        cin >> x >> y >> z;
        addEdge(x, y, z);
        addEdge(y, x, z);
    }
    
    int nodeCnt = 1; // 當前觸碰到的點數量
    int cost = 0;
    where[1] = -2; // 節點 1 視為已經彈出
    for(int ei = head[1]; ei > 0; ei = Next[ei]) { // 將第一個點能接觸到的鄰居放入 heap, 作為初始狀態
        addOrUpdateOrIgnore(ei);
    }

    while(!isEmpty()) {
        int v = heap[0][0];
        int w = heap[0][1];
        pop();
        cost += w;
        nodeCnt++;
        for(int ei = head[v]; ei > 0; ei = Next[ei]) {
            addOrUpdateOrIgnore(ei);
        }
    }
    if(nodeCnt != n) {
        cout << "orz";
    }
    else {
        cout << cost; 
    }
}