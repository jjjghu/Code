// P5026 Lycanthropy
#include <iostream>
using namespace std;
const int MX = 1e6 + 1;
const int OFFSET = 3e4 + 1; // 避免 v 越界判斷
long long diff[OFFSET + MX + OFFSET]{};
void set(int l, int r, int s, int e, int d) {
    diff[l] += s;
    diff[l + 1] += d - s;
    diff[r + 1] -= d + e;
    diff[r + 2] += e;
}
void build(int m) {
    for(int i = 1; i <= m + OFFSET; ++i) {
        diff[i] += diff[i - 1];
    }
    for(int i = 1; i <= m + OFFSET; ++i) {
        diff[i] += diff[i - 1];
    }
}
int main(void) {
    int n, m, v, x; // 1e6, 1e6, 1e4, 1e6
    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> v >> x; // 體積, 落水點 i 
        x += OFFSET; // 落水點加入偏移量
        set(x-3*v+1, x-2*v, 1, v, 1);
        set(x-2*v+1, x, v-1, -v, -1);
        set(x+1, x+2*v, -v+1, v, 1);
        set(x+2*v+1, x+3*v-1, v-1, 1, -1);
    }
    build(m);
    for(int i = OFFSET + 1; i <= OFFSET + m; ++i) {
        cout << diff[i] << (i == OFFSET + m ? "" : " ");
    }
    cout << endl;
}