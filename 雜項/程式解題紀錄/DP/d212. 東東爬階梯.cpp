#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
    vector<long long> dp(100, 0);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i < 100; ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    int n;
    while (cin >> n)
        cout << dp[n] << endl;
}
/*
動態規劃五步法
1. 構造問題: 每一步爬 1 或 2 步, 爬到階梯 n 的方法數共有幾種?
2. 定義狀態: f(i) 表示爬到 i 的方法數
3. 求解小規模的簡單問題: f(0) = 1, f(1) = 1
4. 狀態轉移方程式: f(i) = f(i - 1) + f(i - 2);
5. 判斷複雜度: O(n)
*/