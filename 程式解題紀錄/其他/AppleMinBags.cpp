#include <iostream>
using namespace std;
class Solution {
private:
    int dfs(int rest) {
        if(rest < 0) return INT_MAX; // 方案不成立(使用無限個袋子)
        if(rest == 0) return 0; // 方案成立
        int planA = dfs(rest - 6); // 使用 6 袋子裝
        int planB = dfs(rest - 8); // 使用 8 袋子裝

        planA += planA != INT_MAX ? 1 : 0; // 方案成立: 使用一個袋子, 不成立: 保持INT_MAX
        planB += planB != INT_MAX ? 1 : 0; 
        return min(planA, planB); // 選擇方案成立的那一個，並且花的袋子比較少。
    }
public:
    int bags1(int apple) {
        int res = dfs(apple);
        return res == INT_MAX ? -1 : res;
    }
    int bags2(int apple) {
        if(apple % 2 == 1) return -1; // 奇數都 -1
        if(apple < 18) {
            if(apple == 0) {
                return 0;
            }
            if(apple == 6 || apple == 8) {
                return 1;
            }
            if(apple == 12 || apple == 14 || apple == 16) {
                return 2;
            }    
            return -1;
        }
        return (apple - 18) / 8 + 3;
        // 18 ~ 24 都是 3
        // 24 ~ 32 都是 4 
        // 32 ~ 40 都是 5 
        // 40 ~ 48 都是 6 
        // 48 ~ 56 都是 7 
    }
};
int main(void) {
    Solution sol;
    for(int i = 0; i < 150; ++i) {
        if(sol.bags1(i) != sol.bags2(i)) {
            printf("Different at %d, expected: %d, output: %d", i, sol.bags1(i), sol.bags2(i));
        }
    }
    cout << "Passed!";
}