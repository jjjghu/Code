#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.length(), m = s2.length();
    if (n == 0 || m == 0)
    {
        cout << "E";
        return 0;
    }
    vector<vector<string>> dp(n + 1, vector<string>(m + 1, ""));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + s1[i - 1];
            }
            else
            {
                dp[i][j] = dp[i - 1][j].length() > dp[i][j - 1].length() ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    if (dp[n][m].length() == 0)
    {
        cout << "E";
    }
    else
    {
        cout << dp[n][m];
    }
}
/*
動態規劃五步法
1. 構造問題: s1, s2 的最長共同子序列
2. 定義狀態: f(i, j) = s1[:i] 和 s2[:j] 的最長共同子序列
3. 求解小規模的簡單問題:
   f(i, 0) = ""
   f(0, j) = ""
4. 狀態轉移方程式:
    f(i, j) =
    {
        if s1[i] == s2[j] : f(i - 1, j - 1) + s1[i];
        else: 選擇 f(i - 1, j), f(i, j - 1) 比較長的
    }
5. 判斷複雜度: O(n^2)
*/