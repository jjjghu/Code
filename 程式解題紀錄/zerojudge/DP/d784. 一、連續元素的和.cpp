#include <iostream>
#include <climits>
using namespace std;
int main(void)
{
    int t;
    cin >> t;
    int n;
    while (cin >> n)
    {
        int result = INT_MIN;
        int sum = 0;
        int num;
        for (int i = 0; i < n; ++i)
        {
            cin >> num;
            sum += num;
            result = max(result, sum);
            if (sum < 0)
                sum = 0;
        }
        cout << result << "\n";
    }
}
/*
最大子數列問題
這個問題可以用一個演算法Kadane's Algorithm解決
核心思想: 遇到數字就加入sum, 如果 sum 變成負數就另起爐灶。
*/