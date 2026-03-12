#include <iostream>
using namespace std;
const int MX = 100005;
int nums[MX];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }    
    bool found;
    int left, right, x;
    for(int i = 0; i < k; ++i) {
        cin >> x;
        found = false;
        left = 0, right = n - 1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] > x) {
                right = mid - 1;
            }
            else if(nums[mid] == x) {
                cout << mid + 1 << "\n";
                found = true;
                break;
            }
            else {
                left = mid + 1;
            }
        }
        if(!found) cout << 0 << "\n";
    }

}