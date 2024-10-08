#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
void solve(int n)
{
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i == 1)
            {
                dp[i][j] = 1;
            }
            else if (i > j)
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }
    cout << dp[n][n] << "\n";
}
int main(void)
{
    int n;
    while (cin >> n)
    {
        solve(n);
    }
}
/*
動態規劃五步法
1. 構造題目: n 步上, n 步下, 爬山的走法共有幾種?
2. 定義狀態: f(n) = 到第 2n 步的走法數量... 推論失敗, 使用二維
   f(i, j) = 限制最高高度 i, 步伐數量 2j, 有幾種走法?
3. 求解小規模的簡單問題:
    f(0,0) = 0
    f(1, 1) = 1, f(1, 2) = 1, f(1, 3) = 1, f(1, 4) = 1
    f(2, 1) = X, f(2, 2) = 2, f(2, 3) = 3, f(2, 4) = 4;
    f(3, 1) = X, f(3, 2) = X, f(3, 3) = 5, f(3, 4) = 9
4. 狀態轉移方程式:
    推論得出: f(i, j) =
    {
        i == 1: f(i, j) = 1
        i > j : f(i, j) = f(i - 1, j)
        其他: f(i - 1, j) + f(i, j - 1)
    }
5. 判斷複雜度: O(n)
*/