#include <iostream>
using namespace std;
int cycle(int num)
{
    int step = 1;
    while(num != 1)
    {
        if(num % 2 == 0)
        {
            num /= 2;
        }
        else
        {
            num = 3 * num + 1;
        }
        ++step;
    }
    return step;
}
int solve(int left, int right)
{
    if(left > right)
    swap(left, right);
    int res = 1;
    for(int i = left; i <= right; ++i)
    {
        res = max(res, cycle(i));
    }
    return res;
}
int main(void)
{
    int left, right;
    while(cin >> left >> right)
    {
        printf("%d %d %d\n", left, right, solve(left, right));
    }
    return 0;
}