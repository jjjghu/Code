#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
    int t;
    cin >> t;
    vector<int> res;
    while(t--)
    {
        long long n;
        cin >> n;

        long long d = 11;
        vector<long long> res;
        while(n >= d)
        {
            if(n % d == 0)
            {
                res.push_back(n / d);
            }
            d = (d - 1) * 10 + 1;
        }
        cout << res.size() << endl;
        for(int i = res.size() - 1; i >= 0; --i)
        {
            cout << res[i] << ' ';
        }
        cout << endl;
    }
    return 0;
}
// y = x append 0 
// n = x + y
// give, n

// n = x + 10^m(x)
// n = x (1 + 10^m)

// n / x = 1 + 10^m
// n / (1000...1) = x