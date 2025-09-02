#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MX = 1e6+1;
bool isPrime[MX];
auto init = []{
    fill(begin(isPrime), end(isPrime), true);
    for(int i = 2; i < MX; ++i)
    {
        if(isPrime[i])
        {
            for(int j = 2 * i; j < MX; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
    return 0;
}();

int rev(int n)
{
    int res = 0;
    while(n) 
    {
        res *= 10;
        res += n % 10;
        n /= 10;
    }
    return res;
}

int main(void)
{
    int n;
    while(cin >> n)
    {
        int revN = rev(n);
        if(n != revN && isPrime[n] && isPrime[revN])
        {
            cout << n << " is emirp.\n";
        }
        else if(isPrime[n])
        {
            cout << n << " is prime.\n";
        }
        else 
        {
            cout << n << " is not prime.\n";
        }
    }  
    return 0;
}
/*

*/