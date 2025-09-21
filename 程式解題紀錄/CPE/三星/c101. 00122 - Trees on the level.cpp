#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left, *right;
    bool hasValue = false;
    TreeNode() : val(0), hasValue(false), left(nullptr), right(nullptr)
    {}
};
int main(void)
{
    string s;
    TreeNode* root = nullptr;
    bool ok = true;

    // 新增節點
    auto addNode = [&](int value, string& path)
    {
        if(root == nullptr)
        {
            root = new TreeNode();
        }
        TreeNode* cur = root;
        for(int i = 0; i < path.size(); ++i)
        {
            if(path[i] == 'L')
            {
                if(!cur -> left)
                {
                    cur -> left = new TreeNode();
                }
                cur = cur -> left;
            }
            else
            {
                if(!cur -> right)
                {
                    cur -> right = new TreeNode();
                }
                cur = cur -> right;
            }
        }
        if(cur -> hasValue)
        {
            return false;
        } 
        cur -> val = value;
        cur -> hasValue = true;
        return true;
    };

    // 走訪答案，檢查值存在
    auto bfs = [&](vector<int>& res){
        res.clear();
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            TreeNode* cur = q.front();
            q.pop();
            if(!cur -> hasValue)
            {
                return false;
            }
            res.push_back(cur -> val);
            if(cur -> left)
            {
                q.push(cur -> left);
            }
            if(cur -> right)
            {
                q.push(cur -> right);
            }
        }
        return true;
    };

    while(cin >> s)
    {
        // 終止輸入
        if(s == "()")
        {
            vector<int> res;
            if(ok && bfs(res))
            {
                for(int i = 0; i < res.size(); ++i)
                {
                    if(i) cout << " ";
                    cout << res[i];
                }
                cout << endl;
            }
            else 
            {
                cout << "not complete\n";
            }
            root = nullptr;
            ok = true;
        }
        else 
        {
            // 拆分數值跟位置
            int value = 0;
            string path = "";
            for(int i = 1; i < s.length() - 1; ++i)
            {
                if(s[i] == ',')
                {
                    path = s.substr(i + 1, s.length() - i - 2);
                    break;
                }
                else 
                {
                    value *= 10;
                    value += s[i] - '0';
                }
            }
            // 新增節點
            if(!addNode(value, path))
                ok = false;
        }
    }
    return 0;
}