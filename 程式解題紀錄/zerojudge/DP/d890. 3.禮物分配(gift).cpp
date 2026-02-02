#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(void)
{
    int n, k, sum = 0;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
        sum += nums[i];
    }
    // 要分成兩堆
    int half = sum / 2;
    vector<bool> dp(half + 1, false);
    dp[0] = true;
    for (int i = 0; i < n; ++i)
    {
        for (int j = half; j >= nums[i]; --j)
        {
            dp[j] = dp[j - nums[i]];
        }
    }
    for (int j = half; j >= 0; --j)
    {
        if (dp[j])
        {
            int sum1 = j;
            int sum2 = sum - j;
            cout << min(sum1, sum2) << " " << max(sum1, sum2) << endl;
            break;
        }
    }
}

/*
動態規劃五步法
1. 構造問題: 把禮物盡量平均分配
2. 定義狀態: f(價格) = 能不能湊出來
3. 求解小規模的簡單問題:
    f(0)   = true
    f(sum) = true
4. 狀態轉移方程式:
   若 f(i) = true, f(i + num) = true
   反過來說 f(i) = true, f(i - num) = true
5. 判斷複雜度: O(n * sum / 2)
*/