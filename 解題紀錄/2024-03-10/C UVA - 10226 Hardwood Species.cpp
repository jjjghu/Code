// UVA - 10226 Hardwood Species
#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    int n;
    string s;
    cin >> n;
    cin.ignore();    // 忽略上面的 \n
    getline(cin, s); // 獲取空白行
    while (n--)
    {
        map<string, int> mp; // 建立 map
        int sum = 0;
        while (getline(cin, s) && s != "") // 獲取輸入, 獲取到空白結束
        {
            ++mp[s]; // 該樹種出現次數 + 1
            ++sum;   // 計算總數
        }
        for (auto it : mp) // map會依照字典序輸出
        {
            cout << it.first << " " << fixed << setprecision(4) << (double)(it.second * 100) / sum << endl;
        }
        cout << endl;
    }
}