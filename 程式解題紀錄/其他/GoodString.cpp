#include <iostream>
#include <vector>
using namespace std;
class Solution {
private:
    bool isPalindrome(string& cur, int left, int right) {
        while(left <= right) {
            if(cur[left] != cur[right]){
                return false;
            }
            left++;
            right--;
        }
        return true;
    };
    int dfs(string cur, int& n, int i) {
        if(i == n) {
            int cnt = 0;
            for(int left = 0; left < n - 1; ++left) {
                for(int right = left + 1; right < n; ++right) {
                    if(isPalindrome(cur, left, right)) {
                        ++cnt;
                    }
                    if(cnt > 1) { // 迴文數量太多，不是好串
                        return 0;
                    }
                }
            }
            return cnt == 1 ? 1 : 0; // 迴文數量太多，不是好串
        }
        else {
            int res = 0;
            res += dfs(cur + 'r', n, i + 1);
            res += dfs(cur + 'e', n, i + 1);
            res += dfs(cur + 'd', n, i + 1);
            return res;
        }
    }
public:
    int solve1(int n) {
        return dfs("", n, 0);
    }
    int solve2(int n) {
        if(n < 2) return 0;
        if(n == 2) return 3;
        if(n == 3) return 18;
        return (n + 1) * 6;
    }
};
int main(void) {
    bool passed = true;
    Solution sol;
    for(int i = 2; i <= 10; i++) {
        int a = sol.solve1(i);
        int b = sol.solve2(i);
        if(a != b) {
            passed = false;
            printf("Different at %d, expected: %d, output: %d", i, a, b);
            break;
        }
    }
    if(passed) cout << "Passed!";
}