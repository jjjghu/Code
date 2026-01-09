#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
const int MX = 1e5 + 5;
vector<int> adj[MX];
long long height[MX];
bool has_parent[MX];

struct TreeNode{ 
    long long val;
    vector<TreeNode*> list;
    TreeNode(long long value) : val(value) {}
};

long long getHeight(int node) {
    if(adj[node].empty()) return 0;
    if(height[node] != -1) return height[node];

    long long mxHeight = 0;
    for(int v : adj[node]) {
        mxHeight = max(mxHeight, 1 + getHeight(v));
    }
    return height[node] = mxHeight;
}
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) height[i] = -1;
    for(int i = 1; i <= n; ++i) {
        int cnt;
        cin >> cnt;
        while(cnt--) { 
            int val;
            cin >> val;
            adj[i].push_back(val);
            has_parent[val] = true;
        }
    }
    int root = 1;
    for(int i = 1; i <= n; ++i) {
        if(!has_parent[i]) {
            root = i;
            break;
        }
    }
    long long sumHeight = 0;
    for(int i = 1; i <= n; ++i) {
        sumHeight += getHeight(i);
    }
    cout << root << "\n" << sumHeight << "\n";
}