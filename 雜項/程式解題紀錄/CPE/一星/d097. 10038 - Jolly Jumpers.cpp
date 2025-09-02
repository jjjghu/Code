#include <iostream>
#include <vector>
using namespace std;
bool solve(vector<int>& nums)
{
    int n = nums.size();
    vector<int> visited(n, false);
    for(int i = 1; i < n; ++i)
    {
        int diff = abs(nums[i] - nums[i - 1]);
        if(!visited[diff])
        {
            visited[diff] = true;
        }
        else
        {
            return false;
        }
    }
    for(int i = 1; i < n; ++i)
    {
        if(visited[i] == false)
            return false;
    }
    return true;
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
        cout << (solve(nums) ? "Jolly" : "Not jolly") << endl;
    }
}