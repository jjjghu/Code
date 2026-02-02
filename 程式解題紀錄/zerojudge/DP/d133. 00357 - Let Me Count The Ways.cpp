#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
    vector<int> coins = {1, 5, 10, 25, 50};
    int n;
    while (cin >> n)
    {
        vector<long long> dp(n + 1);
        dp[0] = 1;
        for (const int &coin : coins)
        {
            for (int i = coin; i <= n; ++i)
            {
                dp[i] += dp[i - coin];
            }
        }
        if (dp[n] != 1)
        {
            cout << "There are " << dp[n] << " ways to produce " << n << " cents change.\n";
        }
        else
        {
            cout << "There is only 1 way to produce " << n << " cents change.\n";
        }
    }
}
/*
動態規劃五步法
1. 構造問題: n 有幾種湊法?
2. 定義狀態: f(i) = 方法數
3. 求解小規模的簡單問題:
   f(0) = 1
4. 狀態轉移方程式:
   coins = {1, 5, 10, 25, 50}, coin 為其中任意一個
   f(i) = f(i - coin)
5. 判斷複雜度: O(n * m)
*/