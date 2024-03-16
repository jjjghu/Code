#include <iostream>
using namespace std;
#define ll long long
const ll MOD = 1e9 + 7;
ll fast_power(ll base, ll power) // 快速冪, 這三小?
{
    ll res = 1;
    base %= MOD;
    while (power > 0)
    {
        if (power & 1) // 遇到 1
            res = (res * base) % MOD; // 加入當前位數冪次
        base = (base * base) % MOD; // 次方加倍, x, x^2, x^4
        power >>= 1; // 需要的次方除2 (已經加入 res 當中)
    }
    return res;
}
ll solve(ll n)
{
    ll total = fast_power(4, n);
    ll d = fast_power(2, n);
    // 不能回傳  / 2, 需要 乘上 2 的反元素 (MOD = 1e9+7)
    return ((total + d) % MOD * fast_power(2, MOD - 2)) % MOD;
}
int main(void)
{
    ll n;
    cin >> n;
    cout << solve(n) << endl;
}
/*
NextUp = 3*up + down;
NextDown = 3*down + up;

差距 d = up - down
Nextd = NextUp - NextDown = (3*up+down) - ( 3 * down + up) = 2up -2down = 2d

Nextd = 2d

獲取 up => (Total + d) / 2, (Up + down + up - down)/2 = up

Total = 4^n // 每次一塊分裂成四塊
 diff = 2^n // 每次差距多兩倍

因為要MOD, 所以 / 2 要轉換為 2 的乘法反元素

MOD = 1e9+7是質數, 2 小於 MOD
依據費馬小定理
2*x === 1 MOD(1e9+7)
a^(1e9+7-1) ≡ 1 MOD(1e9+7)
a*a^(1e9+7-2) ≡ 1 MOD(1e9+7)

2*2^(1e9+7-2) ≡ 1 MOD(1e9+7)
2 的反元素 = 2^(1e9+7-2)
*/