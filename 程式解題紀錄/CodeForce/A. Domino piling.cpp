#include <iostream>
using namespace std;
int main(void) {
    int m, n;
    cin >> m >> n;
    if(m % 2 == 0) {
        cout << m / 2 * n << endl;
    }
    else if(n % 2 == 0) {
        cout << n / 2 * m << endl;
    }
    else {
        cout << n / 2 * m + m / 2 << endl;
    }
}