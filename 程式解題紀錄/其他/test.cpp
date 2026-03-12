#include <iostream>
using namespace std;
const int MX = 51;
int nums[MX];
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t, n;
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		int res = 0;
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				res += nums[i] > nums[j];
			}
		}
		cout << "Optimal train swapping takes " << res << " swaps." << endl;
	}
}