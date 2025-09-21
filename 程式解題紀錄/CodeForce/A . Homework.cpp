#include <iostream>
#include <string>
using namespace std;
string solve(string& a, string& b, string& order)
{
    int n = order.length();
    for(int i = 0; i < n; ++i)
    {
        if(order[i] == 'D') {
            a += b[i];
        }
        else {
            a = b[i] + a;
        }
    }
    return a;
}
int main(void)
{
    int t, n;
    cin >> t;
    while(t--)
    {
        string a, b, order;
        cin >> n >> a;
        cin >> n >> b;
        cin >> order;
        cout << solve(a, b, order) << endl;
    }
}
// 800