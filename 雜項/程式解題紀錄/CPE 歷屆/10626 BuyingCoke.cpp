#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class Solution
{
private:
    int coke;
    int one;
    int five;
    int ten;
    vector<vector<vector<int>>> dp;
    int buy(int coke, int one, int five, int ten)
    {
        if (coke == 0)
            return 0;
        if (dp[one][five][ten] != 0)
            return dp[one][five][ten];
        dp[one][five][ten] = 2147483647;
        // 10
        if (ten >= 1)
            dp[one][five][ten] = min(dp[one][five][ten], buy(coke - 1, one + 2, five, ten - 1) + 1);
        // 13
        if (one >= 3 && ten >= 1)
            dp[one][five][ten] = min(dp[one][five][ten], buy(coke - 1, one - 3, five + 1, ten - 1) + 4);
        // 10
        if (five >= 2)
            dp[one][five][ten] = min(dp[one][five][ten], buy(coke - 1, one + 2, five - 2, ten) + 2);
        // 8
        if (one >= 3 && five >= 1)
            dp[one][five][ten] = min(dp[one][five][ten], buy(coke - 1, one - 3, five - 1, ten) + 4);
        // 8
        if (one >= 8)
            dp[one][five][ten] = min(dp[one][five][ten], buy(coke - 1, one - 8, five, ten) + 8);
        return dp[one][five][ten];
    }

public:
    Solution(int coke, int one, int five, int ten) : coke(coke), one(one), five(five), ten(ten)
    {
        dp = vector<vector<vector<int>>>(one + 500, vector<vector<int>>(five + 100, vector<int>(ten + 10)));
    }
    int solve()
    {
        // coke cost 8
        return buy(coke, one, five, ten);
    }
};
int main(void)
{
    int t, coke, one, five, ten;
    cin >> t;
    while (t--)
    {
        cin >> coke >> one >> five >> ten;
        Solution solution(coke, one, five, ten);
        cout << solution.solve() << endl;
    }
}