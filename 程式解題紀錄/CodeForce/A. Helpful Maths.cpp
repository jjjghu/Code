#include <iostream>
using namespace std;
int main(void) {
    string s;
    cin >> s;
    int freq[3]{};
    for(char& ch : s) {
        freq[ch - '1']++;
    }
    s = "";
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < freq[i]; ++j) {
            s += (char)(i + '1');
            s += '+';
        }
    }
    s.pop_back();
    cout << s;
}