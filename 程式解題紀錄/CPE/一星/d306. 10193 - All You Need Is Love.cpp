#include <iostream>
#include <algorithm>
using namespace std;
int convert(string& s)
{
    int res = 0;
    for(int i = 0; i < s.length(); ++i)
    {
        res <<= 1;
        res += s[i] - '0';
    }
    return res;
}
bool solve(string& a, string& b)
{
    int x = convert(a);
    int y = convert(b);
    if(__gcd(x, y) > 1)
        return true;
    else
        return false;
}
int main(void)
{
    int n;
    cin >> n;
    string a, b;
    int t = 0;
    while(cin >> a >> b)
    {
        bool res = solve(a, b);
        ++t;
        if(res)
        {
            printf("Pair #%d: All you need is love!\n", t);
        }
        else
        {
            printf("Pair #%d: Love is not all you need!\n", t);
        }
    }
    return 0;
}