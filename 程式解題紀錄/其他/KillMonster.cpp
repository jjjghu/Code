#include <bits/stdc++.h>
using namespace std;

class Code07_CutOrPoison {
public:
    // 動態規劃方法（只是為了驗證）
    // 血量比較大會超時（還很佔空間）
    static int fast1(const vector<int>& cuts, const vector<int>& poisons, int hp) {
        int sum = 0;
        for (int num : poisons) sum += num;
        // dp[i][r][p] : 從第 i 回合開始，剩餘血量 r，目前每回合毒傷 p 的情況下，
        // 怪獸在第幾回合最少死（回傳值是回合數）
        // Java 用 int[][][] 初始化為 0 為「沒算過」的標記
        // C++ 用 vector 初始化同樣全 0
        int n = (int)cuts.size();
        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(hp + 1, vector<int>(sum + 1, 0))
        );
        return f1(cuts, poisons, 0, hp, 0, dp);
    }

    // 不做要求：遞迴 + 記憶化
    static int f1(const vector<int>& cuts, const vector<int>& poisons,
                  int i, int r, int p,
                  vector<vector<vector<int>>>& dp) {
        r -= p;
        if (r <= 0) {
            return i + 1;
        }
        if (i == (int)cuts.size()) {
            if (p == 0) {
                return INT_MAX;
            } else {
                // cuts.length + 1 + (r + p - 1) / p
                return (int)cuts.size() + 1 + (r + p - 1) / p;
            }
        }
        if (dp[i][r][p] != 0) {
            return dp[i][r][p];
        }
        int p1 = (r <= cuts[i]) ? (i + 1) : f1(cuts, poisons, i + 1, r - cuts[i], p, dp);
        int p2 = f1(cuts, poisons, i + 1, r, p + poisons[i], dp);
        int ans = min(p1, p2);
        dp[i][r][p] = ans;
        return ans;
    }

    // cuts、poisons：每一回合刀砍、毒殺的效果
    // hp：怪獸血量
    // limit：回合限制（要求在 limit 回合內死）
    static bool f(const vector<int>& cuts, const vector<int>& poisons, long long hp, int limit) {
        int n = min((int)cuts.size(), limit);
        for (int i = 0; i < n; i++) {
            // 從刀砍與毒殺當中選一個傷害高的
            // 刀砍: cuts[i]
            // 毒殺: poisons[i], 從下回合 i + 1 生效，一直到 limit 為止。
            long long best = max((long long)cuts[i], (long long)poisons[i] * (limit - i - 1));
            hp -= best;
            if (hp <= 0) return true;
        }
        return false;
    }
    
    // 二分答案法（最優解）
    // 時間複雜度 O(nlog(hp)), 空間 O(1)
    static int fast2(const vector<int>& cuts, const vector<int>& poisons, int hp) {
        int l = 0, r = hp + 2; // 開區間
        while (l + 1 < r) {
            int m = l + (r - l) / 2;
            (f(cuts, poisons, (long long)hp, m) ? r : l) = m;
        }
        return r;
    }


    // 對數器測試：隨機數組
    static vector<int> randomArray(int n, int v) {
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = (rand() % v) + 1;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    srand((unsigned)time(nullptr));

    cout << "測試開始\n";
    // 隨機測試的資料量不大，因為 fast1 會逾時/爆內存
    int N = 30;
    int V = 20;
    int H = 300;
    int testTimes = 10000;

    for (int t = 0; t < testTimes; t++) {
        int n = (rand() % N) + 1;
        vector<int> cuts = Code07_CutOrPoison::randomArray(n, V);
        vector<int> poisons = Code07_CutOrPoison::randomArray(n, V);
        int hp = (rand() % H) + 1;

        int ans1 = Code07_CutOrPoison::fast1(cuts, poisons, hp);
        int ans2 = Code07_CutOrPoison::fast2(cuts, poisons, hp);

        if (ans1 != ans2) {
            cout << "出錯了!\n";
            // 你也可以選擇列印資料方便定位
            // cout << "n=" << n << " hp=" << hp << "\n";
            // ...
            break;
        }
    }

    cout << "測試結束\n";
    return 0;
}