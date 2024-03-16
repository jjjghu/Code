#include <iostream>
using namespace std;
int main(void)
{
    string s;
    cin >> s;
    int res = 1, combo = 1;
    for (int i = 0; i < s.length() - 1; ++i)
    {
        if (s[i] == s[i + 1])
        {
            ++combo;
            res = max(res, combo);
        }
        else
            combo = 1;
    }
    cout << res << endl;
}