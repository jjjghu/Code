#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
    int t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        vector<int> nums(n);
        int sum = 0;

        for (int i = 0; i < n; ++i)
        {
            cin >> nums[i];
            sum += nums[i];
        }

        int half = sum / 2;
        vector<bool> dp(half + 1, false);
        dp[0] = true;

        for (int num : nums)
        {
            for (int j = half; j >= num; --j)
            {
                dp[j] = dp[j] || dp[j - num];
            }
        }

        for (int j = half; j >= 0; --j)
        {
            if (dp[j])
            {
                int sum1 = j;
                int sum2 = sum - j;
                cout << abs(sum1 - sum2) << endl;
                break;
            }
        }
    }
}

/*
動態規劃五步法
1. 構造問題: 把硬幣盡量平均分配
2. 定義狀態: f(i) = 能不能湊出 i
3. 求解小規模的簡單問題:
    f(i) = true
    其他 f(i) = false
4. 狀態轉移方程式:
   若 f(i) = true, 則 f(i + num) = true
5. 判斷複雜度: O(n * sum / 2)
*/
