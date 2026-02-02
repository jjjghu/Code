#include <iostream>
using namespace std;

struct TrieNode {
    int pass;
    TrieNode* nexts[26];
    TrieNode() : pass(0), nexts{nullptr} {};
};

class Trie {
public:
    TrieNode* root;
    Trie() : root(new TrieNode()) {};
    void insert(string name) {
        TrieNode* cur = root;
        for(char ch : name) {
            int path = ch - 'a';
            if(cur->nexts[path] == nullptr) {
                cur->nexts[path] = new TrieNode();
            }
            cur = cur->nexts[path];
            cur->pass++;
        }
    }

    // cur: 當前的節點
    // height: 現在節點的高度
    // return: 所需要的最少字符總數
    int dfs(TrieNode* cur, int height) {
        if(cur->pass == 1) { // 這條路只有一個節點
            return height;
        }
        int res = 0;
        for(int i = 0; i < 26; ++i) {
            if(cur->nexts[i] == nullptr) continue; // 無路可走
            res += dfs(cur->nexts[i], height + 1);
        }
        return res;
    }
};
int main(void) {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n;
    string name;
    cin >> t;
    while(t--) {
        Trie trie;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> name;
            trie.insert(name);
        }
        cout << trie.dfs(trie.root, 0) << endl;
    }
}