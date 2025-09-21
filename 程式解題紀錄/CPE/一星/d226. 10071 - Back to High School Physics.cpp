#include <iostream>
using namespace std;
int main(void)
{
    int v,t;
    while(cin >> v >> t)
    {
        cout << 2 * v * t << endl;
    }
}
// 1/2 * (v/t) * (2t)^2
// 2 * v * t