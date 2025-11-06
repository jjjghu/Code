#include <iostream>
using namespace std;
int main(void) {
    int t;
    cin >> t;
    int dx, dy, dz;
    int x, y, z;
    x = y = z = 0;
    while(t--) {
        cin >> dx >> dy >> dz;
        x += dx;
        y += dy;
        z += dz;
    }
    if(x == 0 && y == 0 && z == 0) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
}