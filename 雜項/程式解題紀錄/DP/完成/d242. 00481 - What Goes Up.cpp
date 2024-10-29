#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(void)
{
    int n;
    vector<int> nums;
    while (cin >> n)
    {
        nums.push_back(n);
    }
    int N = nums.size();
    vector<int> dp(N, 0), lis;
    for (int i = 0; i < N; ++i)
    {
        auto it = lower_bound(lis.begin(), lis.end(), nums[i]);
        if (it == lis.end())
        {
            lis.push_back(nums[i]);
            dp[i] = lis.size();
        }
        else
        {
            *it = nums[i];
            dp[i] = it - lis.begin() + 1;
        }
    }
    int L = lis.size();
    cout << L << "\n-\n";

    vector<int> result;
    for (int i = N - 1; i >= 0; --i)
    {
        if (dp[i] == L)
        {
            result.push_back(nums[i]);
            --L;
        }
    }

    reverse(result.begin(), result.end());
    for (int num : result)
    {
        cout << num << "\n";
    }

    return 0;
}
/*
動態規劃五步法
1. 構造問題: 找出最長遞增子序列
2. 定義狀態: f(i) = 到 index i 為止的最長遞增子序列
3. 求解小規模的簡單問題: f(0) = 1
4. 狀態轉移方程式:
    f(i) = max( f(j) + 1 | nums[i] > nums[j])
    (如果 nums[i] > nums[j], 那麼 f(j) + 1 就是預備答案之一, 最後要找最大的)
5. 判斷複雜度: O(n^2)

耐心排序
nums = {3, 4, 2, 1, 10}, dp = {0, 0, 0, 0, 0}, lis = {}
當有新的數字加入, 找到它的 lowerbound 位置, 如果是最大, 就加入尾端, 否則取代該位置
3 加入: dp = {1, 0, 0, 0, 0}, lis = {3}
4 加入: dp = {1, 1, 0, 0, 0}, lis = {3, 4}
2 加入: dp = {1, 2, 0, 0, 0}, lis = {2, 4}
1 加入: dp = {1, 2, 0, 0, 0}, lis = {1, 4}
10加入: dp = {1, 2, 0, 0, 3}, lis = {1, 4, 10}
上面的 lis 這時就沒有用了, 因為它只用來建立 dp
還原真正的解答 ans, 現在有 dp 的資訊, 用它來反推結果,
*/