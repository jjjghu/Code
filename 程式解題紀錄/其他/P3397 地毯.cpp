#include <iostream>
#include <string.h>
using namespace std;
const int MX = 1005;
int diff[MX][MX];
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; 
    cin >> n >> m;
    int x1, y1, x2, y2;
    for(int i = 0; i < m; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        diff[x1][y1]++;
        diff[x1][y2 + 1]--;
        diff[x2 + 1][y1]--;
        diff[x2 + 1][y2 + 1]++;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << diff[i][1];
        for(int j = 2; j <= n; j++) {
            cout << " " << diff[i][j];
        }
        cout << "\n";
    }
}