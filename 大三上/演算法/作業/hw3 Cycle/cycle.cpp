#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;
struct WeightedCycle
{
    int weight;
    vector<int> nodes;
    // cmp
    bool operator<(const WeightedCycle &other) const
    {
        return weight < other.weight;
        // return (weight == other.weight) ? nodes[0] < other.nodes[0] : weight < other.weight;
    }
};
class Solution
{
private:
    int nodeNum;
    int edgeNum;

public:
    vector<WeightedCycle> findMinimumCycleBasis(const vector<WeightedCycle> &allCycles, int nodeNum, int edgeNum)
    {
        this->nodeNum = nodeNum;
        this->edgeNum = edgeNum;

        vector<WeightedCycle> basis;
        vector<WeightedCycle> sortedCycles = allCycles;
        stable_sort(sortedCycles.begin(), sortedCycles.end());
        if (allCycles.size() <= 2)
        {
            return sortedCycles;
        }
        vector<vector<int>> basisMat;
        basis.push_back(sortedCycles[0]);
        basis.push_back(sortedCycles[1]);
        basisMat.push_back(convertToMat(sortedCycles[0].nodes));
        basisMat.push_back(convertToMat(sortedCycles[1].nodes));
        for (int i = 2; i < sortedCycles.size(); ++i)
        {
            vector<int> newCycle = convertToMat(sortedCycles[i].nodes);
            if (!canFormTarget(newCycle, basisMat))
            {
                basis.push_back(sortedCycles[i]);
                basisMat.push_back(newCycle);
                if (basisMat.size() == (edgeNum - nodeNum + 1))
                {
                    break;
                }
            }
        }
        return basis;
    }

private:
    vector<int> convertToMat(const vector<int> &nodes)
    {
        vector<vector<int>> vec(this->edgeNum, vector<int>(this->edgeNum, 0));
        for (int i = 1; i < nodes.size(); ++i)
        {
            vec[nodes[i]][nodes[i - 1]] = 1;
            vec[nodes[i - 1]][nodes[i]] = 1;
        }
        vec[nodes[0]][nodes[nodes.size() - 1]] = 1;
        vec[nodes[nodes.size() - 1]][nodes[0]] = 1;
        // 展平
        vector<int> mat;
        for (int i = 0; i < vec.size(); ++i)
        {
            for (int j = 0; j < vec.size(); ++j)
                mat.push_back(vec[i][j]);
        }
        return mat;
    }
    // bool canFormTarget(const vector<int> &newCycle, const vector<vector<int>> &basisMat)
    // {

    //     // 使用靜態變數來保存組合結果
    //     static vector<vector<int>> cachedCombined;
    //     static int cachedNumCycles = -1;
    //     // 展開所有的可能性 (span 出空間)
    //     int n = newCycle.size();
    //     int numCycles = basisMat.size();
    //     // 當 cycles 內容變化時才重新計算 cachedCombined
    //     if (numCycles != cachedNumCycles)
    //     {
    //         // 擴展 cachedCombined 容量
    //         int oldSize = cachedCombined.size();
    //         cachedCombined.resize(1 << numCycles, vector<int>(n, 0)); // 擴展大小
    //         // 計算新的 cycle 組合
    //         for (int mask = oldSize; mask < (1 << numCycles); ++mask)
    //         {
    //             for (int i = 0; i < numCycles; ++i)
    //             {
    //                 if (mask & (1 << i))
    //                 {
    //                     for (int j = 0; j < n; ++j)
    //                     {
    //                         // 對每位進行xor
    //                         cachedCombined[mask][j] ^= basisMat[i][j];
    //                     }
    //                 }
    //             }
    //         }
    //         // 更新 cachedNumCycles
    //         cachedNumCycles = numCycles;
    //     }
    //     // 檢查是否有組合等於 target
    //     for (const auto &combined : cachedCombined)
    //     {
    //         if (combined == newCycle)
    //         {
    //             return true;
    //         }
    //     }
    //     return false; // 無法合成目標
    // }
    bool canFormTarget(const vector<int> &newCycle, const vector<vector<int>> &basisMat)
    {
        // 複製一份 basisMat
        vector<vector<int>> basis = basisMat;
        int n = newCycle.size();

        // 組合目標是 newCycle
        vector<int> target = newCycle;

        // 用高斯消去法看看能不能合出目標
        for (int i = 0; i < basis.size(); ++i)
        {
            // 找到基底向量中的最高位 (leading bit), 也就是最前面的 1
            int leadIndex = -1;
            for (int j = 0; j < n; ++j)
            {
                if (basis[i][j] != 0)
                {
                    leadIndex = j;
                    break;
                }
            }

            // 如果這個基底向量能夠影響組合目標, 組合目標 -= 基底向量
            if (leadIndex != -1 && target[leadIndex] != 0)
            {
                for (int j = leadIndex; j < n; ++j)
                {
                    target[j] ^= basis[i][j];
                }
            }
        }

        // 如果消去過後依舊有 1 存在, 表示不能被 span 出來
        for (int val : target)
        {
            if (val != 0)
            {
                return false;
            }
        }
        return true;
    }
};
int main(int argc, char *argv[])
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
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
    int nodeNum, edgeNum, cost, begin, end, i, j;
    // inFile >> nodeNum >> edgeNum;
    string line;
    if (getline(inFile, line))
    {
        stringstream ss(line);
        ss >> nodeNum;
        cout << "nodeNum: " << nodeNum << endl;
    }
    int A[nodeNum][nodeNum], Cost[nodeNum][nodeNum];
    for (i = 0; i < nodeNum; i++)
        for (j = 0; j < nodeNum; j++)
            A[i][j] = 0;
    edgeNum = 0;
    while (inFile >> begin >> end >> cost)
    {
        A[begin][end] = 1;
        A[end][begin] = 1;
        Cost[begin][end] = cost;
        Cost[end][begin] = cost;
        ++edgeNum;
    }
    cout << "EdgeNum: " << edgeNum << endl;
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
    /*-----------------------------------*/
    Solution solution;
    vector<WeightedCycle> result = solution.findMinimumCycleBasis(weightedCycles, nodeNum, edgeNum);
    cout << "Minimum Cycle Basis:" << endl;
    int allweight = 0;
    for (const auto &cycle : result)
    {
        allweight += cycle.weight;
        cout << "Weight: " << cycle.weight << " => ";
        for (int node : cycle.nodes)
        {
            cout << setw(2) << node << " ";
        }
        cout << endl;
    }
    cout << "Number of cycles in basis: " << result.size() << endl;
    cout << "Expected number of cycles: " << (edgeNum - nodeNum + 1) << endl;
    cout << "All weight: " << allweight << endl;
    cout << cycle << " cycles" << endl;
    return 0;
}