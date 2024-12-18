#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

bool is_greater(const string &s1, const string &s2)
{
    string s1_trim = s1, s2_trim = s2;
    s1_trim.erase(0, s1_trim.find_first_not_of('0'));
    s2_trim.erase(0, s2_trim.find_first_not_of('0'));
    if (s1_trim.empty())
        s1_trim = "0";
    if (s2_trim.empty())
        s2_trim = "0";
    if (s1_trim.length() != s2_trim.length())
        return s1_trim.length() > s2_trim.length();
    return s1_trim > s2_trim;
}
void solve(char *fileName)
{
    ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        cout << "無法開啟檔案: " << fileName << "\n";
        return;
    }
    string s1, s2;
    while (inFile >> s1 >> s2)
    {
        int n = s1.length(), m = s2.length();
        vector<vector<string>> dp(n + 1, vector<string>(m + 1, ""));
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + s1[i - 1];
                }
                else
                {
                    dp[i][j] = is_greater(dp[i - 1][j], dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
                }
            }
        }
        string result = dp[n][m];
        result.erase(0, result.find_first_not_of('0'));
        // cout << "The common subsequence of " << s1 << " and " << s2 << " is ";
        cout << (result.empty() ? "0" : result) << endl;
    }
    return;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " <input_file_1> <input_file_2> ... <input_file_n>\n";
        return 1;
    }
    for (int i = 1; i < argc; ++i)
    {
        solve(argv[i]);
    }
    return 0;
}
/*
動態規劃五步法
1. 構造問題: s1, s2 的最長共同子序列
2. 定義狀態: f(i, j) = s1[:i] 和 s2[:j] 的最長共同子序列
3. 求解小規模的簡單問題:
   f(i, 0) = ""
   f(0, j) = ""
4. 狀態轉移方程式:
    f(i, j) =
    {
        if s1[i] == s2[j] : f(i - 1, j - 1) + s1[i];
        else: 選擇 f(i - 1, j), f(i, j - 1) 比較長的
    }
5. 判斷複雜度: O(n^2)
*/
/*
最大共同子整數問題 (pdf可到公告區下載)
給定一個正數 N1=2579413，
定義一個整數的子整數為組成的數字出現在原整數內，
可以不連續但必須要維持數字之間的順序。
例如，2, 5, 7, 9, 4, 1, 3, 25, 27, 29, 24, 293, 413, 2793, 57941, 2579413等(未完全列出)均為N1的子整數。
共同子整數問題為在給定的兩個整數N1, N2中，出現於每一個整數的子整數為N1與N2的共同子整數。
例如若N1=2579413, N2=354573,
共同子整數為5, 4, 3, 7, 57, 54, 53, 73, 43, 543, 573等。
共同子整數中數值最大者定義為此兩個整數的最大共同子整數(Largest Common Sub-Integer, LCSI)。
故N1=2579413, N2=354573, LCSI(N1, N2)=573
設計一個程式，輸入兩個正整數，輸出此兩個正整數的最大共同子整數，若無則輸出0。

輸入說明： 每組測試案例之輸入資料於同一行，代表為兩個正整數N1, N2，中間以空格區分。
單一輸入整數最大位數為50位。

輸出說明： 每組測試案例輸出一行，輸出為一個整數。
範例輸入1： 1357904 20468
範例輸出1：4

範例輸入2： 2579413 354573
範例輸出2： 573

範例輸入3： 12365402345 316524015331
範例輸出3： 365405

範例輸入4： 123654045 31654015
範例輸出4： 365405

範例輸入5： 10579413 015143
範例輸出5： 1543

範例輸入6： 123654045123654045 3165401531654015
範例輸出6： 365405365405
*/