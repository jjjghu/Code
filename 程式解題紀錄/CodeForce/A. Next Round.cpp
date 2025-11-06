#include <iostream>
#include <vector>
using namespace std;
int main(void) {
    int freq[101]{};
    int n, k, x;
    int res = 0;
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> x;
        freq[x]++;
    }
    for(int i = 100; i > 0; i--) {
        if(res < k) {
            res += freq[i];
        }
    }
    cout << res << endl;
}
/*
排名前 k 的人數有多少 (同分, 分數比較大都算贏過)
 */