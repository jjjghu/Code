// UVA 490 Rotating Sentence
#include <iostream>
#include <cstring>
using namespace std;

const int mxN = 100;
char list[mxN + 1][mxN + 1];
int main(void)
{
    memset(list, ' ', sizeof(list));
    string s;
    int cnt = 0, mx = 0;    // 紀錄有幾行, 最長字串長度
    while (getline(cin, s)) // 輸入包含空格, 使用 getline
    {
        for (int i = 0; i < s.length(); ++i)
        {
            list[cnt][i] = s[i];
        }
        mx = max(mx, (int)s.length()); // 更新字串長度
        cnt++;
    }
    for (int i = 0; i < mx; ++i)
    {
        for (int j = cnt - 1; j >= 0; --j)
        {
            if (list[j][i] == '\0') // 若為字串結尾
                cout << ' ';        // 輸出空格
            else
                cout << list[j][i];
        }
        cout << endl;
    }
}
