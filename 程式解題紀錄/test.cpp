#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
class Solution {
private:
    vector<int> combine(vector<int>& a, vector<int>& b) {
        int index = 0, i = 0, j = 0;
        vector<int> res(a.size() + b.size());
        while(i < a.size() && j < b.size()) {
            res[index++] = nums[i] < nums[j] ? nums[i++] : nums[j++];
        }
        while(i < a.size()) {
            res[index++] = nums[i++];
        }
        while(j < b.size()) {
            res[index++] = nums[j++];
        }
        return res;
    }
public:
    long long minMergeCost(vector<vector<int>>& lists) {
        long long res = LLONG_MAX;
        auto dfs = [&](vector<vector<int>> list, long long cost) -> void {
            if(list.size() < 2) {
                res = min(res, cost);
                return;
            }
            for(int i = 0; i < list.size(); ++i) {
                for(int j = i + 1; j < list.size(); ++j) {
                    if(i == j) continue;
                    // 合併 i, j, 將新的加入 
                    vector<int> temp = combine(list[i], list[j]);
                    list[i] = temp;
                    list.erase(list.begin() + j);
                    dfs(list);
                }
            }
        };
        dfs(lists, 0);
        return res;
    }
};
int main(void) {
    Solution sol;
    vector<string> vec = {"able", "area", "echo", "also"};
    vector<vector<string>> res = sol.wordSquares(vec);
    cout << "test begin\n";
    for(auto& v : res) {
        for(auto& s : v) {
            cout << s << " ";
        }
        cout << endl;
    }
    cout << "test end\n";
}