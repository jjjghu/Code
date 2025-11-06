#include <iostream>
using namespace std;
int main(void) {
    const string HELLO = "hello";
    const int n = HELLO.length();
    int index = 0;
    string s;
    cin >> s;
    for(char& ch : s) {
        if(index < n && ch == HELLO[index]) {
            ++index;;
        }
    }
    if(index == n) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
}