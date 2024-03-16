// 給定 n 個棍子, 求出最少需要調整多少才能使所有棍子長度相同,
// 每次調整可加可減
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ar array
const int mxN = 2e5;
int n, p[mxN];
int main(void)
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> p[i];
    sort(p, p + n);
    ll x = p[n / 2]; // 獲取中位數
    ll ans = 0;
    for (int i = 0; i < n; ++i)
        ans += abs(p[i] - x);
    cout << ans; // 計算並輸出答案
}