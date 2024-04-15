// CSES Coin Combinations II
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mxN = 100, mxX = 1e6, M = 1e9 + 7;
int n, coin[mxN], x;
ll dp[mxX + 1];
int main(void)
{
    int n, x;
    cin >> n >> x;
    for (int i = 0; i < n; ++i)
        cin >> coin[i];
    dp[0] = 1;
    for (int j = 0; j < n; ++j)
    {
        for (int i = 1; i <= x; ++i)
        {
            if (coin[j] <= i)
            {
                dp[i] = (dp[i] + dp[i - coin[j]]) % M;
            }
        }
    }
    cout << dp[x];
}
