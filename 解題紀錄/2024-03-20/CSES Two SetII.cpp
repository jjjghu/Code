// Two Set II
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int main(void)
{
    int n;
    cin >> n;
    int target = (n * (n + 1)) / 2;
    // 總和奇數, 不可能被分成兩組
    if (target & 1)
    {
        cout << 0;
        return 0;
    }
    // 需要找到 target 共有幾種組合方式, 只需要組合一邊, 另一邊自己會成形
    target /= 2;
    vector<vector<int>> dp(n, vector<int>(target + 1));
    // dp[maxNum][curTar] = 使用 1 ~ maxNum 組合出 curTar 的方法數
    // 初始狀態
    dp[0][0] = 1;
    // 當前最大數字
    for (int maxNum = 1; maxNum < n; ++maxNum)
    {
        // 當前目標
        for (int curTar = 0; curTar <= target; ++curTar)
        {
            // 複製上排
            dp[maxNum][curTar] += dp[maxNum - 1][curTar];
            // 如果當前目標 > 當前最大數字
            if (curTar >= maxNum)
            {
                // 代表可能性增加, 小目標dp[maxNum-1][curTar-maxNum]加入當前最大數字(多了maxNum這個選擇)就能合成出curTar
                dp[maxNum][curTar] += dp[maxNum-1][curTar - maxNum];
            }
            dp[maxNum][curTar] %= MOD;
        }
    }
    cout << dp[n - 1][target];
}
