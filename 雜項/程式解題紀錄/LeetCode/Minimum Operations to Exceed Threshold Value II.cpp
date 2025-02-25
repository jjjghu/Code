#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minOperations(vector<int> &nums, int k)
    {
        long long total = accumulate(nums.begin(), nums.end(), 0LL);
        if (total >= k)
            return 0;

        priority_queue<long long, vector<long long>, greater<long long>> pq;
        for (int num : nums)
            pq.push(num);

        int operations = 0;

        while (pq.size() >= 2 && total < k)
        {
            long long smallest = pq.top();
            pq.pop();
            long long second = pq.top();
            pq.pop();

            long long merged = smallest * 2 + second;
            pq.push(merged);

            // 更新總和：減去被合併的兩個數，加上新數
            total = total - smallest - second + merged;
            operations++;
        }

        return total >= k ? operations : -1; // 根據題目假設可能需要返回-1表示不可能
    }
};