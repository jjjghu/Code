#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <bitset>
#include <map>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
const int MAX_EDGES = 1000;
struct WeightedCycle
{
    int weight;
    vector<int> cycle;
};
struct Cycle
{
    vector<int> nodes;
    bitset<MAX_EDGES> edgeMask;
    int weight;
};
vector<Cycle> findMinimumCycleBasis(const vector<WeightedCycle> &allCycles, int nodeNum, int edgenum);
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "使用方式: " << argv[0] << " <檔案名稱>" << endl;
        return 1;
    }
    // 檔案讀取相關
    ifstream inFile(argv[1]);
    if (!inFile.is_open())
    {
        cout << "無法開啟檔案: " << argv[1] << "\n";
        return 1;
    }
    int nodeNum, edgenum, cost, begin, end, i, j;
    inFile >> nodeNum >> edgenum;
    int A[nodeNum][nodeNum], Cost[nodeNum][nodeNum];
    for (i = 0; i < nodeNum; i++)
        for (j = 0; j < nodeNum; j++)
            A[i][j] = 0;
    for (int i = 0; i < edgenum; ++i)
    {
        inFile >> begin >> end >> cost;
        A[begin][end] = 1;
        A[end][begin] = 1;
        Cost[begin][end] = cost;
        Cost[end][begin] = cost;
    }
    inFile.close();
    int r, f;
    int k, c, pre, no;
    int b = 0;
    int s = 0, e = nodeNum, cycle = 0;
    int temp[nodeNum];
    int order[20000][nodeNum];
    int check_re[20000];
    int check_cycle[nodeNum];
    for (i = 0; i < 20000; i++)
        for (j = 0; j < nodeNum; j++)
            order[i][j] = -1;
    for (i = 0; i < nodeNum; i++)
        order[i][0] = i;
    int adde;
    int t;
    int smallest, compare;
    int m, n;
    vector<WeightedCycle> weightedCycles;
    for (no = 1; no < nodeNum; no++)
    {
        adde = 0;
        s = 0;
        for (k = 0; k < e; k++)
        {
            s = s + b;
            b = 0;
            pre = order[s][no - 1];
            for ((i = order[s][0] + 1); i < nodeNum; i++)
            {
                if (A[pre][i] == 1)
                {
                    for (j = 1; j < (no - 1); j++)
                    {
                        if (order[s][j] == i)
                        {
                            j = -1;
                            break;
                        }
                    }
                    if (j != -1)
                        temp[b++] = i;
                }
            }
            c = 0;

            if (b > 0)
            {
                adde = adde + b - 1;
                for (i = e + adde; i > s; i--)
                {
                    for (j = 0; j < no; j++)
                        order[i + b - 1][j] = order[i][j];
                }
                for (i = s; i < (s + b); i++)
                {
                    order[i][no] = temp[c++];
                    for (j = 0; j < no; j++)
                        order[i][j] = order[s][j];
                    if (no > 1 && A[order[i][no]][order[i][0]] == 1)
                    {

                        for (m = 0; m <= no; m++)
                            check_cycle[m] = order[i][m];

                        compare = 0;

                        for (m = 1; m <= no; m++)
                            compare = compare * 10 + check_cycle[m];
                        compare = compare * 10 + check_cycle[0];

                        check_re[i] = 0;
                        for (m = no; m >= 0; m--)
                            check_re[i] = check_re[i] * 10 + check_cycle[m];

                        for (m = 0; m < i; m++)
                        {
                            if (check_re[m] == compare)
                            {
                                m = -1;
                                break;
                            }
                        }
                        if (m != -1)
                        {
                            vector<int> comb;
                            int weight = 0;
                            for (j = 0; j <= no; j++)
                            {
                                comb.push_back(order[i][j]);
                                if (j > 0)
                                {
                                    weight += Cost[order[i][j - 1]][order[i][j]];
                                }
                            }
                            weight += Cost[order[i][no]][order[i][0]];
                            weightedCycles.push_back({weight, comb});
                            cycle++;
                        }
                    }
                }
            }
            else
            {
                for (i = s; i < e + adde; i++)
                {
                    for (j = 0; j <= no; j++)
                        order[i][j] = order[i + 1][j];
                }
                adde--;
            }
        }
        e = e + adde;
    }
    sort(weightedCycles.begin(), weightedCycles.end(), [](const WeightedCycle &a, const WeightedCycle &b)
         { return a.weight == b.weight ? a.cycle[0] < b.cycle[0] : a.weight < b.weight; });
    cout << "Minimum Cycle Basis:" << endl;
    vector<Cycle> minCycleBasis = findMinimumCycleBasis(weightedCycles, nodeNum, edgenum);
    int allweight = 0;
    for (const auto &cycle : minCycleBasis)
    {
        allweight += cycle.weight;
        cout << "Weight: " << cycle.weight << " => ";
        for (int node : cycle.nodes)
        {
            cout << setw(2) << node << " ";
        }
        cout << endl;
    }
    cout << "Number of cycles in basis: " << minCycleBasis.size() << endl;
    cout << "Expected number of cycles: " << (edgenum - nodeNum + 1) << endl;
    cout << "All weight: " << allweight << endl;
    cout << cycle << " cycles" << endl;
    return 0;
}
vector<Cycle> findMinimumCycleBasis(const vector<WeightedCycle> &allCycles, int nodeNum, int edgenum)
{
    // 回傳結果
    vector<Cycle> basis;
    // 基底的邊
    vector<bitset<MAX_EDGES>> basisMasks;
    int targetSize = edgenum - nodeNum + 1;

    // 用 index 代表邊,  {u, v} = index++;
    map<pair<int, int>, int> edgeToIndex;
    int edgeIndex = 0;

    // allCycle 是 vector<weightedCycle>, 每個 weightedCycle 有一個 cycle 向量跟 weight
    for (const auto &cycle : allCycles)
    {
        // 把每個 cycle 拆開來, 對每條邊加入一個編號, 讓每個 cycle 編出來的結果都相同
        for (int i = 0; i < cycle.cycle.size(); ++i)
        {
            int u = cycle.cycle[i];
            int v = cycle.cycle[(i + 1) % cycle.cycle.size()];
            // 大的編在前面
            if (u > v)
                swap(u, v);
            // 第一次遇到邊, 為它編號
            if (edgeToIndex.find({u, v}) == edgeToIndex.end())
            {
                edgeToIndex[{u, v}] = edgeIndex++;
            }
        }
    }

    // 編號完畢, 第二次遍歷 allCycles, 找出 |E| - |V| + 1 個基底
    for (const auto &weightedCycle : allCycles)
    {
        // 將 weightedCycle 轉換成 Cycle, 兩者不同在有多一個 mask
        Cycle cycle;
        cycle.nodes = weightedCycle.cycle;
        cycle.weight = weightedCycle.weight;

        // 設置 edgeMask
        for (int i = 0; i < cycle.nodes.size(); ++i)
        {
            int u = cycle.nodes[i];
            int v = cycle.nodes[(i + 1) % cycle.nodes.size()];
            if (u > v)
                swap(u, v);
            // 找出邊的對應編號
            int idx = edgeToIndex[{u, v}];
            // 設定 mask
            cycle.edgeMask.set(idx);
        }

        // 檢查線性獨立
        bool linearDep = true;
        for (const auto &basisMask : basisMasks)
        {
            // 假如 cycle 的 mask 能被組合出來, 就不是線性獨立的
            if ((cycle.edgeMask & basisMask) == cycle.edgeMask)
            {
                linearDep = false;
                break;
            }
        }

        if (linearDep)
        {
            // 加入到基底當中
            basis.push_back(cycle);
            basisMasks.push_back(cycle.edgeMask);

            for (int i = 0; i < basisMasks.size() - 1; ++i)
            {
                // and 之後的結果有 1
                if ((basisMasks[i] & cycle.edgeMask).any())
                {
                    // 都有 1 就會因為 xor 削掉
                    basisMasks[i] ^= cycle.edgeMask;
                }
            }

            if (basis.size() == targetSize)
            {
                break;
            }
        }
    }

    return basis;
}
