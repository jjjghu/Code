#include <iostream>
#include <vector>
using namespace std;
vector<int> dp;
void init()
{
    dp.push_back(0);
    dp.push_back(1);
    int a = 0, b = 1;
    while (b < 1000000)
    {
        dp.push_back(a + b);
        int temp = a + b;
        a = b;
        b = temp;
    }
}
void solve()
{
    int left, right;
    cin >> left >> right;
    if (left > right)
    {
        swap(left, right);
    }
    int cnt = 0;
    for (const int &value : dp)
    {
        if (value > right)
        {
            break;
        }
        if (left <= value)
        {
            cout << value << "\n";
            ++cnt;
        }
    }
    cout << cnt << "\n";
}

int main(void)
{
    init();
    int t;
    cin >> t;
    while (t--)
    {
        solve();
        if (t != 0)
        {
            cout << "------\n";
        }
    }
}
/*
動態規劃五步法
1. 構造問題: 輸出範圍內的費氏數列
2. 定義狀態: f(i) 表示費氏數列的第 i 項
3. 求解小規模的簡單問題: f(0) = 1, f(1) = 1
4. 狀態轉移方程式: f(i) = f(i - 1) + f(i - 2);
5. 判斷複雜度: O(n)
*/