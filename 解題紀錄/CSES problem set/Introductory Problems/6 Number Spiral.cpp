#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define ll long long
int main(void)
{
    ll n;
    cin >> n;
    while (n--)
    {
        ll y, x;
        cin >> y >> x;
        ll z = max(y, x);
        ll z2 = (z - 1) * (z - 1), ans;
        if (z % 2) // z is even
        {
            if (z == y)
                ans = z2 + x;
            else
                ans = z2 + 2 * z - y;
        }
        else // z is odd
        {
            if (z == y)
                ans = z2 + 2 * z - x;
            else
                ans = z2 + y;
        }
        cout << ans << endl;
    }
}
