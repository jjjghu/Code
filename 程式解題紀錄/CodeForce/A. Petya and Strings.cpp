#include <iostream>
using namespace std;
int main(void) {
    string s1, s2;
    cin >> s1 >> s2;
    for(char& ch : s1) {
        ch = tolower(ch);
    }
    for(char& ch : s2) {
        ch = tolower(ch);
    }
    if(s1 == s2) {
        cout << "0";
    }
    else if(s1 > s2) {
        cout << "1" << endl;
    }
    else {
        cout << "-1" << endl;
    }
}