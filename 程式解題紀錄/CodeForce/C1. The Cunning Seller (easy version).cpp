#include <iostream>
#include <vector>
using namespace std;

vector<long long> powerOf3;

auto init = []{
    long long cur = 1;
    powerOf3.push_back(cur);
    for(int i = 0; i < 30; ++i)
    {
        cur *= 3;
        powerOf3.push_back(cur);
    }
    return 0;
}();

void solve(int num)
{
    long long cost = (num % 3) * 3;
    num /= 3;

    int index = 1;
    while(num)
    {
        cost += (num % 3) * (powerOf3[index + 1] + index * powerOf3[index - 1]);
        num /= 3;
        ++index;
    }
    cout << cost << endl;
    return;
}
int main(void)
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        solve(n);
    }
}
/*
買 2010 (三進位) 個西瓜，代表需要花費
3^2 + 1 * 3^0
3^4 + 3 * 3^2
 */