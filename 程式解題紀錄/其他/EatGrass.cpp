#include <iostream>
using namespace std;
class Solution {
private:
    // rest：還有多少草
    // cur：當前選手名字
    // return：誰會贏
    char dfs(int rest, char cur) {
        char enemy = cur == 'A' ? 'B' : 'A';
        if(rest < 5) {
            return rest == 0 || rest == 2 ? enemy : cur;
        }
        else {
            int pick = 1;
            // 吃一份草 -> 自己會不會贏
            // 吃四份草 -> 自己會不會贏
            // 吃16份草 -> 自己會不會贏
            // ...
            while(pick <= rest) {
                if(dfs(rest - pick, enemy) == cur) {
                    return cur;
                }
                pick *= 4;
            }
            return enemy; // 滿盤接輸
        }
    }
public:
    char solve1(int n) {
        return dfs(n, 'A');
    }
    char solve2(int n) {
        const string s = "BABAA";
        return s[n % 5];
        // BABAA
        // BABAA
        // BABAA
    }
};
int main(void) {
    Solution sol;
    for(int i = 0; i < 50; ++i) {
        char a = sol.solve1(i);
        char b = sol.solve2(i);
        if(a != b) {
            printf("Differnt at %d, expected: %d, output: %d\n",i, a, b);
        }
    }
}