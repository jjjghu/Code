#include <ranges>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    vector<int> res = {1, 4, 2, 9, 0};
    ranges::sort(res);
    for(int i : res) {
        cout << i << " ";
    }
}
