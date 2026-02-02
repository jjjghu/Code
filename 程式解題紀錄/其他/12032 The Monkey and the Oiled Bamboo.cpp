#include <iostream>
using namespace std;

const int MX = 100005;
int nums[MX]{};
int n, m;

bool check(int k) {
    int cur = 0;
    for(int i = 0; i < n; i++) {
        int dist = nums[i] - cur;
        if(dist > k) return false;
        else if(dist == k)  k--;
        cur = nums[i];
    }
    return true;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for(int c = 1; c <= t; c++) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        int left = 1, right = 1e7;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(check(mid)) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        cout << "Case " << c << ": " << left << "\n"; 
    }
}