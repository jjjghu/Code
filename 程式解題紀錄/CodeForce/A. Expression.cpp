#include <iostream>
using namespace std;
int main(void) {
    int a, b, c;
    cin >> a >> b >> c;
    // ab add mpy -> (ab), c, add, mpy
    // bc add mpy -> a, (bc), add, mpy
    int res = 0;
    res = max(res, a + b + c);
    res = max(res, a * b * c);
    res = max(res, a + b * c);
    res = max(res, a * b + c);
    res = max(res, (a + b) * c);
    res = max(res, a * (b + c));
    cout << res;
}
/*
+, *, ()
*/