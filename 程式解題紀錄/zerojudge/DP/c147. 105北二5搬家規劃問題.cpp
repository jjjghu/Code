#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
int main(void)
{
    int mx;
    vector<int> weight, value;
    string s;
    stringstream ss;

    getline(cin, s);
    ss.clear();
    ss.str(s);
    while (ss >> s)
    {
        weight.push_back(stoi(s));
    }
    getline(cin, s);
    ss.clear();
    ss.str(s);
    while (ss >> s)
    {
        value.push_back(stoi(s));
    }
    cin >> mx;

    int n = weight.size();
    vector<int> dp(mx + 1, 0);
    // vector<vector<int>> dp(n + 1, vector<int>(mx + 1, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = mx; j >= weight[i]; --j)
        {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
        // for (int j = 0; j <= mx; ++j)
        // {
        //     dp[i][j] = dp[i - 1][j];
        //     if (j >= weight[i - 1])
        //     {
        //         dp[i][j] = max(dp[i][j], dp[i - 1][j - weight[i - 1]] + value[i - 1]);
        //     }
        // }
    }
    cout << dp[mx] << "\n";
    // cout << dp[n][mx] << "\n";
}

/*
動態規劃五步法
1. 構造問題: 在重量限制下找出最佳的價值組合
2. 定義狀態: f(i, j) = 前 i 個物品, 重量 j 的最高價值
3. 求解小規模的簡單問題:
    f(0, j) = 0
    f(i, 0) = 0
4. 狀態轉移方程式:
    f(i, j) =
    {
        不選擇: f(i - 1, j)
        選擇: f(i - 1, j - weight[i - 1]) + value[i - 1]
    }
5. 判斷複雜度: O(n *  mx)

因為每次都只需要前一行的資訊, 而自己就可以扮演前一行, 所以能夠壓縮到一維。

1. 構造問題: 在重量限制下找出最佳的價值組合
2. 定義狀態: dp[j] = 重量 j 的最高價值
3. 求解小規模的簡單問題:
    dp[0] = 0
4. 狀態轉移方程式:
    每一輪都加入新的貨物, 更新一遍
    dp[j] = max(dp[j], dp[j - weight[i]] + value[i])
5. 判斷複雜度: O(n * mx)
*/