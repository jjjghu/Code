#include <iostream>
#include <climits>
using namespace std;
int main(void)
{
    int n;
    while (cin >> n, n != 0)
    {
        int result = INT_MIN;
        int sum = 0;
        int num;
        for (int i = 0; i < n; ++i)
        {
            cin >> num;
            sum += num;
            if (sum < 0)
                sum = 0;
            result = max(result, sum);
        }
        if (result)
        {
            cout << "The maximum winning streak is ";
            cout << result << ".\n";
        }
        else
        {
            cout << "Losing streak.\n";
        }
    }
}
/*
這不是 dp, 使用 Kadane's Algorithm
*/