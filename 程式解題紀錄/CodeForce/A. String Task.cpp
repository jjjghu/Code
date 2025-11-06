#include <iostream>
using namespace std;
int main(void) {
    string vowels = "aoyeui";
    string s, res;
    cin >> s;
    for(char& ch : s) {
        if(vowels.find(tolower(ch)) != string::npos) {
            continue;
        }
        else {
            res += '.';
            res += tolower(ch);
        }
    }
    cout << res;
}