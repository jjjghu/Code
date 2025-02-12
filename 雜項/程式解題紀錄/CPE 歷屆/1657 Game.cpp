#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<pair<int, int>> table;
        unordered_map<int, int> sum_mp, product_mp;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = i + 1; j <= n; ++j)
            {
                table.emplace_back(i, j);
                sum_mp[i + j]++;
                product_mp[i * j]++;
            }
        }
        vector<bool> useable(table.size(), true);

        // 每次不知道都篩選掉某些 pair
        for (int i = 0; i < m; ++i)
        {
            for (auto it = table.begin(); it != table.end(); ++it)
            {
                if (!(useable[it - table.begin()]))
                    continue;
                int sum = it->first + it->second;
                int product = it->first * it->second;
                if (i & 1)
                {
                    if (product_mp[product] <= 1)
                    {
                        product_mp.erase(product);
                        sum_mp[sum]--;
                        useable[it - table.begin()] = false;
                    }
                }
                else
                {
                    if (sum_mp[sum] <= 1)
                    {
                        sum_mp.erase(sum);
                        product_mp[product]--;
                        useable[it - table.begin()] = false;
                    }
                }
            }
        }
        
        // 紀錄留下的 pair, 輸出
        vector<pair<int, int>> res;
        if (m & 1)
        {
            for (int i = 0; i < table.size(); ++i)
            {
                pair<int, int> &p = table[i];
                if (!useable[i])
                    continue;
                if (product_mp[p.first * p.second] == 1)
                {
                    res.push_back(p);
                }
            }
        }
        else
        {
            for (int i = 0; i < table.size(); ++i)
            {
                pair<int, int> &p = table[i];
                if (!useable[i])
                    continue;
                if (sum_mp[p.first + p.second] == 1)
                {
                    res.push_back(p);
                }
            }
        }

        cout << res.size() << endl;
        for (const auto &p : res)
        {
            cout << p.first << " " << p.second << endl;
        }
    }
}