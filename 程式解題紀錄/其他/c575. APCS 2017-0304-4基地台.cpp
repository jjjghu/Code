#include <iostream>
#include <algorithm>
using namespace std;
const int MX = 50001;
int nums[MX];
int n, k;

bool check(int diameter) {
    // 最多只能放 k 個基地台，問在直徑為 diameter 的情況下能不能擺放
    int cnt = 1; // 基地台數量
    int end = nums[0] + diameter; // 第一個基地台能覆蓋的起點
    for(int i = 1; i < n; i++) {
        if(nums[i] > end) {
            if(++cnt > k) return false;
            end = nums[i] + diameter;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    sort(nums, nums + n);
    int left = 0, right = (nums[n - 1] - nums[0]) / k + 1;
    while(left + 1 < right) {
        int mid = left + (right - left) / 2;
        (check(mid) ? right : left) = mid;
    }
    cout << right;
}