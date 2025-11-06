#include <iostream>
using namespace std;
int main(void) {
    int n, m, a; 
    cin >> n >> m >> a;
    int row = n / a + (n % a > 0 ? 1 : 0);
    int col = m / a + (m % a > 0 ? 1 : 0);
    cout << 1LL * row * col << endl;
}