#include <iostream>
using namespace std;
int main(void) {
    int n; 
    cin >> n;
    string s;
    int x = 0;
    while(n--) {
        cin >> s;
        if(s[1] == '+') {
            ++x;
        } 
        else {
            --x;
        }
    }
    cout << x << endl;
}