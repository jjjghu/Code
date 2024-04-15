#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, a, b;
    cin >> n >> a >> b;
    vector<vector<double>> dp(n + 1, vector<double>(b - a + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = a; j <= b; j++)
        {
            dp[i][j - a] = dp[i - 1][j - 1] * (1.0 / 6) + dp[i - 1][j] * (1.0 / 6);
        }
    }
    cout << fixed << setprecision(6) << dp[n][b - a] << endl;
}