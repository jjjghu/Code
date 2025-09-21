#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;
void solve(vector<int>& nums, int x) 
{
    int n = nums.size();
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        // 係數 * 冪次
        res += nums[i] * (n - i);
        // 最後一項以外，都 * x
        if(i < n - 1){
            res *= x;
        }
    }
    cout << res << endl;
    return;
}
int main(void)
{
    int x;
    string s;
    while(cin >> x)
    {
        cin.ignore();
        getline(cin, s);
        stringstream ss(s);
        vector<int> nums;
        while(ss >> s) 
        {
            nums.push_back(stoi(s));
        }
        nums.pop_back();
        solve(nums, x);
    }
} 
/*
1 1 1 -> 1 1 = (x^2 + x)'
 */