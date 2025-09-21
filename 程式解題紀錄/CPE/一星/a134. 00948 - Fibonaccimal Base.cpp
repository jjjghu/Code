#include <iostream>
#include <vector>
using namespace std;
vector<int> base = {1, 2};
void init()
{
    int a = 1, b = 2;
    while(a + b <= 1e9)
    {
        base.push_back(a + b);
        a = a + b;
        swap(a, b);
    }
}
string solve(int num)
{
    int n = base.size() - 1;

    string res;
    bool started = false;
    for(int i = n - 1; i >= 0; --i)
    {
        if(num >= base[i])
        {
            num -= base[i];
            res += '1';
            started = true;
        }
        else if(started)
        {
            // 消滅前導 0 
            res += '0';
        }
    }
    return res;
}
int main(void)
{
    init();
    int n, num;
    cin >> n;
    while(cin >> num)
    {
        cout << num << " = " << solve(num) << " (fib)\n";
    }
    return 0;
}