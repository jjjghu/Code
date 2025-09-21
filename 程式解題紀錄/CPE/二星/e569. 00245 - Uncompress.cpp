#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(void) 
{
    string s;
    vector<string> words;
    while (getline(cin, s)) 
    {
        if (s == "0")
            break;
        s += "\n";
        string word;
        int num = 0;
        for (int i = 0; i < s.length(); ++i) 
        {
            if (isalpha(s[i])) {
                word += s[i];
            }
            else if (isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
            }
            else {
                // 處理單字
                if (!word.empty()) {
                    cout << word;
                    words.insert(words.begin(), word);
                    word = "";
                }
                // 處理數字
                if (num != 0) {
                    string temp = words[num - 1];
                    cout << temp;

                    // 把它移到最前面
                    for (int j = num - 1; j > 0; --j) {
                        words[j] = words[j - 1];
                    }
                    words[0] = temp;

                    num = 0;
                }
                // 其他符號正常輸出
                cout << s[i];
            }
        }
    }
}
