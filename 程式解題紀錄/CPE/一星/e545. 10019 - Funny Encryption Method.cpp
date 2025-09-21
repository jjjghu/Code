#include <iostream>
using namespace std;

int binary(int num)
{
    int res = 0;
    while(num > 0)
    {
        res += num & 1;
        num >>= 1;
    }
    return res;
}
pair<int,int> solve(int num)
{
    int b1 = binary(num);
    int b2 = 0;
    while(num > 0)
    {
        b2 += binary(num % 10);
        num /= 10;
    }
    return {b1, b2};
}
int main(void)
{
    int n, t;
    cin >> t;
    while(cin >> n)
    {
        cout << solve(n).first << " " << solve(n).second << endl;
    }
}