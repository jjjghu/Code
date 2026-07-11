#include <iostream>
#include <climits>
#include <algorithm>
#include <queue>
#include <tuple>
using namespace std;

const int MX_N = 1e4 + 1;
const int MX_M = 1e5 + 1; // 5e4 * 2

// 鏈式前向星
int head[MX_N];
int Next[MX_M];
int to[MX_M];
int weight[MX_M];
int cnt;

// djikstra 
int dist[MX_N][11]; // dist[node][0] = 距離, dist[node][1] = 剩餘免單次數


// heap 
int heap[MX_M * 11][3]; // curDist, city, 剩餘免單次數
int heapSize;

void build(int n, int k) {
	fill(head, head + n + 1, 0);
	cnt = 1;

	for(int i = 0; i < n; i++) {
		fill(dist[i], dist[i] + k + 1, INT_MAX);
	}

	heapSize = 0;
}

void addEdge(int u, int v, int w) {
	Next[cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
	weight[cnt] = w;
	cnt++;
}

void heapSwap(int i, int j) {
	swap(heap[i], heap[j]);
}

void heapInsert(int curDist, int node, int k) {
	heap[heapSize][0] = curDist;
	heap[heapSize][1] = node;
	heap[heapSize][2] = k;
	int i = heapSize++;
	while(heap[i][0] < heap[(i - 1) / 2][0]) {
		swap(heap[i], heap[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

void heapify() {
	int i = 0;
	int l = 1;
	while(l < heapSize) {
		int best = l + 1 < heapSize && heap[l][0] > heap[l + 1][0] ? l + 1 : l;
		best = heap[best][0] < heap[i][0] ? best : i;
		if(best == i) {
			break;
		}
		else {
			heapSwap(i, best);
		}
		i = best;
		l = i * 2 + 1;
	}
}

void heapPop() {
	--heapSize;
	heapSwap(0, heapSize);
	heapify();
}

bool isEmpty() {
	return heapSize == 0;
}

int main(void) {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, k, s, t;
	int u, v, w;
	cin >> n >> m >> k;
	cin >> s >> t;
	build(n, k);
	for(int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		addEdge(u, v, w);
		addEdge(v, u, w);
	}

	using tiii = tuple<int, int, int>;
	heapInsert(0, s, k);
	dist[s][k] = 0;
	while(!isEmpty()) {
		int curDist = heap[0][0];
		int node = heap[0][1];
		int leftK = heap[0][2];
		heapPop();
		if(curDist > dist[node][leftK]) continue;
		if(node == t) {
			cout << dist[node][leftK];
			return 0;
		}
		for(int ei = head[node]; ei != 0; ei = Next[ei]) {
			int newDist = curDist;
			if(leftK > 0 && newDist < dist[to[ei]][leftK - 1]) { // 使用免單
				dist[to[ei]][leftK - 1] = newDist;
				heapInsert(newDist, to[ei], leftK - 1);
			}
			
			newDist += weight[ei]; // 注意在這裡就加了邊權
			if(newDist < dist[to[ei]][leftK]) { // 不使用免單
				dist[to[ei]][leftK] = newDist;
				heapInsert(newDist, to[ei], leftK);
			}
		}
	}
	cout << -1 << endl; // something wrong
}