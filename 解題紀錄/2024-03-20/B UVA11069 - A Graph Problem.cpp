// 11069 - A Graph Problem
#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    long long dp[80];
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 2;
    for (int i = 4; i < 80; ++i)
    {
        dp[i] = dp[i - 2] + dp[i - 3];
    }
    int n;
    while (cin >> n)
    {
        cout << dp[n] << endl;
    }
}