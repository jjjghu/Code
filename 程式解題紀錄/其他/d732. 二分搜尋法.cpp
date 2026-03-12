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
    for(int i = 0, x; i < k; ++i) {
        cin >> x;
        auto it = lower_bound(nums, nums + n, x);
        if(it == nums + n || *it != x) {
            cout << 0 << "\n";
        }
        else {
            cout << it - nums + 1 << "\n";
        }
    }

}