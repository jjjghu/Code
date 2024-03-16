// UVA 11150 Cola
#include <iostream>
#include <algorithm>
using namespace std;
int n;
int main(void)
{
    while (cin >> n)
    {
        int res = n;
        while (n >= 3)
        {
            res += n / 3;
            n = n / 3 + n % 3;
        }
        if (n == 2) // 只有這樣的情況才還的回去
            ++res;
        cout << res << endl;
    }
}
/*
解法 2: *1.5 倍
    while (cin >> n)
    {
        cout << n * 3 / 2 << endl;
    }
每次 n 都 / 3
res = n + n/3 + n/9 + n/81 + ...
res = n(1-0(無限小視為0)) / 1-1 / 3 = n*1.5
*/