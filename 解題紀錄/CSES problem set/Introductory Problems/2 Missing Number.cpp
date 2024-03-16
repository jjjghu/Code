#include <iostream>
using namespace std;
#define ll long long
int main(void)
{
    ll n, s = 0;
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int a;
        cin >> a;
        s += a;
    }
    cout << n * (n + 1) / 2 - s;
}