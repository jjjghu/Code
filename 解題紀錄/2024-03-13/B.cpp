// UVA 10976 Fraction Again?!
#include <iostream>
#include <vector>
using namespace std;
vector<pair<int, int>> solve(int k)
{
    vector<pair<int, int>> res;          // 記錄所有答案
    for (int x = k + 1; x <= 2 * k; ++x) // 從比 k 大的地方開始解, 才能確保最後分數不會大於 1/k, 一直到分水嶺 2k
    {
        if (k * x % (x - k) == 0) // 求得對應 y, 確保是整數
        {
            int y = k * x / (x - k);
            res.push_back(make_pair(x, y)); // 加入對應解
        }
    }
    return res;
}

int main()
{
    int k;
    while (cin >> k)
    {
        vector<pair<int, int>> res = solve(k);
        cout << res.size() << endl;
        for (pair<int, int> &r : res)
        {
            cout << "1/" << k << " = "
                 << "1/" << r.second << " + 1/" << r.first << endl;
        }
    }
    return 0;
}
/*
分割後面的兩個分母 x y 必定有一種是 k*2 k*2的樣式, 將其當作分水嶺
*/