// 給定硬幣, 輸出沒法組合出的金錢數值
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ar array
const int mxN = 2e5;
ll n, p[mxN + 1];
int main(void)
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> p[i];
    sort(p, p + n);
    ll res = 1;
    for (int i = 0; i < n; ++i)
    {
        if (res < p[i])
            break;
        else
            res += p[i];
    }
    cout << res;
}