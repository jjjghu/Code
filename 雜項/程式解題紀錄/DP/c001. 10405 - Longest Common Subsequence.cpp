#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
    string sa, sb;
    while (cin >> sa >> sb)
    {
        int n = sa.size(), m = sb.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (sa[i - 1] == sb[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        cout << dp[n][m] << "\n";
    }
}
/*
動態規劃五步法
1. 構造問題: 求解兩個字串 sa, sb 的最長共同子序列
2. 定義狀態: f(i, j) 表示 sa 的前 i 個字元和 sb 的前 j 個字元的最長共同子序列長度
3. 求解小規模的簡單問題:
    f(0, j) = 0 (for all j)
    f(i, 0) = 0 (for all i)
4. 狀態轉移方程式:
    f(i, j) =
    {
        sa[i] != sb[j]: max(f(i, j - 1), f(i - 1, j))
        sa[i] == sb[j]: f(i - 1, j - 1) + 1
    }
5. 判斷複雜度: O(n * m) n = sa.size(), m = sb.size();
*/