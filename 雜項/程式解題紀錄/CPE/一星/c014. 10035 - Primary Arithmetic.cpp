#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int solve(string s1, string s2)
{
    int res = 0, carry = 0;
    
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    
    int n = max(s1.length(), s2.length());
    while(s1.length() < n) s1.push_back('0');
    while(s2.length() < n) s2.push_back('0');

    for(int i = 0; i < n; ++i)
    {
        int current = (s1[i] - '0') + (s2[i] - '0') + carry;
        if(current <= 9)
        {
            carry = 0;
        }
        else
        {
            carry = 1;
            ++res;
        }
    }
    return res;
}
int main(void)
{
    string a, b;
    while(cin >> a >> b)
    {
        if(a == "0" && b == "0")
            break;

        int res = solve(a, b);
        if(res == 0)
        {
            cout << "No carry operation." << endl;
        }
        else if(res == 1)
        {
            cout << "1 carry operation." << endl;
        }
        else
        {
            cout << res << " carry operations." << endl;
        }
    }
    return 0;
}