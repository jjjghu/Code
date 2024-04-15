// CSES Problem Set Array Description
#include <bits/stdc++.h>
using namespace std;
const int mxN = 1e5 + 1;
int a[mxN];
int main(void)
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    int res = 1;
    for (int i = 0; i < n; ++i)
    {
        int cur = 1;
        // find zero
        if (a[i] == 0)
        {
            // check left
            if (i - 1 >= 0 && i + 1 <= n)
            {
                cur += (a[i - 1] == a[i + 1]);
            }
        }
        // fprintf(stderr, "%d\n", cur);
        res *= cur;
    }
    cout << res << endl;
}