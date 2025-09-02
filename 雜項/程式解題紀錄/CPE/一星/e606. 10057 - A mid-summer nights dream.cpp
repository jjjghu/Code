#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> solve(vector<int>& nums)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());

    int midL = nums[(n - 1) / 2];
    int midR = nums[n / 2];
    int cnt = 0;
    for(int x : nums)
    {
        cnt += x == midL || x == midR;
    }

    return {midL, cnt, midR - midL + 1};
}
int main(void)
{
    int n;
    while(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; ++i)
        {
            cin >> nums[i];
        }
        vector<int> res = solve(nums);
        cout << res[0] << " " << res[1] << " " << res[2] << endl;
    }
}