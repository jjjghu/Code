#include <iostream>
using namespace std;
int main()
{
    int sum, feet;
    while (cin >> sum >> feet)
    {
        if (feet % 2 & 1)
        {
            cout << "no solution\n";
            continue;
        }
        int y = (feet / 2) - sum;
        int x = sum - y;
        if (x < 0 || y < 0)
        {
            cout << "no solution\n";
        }
        else
        {
            cout << x << " " << y << "\n";
        }
    }
}