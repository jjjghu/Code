#include <iostream>
#include <vector>
#include <functional>
#include <algorithm> // for swap

using namespace std;

class Solution
{
public:
    vector<int> sortArray(vector<int> &nums)
    {
        function<void(int, int)> quickSort = [&](int left, int right) -> void
        {
            if (left >= right)
            {
                return;
            }
            int i = left - 1, j = right + 1;
            // 使用固定的 pivot
            int pivotIndex = right; // 取右邊界作為 pivot
            int pivotValue = nums[pivotIndex];
            cout << "Pivot: " << pivotValue << " (from index " << pivotIndex << ")\n"; // 打印基準點

            while (i < j)
            {
                do
                {
                    ++i;
                } while (nums[i] < pivotValue);
                do
                {
                    --j;
                } while (pivotValue < nums[j]);
                if (i < j)
                {
                    swap(nums[i], nums[j]);
                }
            }
            // 打印當前狀態
            cout << "Current array state: ";
            for (int k = 0; k < nums.size(); ++k)
            {
                cout << nums[k] << " ";
            }
            cout << endl;

            quickSort(left, j);
            quickSort(j + 1, right);
        };
        quickSort(0, nums.size() - 1);
        return nums;
    }
};

int main()
{
    Solution solution;
    vector<int> nums = {5, 7, 6, 3, 4, 2, 8, 1};
    vector<int> sortedArray = solution.sortArray(nums);

    cout << "Sorted array: ";
    for (int num : sortedArray)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
