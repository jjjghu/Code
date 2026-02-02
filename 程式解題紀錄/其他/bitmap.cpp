#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>
using namespace std;
class BitSet {
private:
    const int LEN = 32;
    vector<int> nums;
public:
    BitSet(int n) : nums((n + LEN - 1) / LEN) {}
    void add(int num) {
        // 第 num / LEN 個數字的第 num % LEN 個位置
        nums[num / LEN] |= 1 << (num % LEN);
    }
    void remove(int num) {
        // 第 num / LEN 個數字的第 num % LEN 個位置
        // mask: 移除的位置是 1, 其他為 0 
        nums[num / LEN] &= ~(1 << (num % LEN)); 
    }
    void reverse(int num) {
        nums[num / LEN] ^= 1 << (num % LEN);
    }
    bool contain(int num) {
        return (nums[num / LEN] >> (num % 32) & 1) == 1;
    }
};
int main(void) {
    int n = 1e3;
    int testTime = 1e4;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis1(1, n);
    uniform_real_distribution<double> dis2(0, 1);

    cout << "測試開始\n";    
    BitSet bset(n);
    unordered_map<int, bool> umap;
    cout << "調用階段開始\n";
    for(int i = 0; i < testTime; ++i) {
        double decide = dis2(gen);
        int number = dis1(gen);
        if(decide < 0.333) {
            bset.add(number);
            umap[number] = true;
        }
        else if(decide < 0.666) {
            bset.remove(number);
            umap[number] = false;
        }
        else {
            bset.reverse(number);
            if(umap.find(number) != umap.end()) {
                umap[number] = !umap[number];
            }
        }
    }
    cout << "調用階段結束\n";
    cout << "調用階段開始\n";
    for(int i = 0; i < n; ++i) {
        if(bset.contain(i) != umap[i]) {
            cout << "出錯了!\n";
        }
    }
    cout << "驗證階段結束\n";
    cout << "測試結束";
}