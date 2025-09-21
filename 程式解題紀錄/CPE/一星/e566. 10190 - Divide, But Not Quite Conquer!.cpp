#include <iostream>
using namespace std;
vector<int> solve(int n, int m)
{
    vector<int> res;
    while(n > 0)
    {
        res.push_back(n);
        n /= m
    }
    return res;
}
int main(void)
{
    int n, m;
    while(cin >> n >> m)
    {
        solve(n, m);
    }
}
/*
n % m until n = 1
a
*/