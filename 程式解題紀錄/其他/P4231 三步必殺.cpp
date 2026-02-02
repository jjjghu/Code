#include <iostream>
#include <climits>
using namespace std;

const int MX = 1e7+5;
long long diff[MX]{};

void set(int l, int r, int s, int e, int d) {
    diff[l] += s;
    diff[l + 1] += d - s;
    diff[r + 1] -= d + e;
    diff[r + 2] += e;
}

void build(int n) {
    for(int i = 0; i < 2; ++i) {
        for(int j = 1; j <= n; ++j) {
            diff[j] += diff[j - 1];
        }
    }
}
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m; // 1e7, 3e5
    int l, r, s, e;
    for(int i = 0; i < m; i++) {
        cin >> l >> r >> s >> e;
        set(l, r, s, e, (e - s)/(r - l));
    }   
    build(n);
    long long mx = LLONG_MIN, xor_value = 0;
    for(int i = 1; i <= n; ++i) {
        mx = max(mx, diff[i]);
        xor_value ^= diff[i];
    }
    cout << xor_value << " " << mx;
}