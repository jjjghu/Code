#include <iostream>
using namespace std;
int main(void)
{
    long long dp[51] = {0};
    dp[0] = 0, dp[1] = 1, dp[2] = 2;
    for (int i = 3; i <= 50; ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    int n;
    while (cin >> n, n)
    {
        cout << dp[n] << "\n";
    }
}
/*
動態規劃五步法
1. 構造問題: 寬度為 n 的牆壁共有幾種花樣?
2. 定義狀態: f(i) 表示寬度為 n 的牆壁共有多少花樣
3. 求解小規模的簡單問題: f(0) = 0, f(1) = 1, f(2) = 2, f(3) = 3,
4. 狀態轉移方程式: f(i) = f(i - 1) + f(i - 2)
5. 判斷複雜度: O(n)

f(4) = 5
f(5) = 8
猜測是費氏數列
...
甚麼糟糕的題目
*/