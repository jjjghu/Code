#include <iostream>
using namespace std;
int main(void) {
    const int n = 5;
    bool matrix[n][n]{};
    int x, y;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
            if(matrix[i][j]) {
                x = i;
                y = j;
                break;
            }
        }
    }
    cout << abs(x - 2) + abs(y - 2);
}