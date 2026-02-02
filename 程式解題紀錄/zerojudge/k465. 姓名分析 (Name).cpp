#include <iostream>
#include <vector>
using namespace std;

const int MX = 2e6 + 1;
int cnt = 1;
int trie[MX][26]{};
int pass[MX]{};

void buildTrie(vector<string>& names) {
    for(int i = 0; i < names.size(); ++i) {
        int cur = 1;
        for(int j = 0; j < names[i].length(); ++j) {
            int path = names[i][j] - 'A';
            if(trie[cur][path] == 0) {
                trie[cur][path] = ++cnt;
            }
            cur = trie[cur][path];
            pass[cur]++;
        }
    }
}

int search(string name) {
    int cur = 1;
    int res = 0;
    for(int i = 0; i < name.length(); ++i) {
        int path = name[i] - 'A';
        if(trie[cur][path] == 0) {
            return res;
        }
        cur = trie[cur][path];
        res += pass[cur] - 1;
    }
    return res;
}

int main(void) {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> names(n);
    for(int i = 0; i < n; ++i) {
        cin >> names[i];
    }

    buildTrie(names);

    for(string name : names) {
        cout << search(name) << "\n";
    }
}