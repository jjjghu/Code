#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        const int MOD = 1e9 + 7;
        int n = nums1.size();
        vector<int> sorted = nums1;
        sort(sorted.begin(), sorted.end());
        long long diff = 0;
        int mx_save = 0; // 最多能省去多少距離
        for(int i = 0; i < n; ++i) {
            int curDiff = abs(nums1[i] - nums2[i]);
            diff += curDiff;            
            // nums2[i] 找到在 nums1 中, 跟自己最接近的數字
            int idx = lower_bound(sorted.begin(), sorted.end(), nums2[i]) - sorted.begin();

            // 原先: abs(nums1[i] - nums2[i])
            // 後來: abs(nums1[idx] - nums2[i]);
            // 能省去 abs(nums1[idx] - nums2[i]) - abs(nums1[i] - nums2[i]);
            if(0 < idx && idx < n) {
                mx_save = max({mx_save, 
                               curDiff - abs(nums2[i] - sorted[idx - 1]), 
                               curDiff - abs(nums2[i] - sorted[idx])}); 
            }
            else if(idx == n) { // 最尾端
                mx_save = max(mx_save, curDiff - abs(nums2[i] - sorted[idx - 1])); 
            }
            else { // 最前端
                mx_save = max(mx_save, curDiff - abs(nums2[i] - sorted[idx])); 
            }
        }
        return (diff - mx_save) % MOD;
    }
};
void readFile(const string fileName, vector<int>& nums) {
    // 開啟檔案
    ifstream file(fileName);
    // 讀取整行
    string line;
    getline(file, line);
    
    // 使用 stringstream 來解析逗號分隔的數字
    stringstream ss(line);
    string temp;
    
    // 讀取每個數字（以逗號分隔）
    while (getline(ss, temp, ',')) {
        nums.push_back(stoi(temp));
    }
    file.close();      
}
int main(void) {
    int n;
    vector<int> nums1, nums2;
    readFile("input1.txt", nums1);
    readFile("input2.txt", nums2);
    Solution sol;
    cout << sol.minAbsoluteSumDiff(nums1, nums2);
    return 0;
}