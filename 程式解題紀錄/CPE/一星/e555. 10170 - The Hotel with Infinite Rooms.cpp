#include <iostream>
using namespace std;
long long solve(long long s, long long d)
{
    // Might TLE but try it first
    while(d > s)
    {
        d -= s;
        ++s;
    }
    return s;
}
int main(void)
{
    long long s, d;
    while(cin >> s >> d)
    {
        cout << solve(s, d) << endl;
    }
}
/*
(2s + n) * n / 2
(2s + n + 1) * n + 1 / 2

s d
10 1

1 + 2 + 3 = 6
 */