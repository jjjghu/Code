#include <iostream>
using namespace std;

const int MX = 1e6 + 1;
int trie[MX][26]{};
int pass[MX]{};
int cnt;

void insert(string name) {
    int cur = 1;
    for(char ch : name) {
        int path = ch - 'a';
        if(trie[cur][path] == 0) {
            trie[cur][path] = ++cnt;
        }
        cur = trie[cur][path];
        pass[cur]++;
    }
}

void clearTrie() {
    for(int i = 0; i <= cnt; ++i) {
        for(int j = 0; j < 26; ++j) {
            trie[i][j] = 0;
        }
        pass[i] = 0;
    }
}

// cur: 當前的節點編號
// height: 現在節點的高度
// return: 所需要的最少字符總數
int dfs(int cur, int height) {
    if(pass[cur] == 1) { // 這條路只有一個節點
        return height;
    }
    int res = 0;
    for(int i = 0; i < 26; ++i) {
        if(trie[cur][i] == 0) continue; // 無路可走
        res += dfs(trie[cur][i], height + 1);
    }
    return res;
}

int main(void) {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n;
    string name;
    cin >> t;
    while(t--) {
        cnt = 1;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> name;
            insert(name);
        }
        cout << dfs(1, 0) << endl;
        clearTrie();
    }
}