// UVA 374 Big Mod
#include <iostream>
using namespace std;
#define ll long long
ll fast_power(ll base, ll power, ll mod)
{
    ll res = 1;
    while (power)
    {
        if (power & 1)
        {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        power >>= 1;
    }
    return res;
}
int main(void)
{
    int b, p, m;
    while (cin >> b >> p >> m)
    {
        cout << fast_power(b, p, m) << endl;
    }
}