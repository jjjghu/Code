#include <iostream>
using namespace std;
#define ll long long
int main(void)
{
    int n;
    cin >> n;
    ll mx = 0, res = 0, enter;
    for (int i = 0; i < n; ++i)
    {
        cin >> enter;
        mx = max(mx, enter);
        res += mx - enter;
    }
    cout << res;
}