#include <iostream>
#include <vector>
using namespace std;
int solve(vector<int>& nums)
{
    int n = nums.size();
    int cnt = 0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = i + 1; j < n; ++j)
        {
            if(nums[i] > nums[j])
            {
                swap(nums[i], nums[j]);
                ++cnt;
            }
        }
    }
    return cnt;
}
int main(void)
{
    int t, n;
    cin >> t;
    while(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; ++i)
        {
            cin >> nums[i];
        }
        int res = solve(nums);
        printf("Optimal train swapping takes %d swaps.\n", res);
    }
    return 0;
}   