#include <iostream>
using namespace std;
#define ll long long
int main(void)
{
    ll n;
    cin >> n;
    cout << n << " ";
    while (n != 1)
    {
        if (n & 1)
            n = n * 3 + 1;
        else
            n /= 2;
        cout << n << " ";
    }
}