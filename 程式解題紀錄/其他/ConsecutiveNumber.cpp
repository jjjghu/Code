#include <iostream>
#include <set>
using namespace std;
class Solution{
private:
public:
    bool check1(int num) {
        int sum;
        for(int start = 1; start < num; ++start) {
            sum = start;
            for(int j = start + 1; j < num; ++j) {
                sum += j;
                if(sum > num) { // 太大
                    break;
                }
                else if(sum == num) { // 相等，找到目標
                    return true;
                }
            }
        }
        return false;
    }
    bool check2(int num) {
        return (num & (num - 1)) != 0;
    }
};  
int main(void) {
    Solution sol;
    for(int i = 1; i < 1000; ++i) {
        bool a = sol.check1(i);
        bool b = sol.check2(i);
        if(a != b) {
            printf("Different at %d, expected: %d, output %d\n", i, a, b);
            break;
        }
    }
}