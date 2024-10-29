#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> nums(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> nums[i];
        }
        // 以自己為起點的遞增序列
        vector<int> LIS(n, 1);
        // 以自己為起點的遞減序列
        vector<int> LDS(n, 1);
        int result = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = n - 1; j > i; --j)
            {
                if (nums[i] < nums[j])
                    LIS[i] = max(LIS[i], LIS[j] + 1);
                if (nums[i] > nums[j])
                    LDS[i] = max(LDS[i], LDS[j] + 1);
            }
            result = max(result, LIS[i] + LDS[i] - 1);
        }
        cout << result << "\n";
    }
}
/*
動態規劃五步法
1. 構造問題:
   新的火車可以加入到現有車廂的前面或後面，或拋棄，輸出最長的遞減序列長度。

2. 定義狀態:
   LIS(i) = 從右到左看，以 index i 為起點的最長遞增子序列長度
   LDS(i) = 從左到右看，以 index i 為起點的最長遞減子序列長度

3. 求解小規模的簡單問題:
   對於所有 i，初始化 LIS(i) = 1, LDS(i) = 1

4. 狀態轉移方程式:
   LIS(i) = max(LIS(i), LIS(j) + 1 | nums[i] > nums[j] && j > i)
   LDS(i) = max(LDS(i), LDS(j) + 1 | nums[i] > nums[j] && j < i)

5. 判斷複雜度:
   時間複雜度: O(n^2)
   空間複雜度: O(n)

最終結果:
最長火車長度 = max(LIS(i) + LDS(i) - 1) 對於所有 i

*/