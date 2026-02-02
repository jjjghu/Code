#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
struct TreeNode{ 
    long long val;
    vector<TreeNode*> list;
    TreeNode(long long value) : val(value) {}
};
long long getHeight(TreeNode* node) {
    if(node == nullptr || node->list.empty()) return 0;
    
    static unordered_map<TreeNode*, int> memo; // 節點對應的高度, 記憶化搜索
    if(memo.find(node) != memo.end()) {
        return memo[node];
    }
    
    long long mxHeight = 0;
    for(int i = 0; i < node->list.size(); ++i) {
        mxHeight = max(mxHeight, getHeight(node->list[i]));
    }
    memo[node] = 1 + mxHeight;
    
    return 1 + mxHeight;
}
int main(void) {
    int n;
    cin >> n;
    unordered_map<long long, TreeNode*> umap; // 編號 -> 節點
    for(int i = 1; i <= n; ++i) {
        int cnt;
        cin >> cnt;
        TreeNode* node = nullptr;
        if(umap.find(i) != umap.end()) {
            node = umap[i];
        }
        else {
            node = new TreeNode(i);
            umap[i] = node;
        }
        while(cnt--) { 
            int val;
            cin >> val;
            TreeNode* nextNode = nullptr;
            if(umap.find(val) != umap.end()) {
                nextNode = umap[val];
            }
            else {
                nextNode = new TreeNode(val);
                umap[val] = nextNode;
            }
            node->list.push_back(nextNode);
        }
    }
    TreeNode* root = nullptr;
    long long sumHeight = 0, mxHeight = 0;
    for(int i = 1; i <= n; ++i) {
        int curHeight = getHeight(umap[i]);
        if(curHeight > mxHeight) {
            mxHeight = curHeight;
            root = umap[i];
        }
        sumHeight += curHeight;
    }
    cout << root->val << endl;
    cout << sumHeight;
}