#include <iostream>
#include <vector>
using namespace std;
int main(void) {
    vector<int> luckyNums;
    auto backtrack = [&](auto&& backtrack, int num) -> void {
        if (num > 1000) return;
        if(num > 0) luckyNums.push_back(num);
        num *= 10;
        backtrack(backtrack, num + 4);
        backtrack(backtrack, num + 7);
    };
    backtrack(backtrack, 0);
    int n; 
    cin >> n;
    for(int num : luckyNums) {
        if(n >= num && n % num == 0) {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
}
