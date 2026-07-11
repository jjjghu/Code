#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
const static int MAXN = 1e5 + 1;
const static int MAXM = 2e5 + 1;

// 鏈式前向星
int head[MAXN]{};
int Next[MAXM]{};
int to[MAXM]{};
int weight[MAXM];
int cnt = 0;

// 反向索引堆
int heap[MAXM]{};
int heapSize;
int where[MAXN]{};

// 距離
int dist[MAXN]{};
void build(int n)
{
    // 鏈式前向星
    cnt = 1;
    fill(head, head + n + 1, 0);

    // 反向索引堆
    heapSize = 0;
    fill(where, where + n + 1, -1);

    // 初始化距離
    fill(dist, dist + n + 1, INT_MAX);
}

void addEdge(int u, int v, int w)
{
    to[cnt] = v;
    weight[cnt] = w;
    Next[cnt] = head[u];
    head[u] = cnt++;
}

bool isEmpty()
{
    return heapSize == 0;
}

void heapSwap(int i, int j)
{
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
    where[heap[i]] = i;
    where[heap[j]] = j;
}

void heapify(int i)
{
    int l = i * 2 + 1;
    while (l < heapSize)
    {
        int best = (l + 1 < heapSize && dist[heap[l + 1]] < dist[heap[l]]) ? l + 1 : l;
        best = dist[heap[i]] < dist[heap[best]] ? i : best;
        if (best == i)
            break;
        heapSwap(best, i);
        i = best;
        l = i * 2 + 1;
    }
}
int pop()
{
    int res = heap[0];
    heapSwap(0, --heapSize);
    heapify(0);
    where[res] = -2;
    return res;
}

void heapInsert(int i)
{
    while (dist[heap[(i - 1) / 2]] > dist[heap[i]])
    {
        heapSwap((i - 1) / 2, i);
        i = (i - 1) / 2;
    }
}

void addOrUpdateOrIgnore(int v, int c)
{
    if (where[v] == -1)
    { // 沒進過堆
        heap[heapSize] = v;
        where[v] = heapSize++;
        dist[v] = c;
        heapInsert(where[v]);
    }
    else if (where[v] >= 0)
    {
        dist[v] = min(dist[v], c);
        heapInsert(where[v]);
    }
}

int main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, m, s;
    cin >> n >> m >> s;
    build(n);
    int u, v, w;
    while (cin >> u >> v >> w)
    {
        addEdge(u, v, w);
    }

    addOrUpdateOrIgnore(s, 0);
    while (!isEmpty())
    {
        int u = pop();
        for (int ei = head[u]; ei != 0; ei = Next[ei])
        {
            addOrUpdateOrIgnore(to[ei], dist[u] + weight[ei]);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << dist[i] << " ";
    }
}