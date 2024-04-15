// A UVA 495 Finonacci Freeze
#include <iostream>
#include <vector>
using namespace std;
class BigInteger
{
public:
    vector<int> num;
    // 無變數宣告
    BigInteger()
    {
        num.push_back(0);
    }
    // 用字串宣告
    BigInteger(string s)
    {
        num.resize(s.size());
        for (int i = 0; i < s.size(); i++)
        {
            num[i] = s[s.size() - 1 - i] - '0';
        }
    }
    void trim()
    {
        while (num.size() > 1 && num.back() == 0)
        {
            num.pop_back();
        }
    }
    // 取代相加
    BigInteger operator+(const BigInteger &other)
    {
        BigInteger res;
        int carry = 0;
        // 取得較大的數字長度
        int maxSize = max(num.size(), other.num.size());
        // 設定 res 的大小
        res.num.resize(maxSize);
        // 當數字小於 max(長度 a , 長度 b)
        for (int i = 0; i < maxSize || carry != 0; i++)
        {
            // 獲取當前位數, 若位數不夠則補 0
            int a = i < num.size() ? num[i] : 0;
            int b = i < other.num.size() ? other.num[i] : 0;
            // 前面的進位加上當前兩數字
            int sum = a + b + carry;
            // 根據 sum 判斷下一次的進位
            carry = sum / 10;
            // 如果空間不夠大, 往外擴
            if (i == res.num.size())
                res.num.push_back(0);
            // 獲取當前相加後的位數
            res.num[i] = sum % 10;
        }
        // 因為是倒過來的字串, 需要將前綴零刪掉
        res.trim();
        return res;
    }
};
BigInteger dp[5005];
int curMax = 0;
void fib(int n)
{
    // 若已經有算過了
    if (n <= curMax)
    {
        // 直接顯示答案
        for (int i = dp[n].num.size() - 1; i >= 0; --i)
        {
            cout << dp[n].num[i];
        }
        return;
    }
    // 第一次計算 or 沒算過
    for (int i = max(curMax, 2); i <= n; ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    for (int i = dp[n].num.size() - 1; i >= 0; --i)
    {
        cout << dp[n].num[i];
    }
}
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // need to using string since the size of number is big
    int curMax = -1;
    int n;

    // 初始條件
    dp[0] = BigInteger("0");
    dp[1] = BigInteger("1");
    while (cin >> n)
    {
        cout << "The Fibonacci number for " << n << " is ";
        fib(n);
        cout << endl;
        // 更新當前輸入最大值
        curMax = max(curMax, n);
    }
}