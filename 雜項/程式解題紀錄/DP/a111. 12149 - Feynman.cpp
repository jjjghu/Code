#include <iostream>
using namespace std;
int main(void)
{
    long long dp[101] = {0};
    dp[0] = 0, dp[1] = 1;
    for (int i = 2; i <= 100; ++i)
    {
        dp[i] = dp[i - 1] + i * i;
    }
    int n;
    while (cin >> n, n)
    {
        cout << dp[n] << "\n";
    }
}
/*
動態規劃五步法
1. 構造問題: 對於一個邊長n * n 的正方形, 裡面有多少個小正方形?
2. 定義狀態: f(i) 表示 i * i 共有多少正方形
3. 求解小規模的簡單問題: f(0) = 0, f(1) = 1, f(2) = 5
4. 狀態轉移方程式: f(i) = i * i + f(i - 1)
5. 判斷複雜度: O(n)
*/