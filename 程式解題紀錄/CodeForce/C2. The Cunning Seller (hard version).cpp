#include <iostream>
#include <vector>
using namespace std;

vector<long long> cost;

auto init = []{
    long long c = 3, cnt = 1;
    cost.push_back(c);
    for(int i = 1; i < 30; ++i)
    {
        cnt *= 3;
        c = 3 * c + cnt;
        cost.push_back(c);
    }
    return 0;
}();

void solve(int num, int k)
{    
    int digits = 0;    
    vector<int> base3;
    while(num)
    {
        base3.push_back(num % 3);
        digits += num % 3;
        num /= 3;
    }
    
    // 最小成交次數都無法滿足
    if(digits > k)
    {
        cout << -1 << endl;
        return;
    }

    // 成交次數最低 = digits, 最多是 num(每次買一顆)
    // 拆分某些位數的時候，或許能得到更小的花費
    // 3^{n + 1} + n * 3^{n - 1} 大交易
    // 3 * (3^{n} + (n - 1) * 3^{n - 2}) 三個小交易
    // 3^{n} + n * 3^{n - 2}
    // 3^{n} + (n - 1) * 3^{n - 2} 各自約掉 3 
    // 很明顯，大交易虧錢虧爛了
    // 所以，每次都拆大交易，直到達到 k 的上限
    int curDeal = digits;
    k -= digits;
    k /= 2;

    for(int i = base3.size() - 1; i >=1 && k > 0; ++i)
    {
        int use = min(base3[i], k);
        base3[i - 1] += 3 * use;
        base3[i] -= use;
        k -= use;
    }
    long long total = 0;
    for(int i = 0; i < base3.size(); ++i)
    {
        total += 1LL * base3[i] * cost[i];
    }
    cout << total << endl;

}
int main(void)
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, k;
        cin >> n >> k;
        solve(n, k);
    }
}
/*
在成交數量不超過 k 的情況下，
買到 n 的西瓜所花的最小金錢數
 */