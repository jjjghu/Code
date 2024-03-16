// 每次撿取數字需要由小到大, 需要撿取幾次數字才能撿完所有數字?
#include <bits/stdc++.h>
using namespace std;
const int mxN = 2e5;
// int n, p[mxN + 1];
int main(void)
{
    int n;
    cin >> n;
    vector<pair<int, int>> p(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> p[i].first;
        p[i].second = i;
    }
    sort(p.begin(), p.end());
    int ans = 1;
    for (int i = 1; i < n; ++i)
    {
        if (p[i - 1].second > p[i].second) // 順序應該要大到小, 如果沒有, 表示有新的一輪
        {
            ++ans;
            cout << p[i - 1].second << " " << p[i].second << endl;
        }
    }
    cout << ans;
}