#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(void)
{
    int n;
    while (cin >> n, n)
    {
        vector<int> nums(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> nums[i];
        }
        vector<vector<int>> dp(n, vector<int>(3, 0));
        dp[0][0] = 0;           // 不跑
        dp[0][1] = nums[0];     // 正常跑
        dp[0][2] = nums[0] * 2; // 加速
        for (int i = 1; i < n; ++i)
        {
            dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][1], dp[i - 1][2]));
            dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) + nums[i];
            dp[i][2] = max(dp[i - 1][0], dp[i - 1][1]) + nums[i] * 2;
        }
        cout << max(dp[n - 1][0], max(dp[n - 1][1], dp[n - 1][2])) << "\n";
    }
}
/*
每次跑步可以選擇加速，如果加速，本次得分 * 2, 但下一個跑道分數歸零
動態規劃五步法
1. 構造問題: 跑步的最高得分
2. 定義狀態: f(i, state), 表示當前跑到第 i 個跑道,選擇 state 的最高得分
3. 求解小規模的簡單問題:
    f(0, 不跑) = 0
    f(0, 跑) = nums[0];
    f(0, 加速) = nums[0] * 2;
4. 狀態轉移方程式:
    f(i, 不跑) = max(f(i - 1, 不跑), f(i - 1, 跑), f(i - 1, 加速))
    f(i, 跑) = max(f(i - 1, 不跑), f(i - 1, 跑)) + nums[i];
    f(i, 加速) = max(f(i - 1, 不跑), f(i - 1, 跑)) + nums[i] * 2;
5. 判斷複雜度: O(n)
*/