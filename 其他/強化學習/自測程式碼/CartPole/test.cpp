#include <iostream>
using namespace std;
int main(void) {
    const int patterns[2][9] = {
        {0x10, 0x18, 0x1C, 0x1E, 0x1F, 0x0F, 0x07, 0x03, 0x01},
        {0x0A, 0x15, 0x0A, 0x15, 0x01, 0x03, 0x07, 0x0F, 0x1F}
    };
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 9; j++) {
            cout << "0x" << hex << (patterns[i][j]<<3) << ", ";
        }
        cout << endl;
    }
}