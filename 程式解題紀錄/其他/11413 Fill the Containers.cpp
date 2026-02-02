#include <iostream>
using namespace std;
const int MX = 1005;
int nums[MX]{};

int n, m;
bool check(int limit) {
    int cnt = 1;
    int sum = 0;
    for(int i = 0; i < n; i++) {
        if(sum + nums[i] > limit) {
            cnt++;
            sum = nums[i];
        }
        else {
            sum += nums[i];
        }
    }
    return cnt <= m;
}
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int left, right;
    while(cin >> n >> m) {
        left = 0, right = 0;
        for(int i = 0; i < n; i++) {
            cin >> nums[i];
            left = max(left, nums[i]);
            right += nums[i];
        }
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(check(mid)) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        cout << left << "\n";
    }
}