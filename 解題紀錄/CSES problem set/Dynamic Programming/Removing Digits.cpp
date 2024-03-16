#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mxN = 1e6;
int n, dp[mxN + 1];
int main(void)
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = 1e9;
        int i2 = i;
        while (i2)
        {
            dp[i] = min(dp[i], dp[i - i2 % 10] + 1); // 將每個位數都減看看
            i2 /= 10;
        }
    }
    cout << dp[n];
}