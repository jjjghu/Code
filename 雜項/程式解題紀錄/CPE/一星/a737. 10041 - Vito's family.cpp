#include <iostream>
#include <algorithm>
using namespace std;
int main(void)
{
    int t, n;
    cin >> t;
    while(cin >> n)
    {
        int nums[n];
        for(int i = 0; i < n; ++i)
        {
            cin >> nums[i];
        }
        sort(nums, nums + n);
        int sum = 0;
        for(int i = 0; i < n; ++i)
        {
            sum += abs(nums[i] - nums[n / 2]);
        }
        cout << sum << endl;
    }
    return 0;
}