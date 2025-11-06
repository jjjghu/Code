#include <iostream>
#include <unordered_set>
using namespace std;
int main(void) {
    string s;
    cin >> s;
    unordered_set<char> uset;
    for(char ch : s) {
        uset.insert(ch);
    }
    if(uset.size() % 2 == 0) {
        cout << "CHAT WITH HER!";
    }
    else {
        cout << "IGNORE HIM!";
    }
}