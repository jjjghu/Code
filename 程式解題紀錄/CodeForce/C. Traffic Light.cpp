#include <iostream>
#include <string>
using namespace std;
int solve(char current, string& s)
{
    int n = s.length();
    int mnDist = 0;
    // 現在燈號是 current，到綠燈的最遠距離是？
    for(int left = 0; left < n; ++left)
    {
        if(s[left] == current)
        {
            for(int right = left; right < 2 * n; ++right)
            {
                if(s[right % n] == 'g')
                {
                   mnDist = max(mnDist, right - left); 
                   left = right;
                   break;
                }
            }
        }
    }
    return mnDist;
}
int main(void)
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        char cur;
        string s;
        cin >> n >> cur >> s;
        cout << solve(cur, s) << endl;
    }
    return 0;
}
/*
r 
rggry
i
*/