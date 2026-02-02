#include <iostream>
#include <array>
#include <vector>
using namespace std;

struct TrieNode {
    int pass;
    int end;
    array<TrieNode*, 26> nexts;
    TrieNode() : pass(0), end(0), nexts{nullptr} { }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    // 插入新的字串
    void insert(string s) {
        TrieNode* node = root;
        root->pass++;
        for(char ch : s) {
            int path = ch - 'a';
            if(node->nexts[path] == nullptr) { // 還沒創建過這條路
                node->nexts[path] = new TrieNode();
            }
            node = node->nexts[path];
            node->pass++;
        }
        // 走到終點
        node->end++;
    }
    // 查詢前綴樹當中，字串 s 出現了幾次
    int search(string s) { 
        TrieNode* node = root;
        for(char ch : s) {
            int path = ch - 'a';
            if(node->nexts[path] == nullptr) {
                return 0;
            }
            node = node->nexts[path];
        }
        // 走到終點
        return node->end;
    }
    // 找出前綴樹當中以單字 s 為前綴的單字，一共有多少個
    int prefixNum(string s) {
        TrieNode* node = root;
        for(char ch : s) {
            int path = ch - 'a';
            if(node->nexts[path] == nullptr) {
                return 0;
            }
            node = node->nexts[path];
        }
        return node->pass;
    }
    // 將字串 s 從前綴樹刪除
    void remove(string s) {
        if(search(s) == 0) return; // 確保字串存在
        TrieNode* node = root;
        node->pass--;
        for(char ch : s) {
            int path = ch - 'a';
            if(--node->nexts[path]->pass == 0) { // 刪除的字串，是某個前綴的最後一個單字，這個子樹就整個刪掉了
                delete node->nexts[path]; // 釋放空間
                node->nexts[path] = nullptr;
                cout << "刪除整個子樹，當前節點" << ch << endl; 
                return;
            }
            node = node->nexts[path];
        }
        node->end--;
    }
};
int main(void) {
    Trie trie;
    trie.insert("abc");
    trie.insert("abde");
    trie.remove("abde");
}