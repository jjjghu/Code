// UVA 10162 Last Digit
#include <bits/stdc++.h>
using namespace std;
int solve(int n)
{
    vector<vector<int>> list =
        {
            {0},
            {1},
            {2, 4, 8, 6},
            {3, 9, 7, 1},
            {4, 6},
            {5},
            {6},
            {7, 9, 3, 1},
            {8, 4, 2, 6},
            {9, 1}};

    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        int last = i % 10;
        int len = list[last].size();
        int pos = i % len;

        pos = (pos - 1 + len) % len;
        res += list[last][pos];
        res %= 10;
    }

    return res;
}

int main()
{
    string s;
    int n;
    while (cin >> s)
    {
        // get last four digit and convert to int
        n = stoi(s.substr(max(0, (int)s.size() - 5)));
        if (n == 0)
            return 0;
        cout << solve(n) << endl;
    }
}