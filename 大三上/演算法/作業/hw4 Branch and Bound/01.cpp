#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
using namespace std;

ostream &operator<<(ostream &os, const vector<bool> &v)
{
    // vector<bool> 的自訂義輸出
    for (bool b : v)
        os << b;
    return os;
};

struct Product
{
    int profit;
    int weight;
    int index;
    Product() : profit(0), weight(0), index(0) {}
    Product(int profit, int weight, int index) : profit(profit), weight(weight), index(index) {}
    // implement operator >, 用於 sort
    bool operator>(const Product &other) const
    {
        // 轉換成 double 之後相除
        return static_cast<double>(profit) / weight > static_cast<double>(other.profit) / other.weight;
    }
    // override print, using friend function to make it accessible by "cout << product"
    friend ostream &operator<<(ostream &os, const Product &product)
    {
        os << product.profit << " " << product.weight << " " << product.index << "\n";
        return os;
    }
};
enum class OutputFormat
{
    DETAIL,
    COMPACT,
    DEBUG
};
struct Node
{
    int lowerBound;
    int upperBound;
    int index;
    vector<bool> choose;
    // 輸出格式
    static OutputFormat outputFormat;
    Node(int lowerBound, int upperBound, int index, vector<bool> choose)
    {
        this->lowerBound = lowerBound;
        this->upperBound = upperBound;
        this->index = index;
        this->choose = choose;
    }
    // implement operator <, 用在 queue 上
    bool operator<(const Node &other) const
    {
        if (lowerBound != other.lowerBound)
            return lowerBound < other.lowerBound; // 讓 priority_queue 大的值優先處理
        return upperBound < other.upperBound;
    }
    // override print, using friend function to make it accessible by "cout << node"
    friend ostream &operator<<(ostream &os, const Node &node)
    {
        if (Node::outputFormat == OutputFormat::DEBUG)
        {
            os << "index = " << node.index << " " << node.choose
               << ", LB=" << node.lowerBound << ", UB=" << node.upperBound << "\n";
            os << "deep = " << node.index << " " << node.choose
               << ", LB=" << node.lowerBound << ", UB=" << node.upperBound << "\n";
        }
        if (Node::outputFormat == OutputFormat::COMPACT)
        {
            os << node.choose << ", LB=" << node.lowerBound << ", UB=" << node.upperBound << "\n";
        }
        else if (Node::outputFormat == OutputFormat::DETAIL)
        {
            for (int i = 0; i < node.choose.size(); ++i)
            {
                if (i < node.index)
                    os << node.choose[i];
                else
                    os << 'X';
            }
            os << ", LB=" << node.lowerBound << ", UB=" << node.upperBound << "\n";
        }
        return os;
    }
};
class Solution
{
private:
    friend class DynamicProgramming;
    int M, n, profit, weight;
    vector<Product> products; // profit weight
    void init()
    {
        products.resize(n);
    }
    bool findBound(Node &node)
    {
        // Greedy,    找出沒有 01 限制的最優解 (LowerBound)
        // Greedy 01, 找出一個可行解 (UpperBound)
        // --------------------------------
        // 計算前面選擇狀況的樣子
        // 重置選擇狀況 (index 前面的不修改)
        fill(node.choose.begin() + node.index, node.choose.end(), 0);
        int m = M;
        int totalProfit = 0;
        for (Product p : products)
        {
            if (node.choose[p.index] == true)
            {
                m -= p.weight;
                totalProfit += p.profit;
            }
        }
        if (m < 0)
        {
            // 因為強制設定為 true, 導致 infeasible
            return false;
        }
        vector<Product> choosableProduct;
        for (Product p : products)
        {
            if (node.index <= p.index)
            {
                choosableProduct.push_back(p);
            }
        }
        // 依照平均獲利排序
        sort(choosableProduct.begin(), choosableProduct.end(), greater<Product>());
        for (Product p : choosableProduct)
        {
            // 重量足夠放下, 將物品放入背包中
            if (p.weight <= m)
            {
                m -= p.weight;
                totalProfit += p.profit;
                node.choose[p.index] = true;
            }
            // 超出重量, 提前退出
            else
            {
                // UpperBound
                node.upperBound = totalProfit;

                // LowerBound
                // 重量不足, 將物品切開放入背包中
                totalProfit += p.profit * m / p.weight;
                node.lowerBound = totalProfit;
                break;
            }
        }
        return true;
    }

public:
    void readFile(char *fileName)
    {
        // read file
        ifstream inFile(fileName);
        if (!inFile.is_open())
        {
            cout << "無法開啟檔案: " << fileName << "\n";
            return;
        }
        inFile >> M >> n;
        init();
        for (int i = 0; i < n; ++i)
        {
            inFile >> profit >> weight;
            products[i] = Product(profit, weight, i);
        }
        products[n - 1] = Product(0, INT_MAX, n - 1);
    }
    void solve()
    {
        // 根節點
        // Node(lowerbound, upperbound, index, choose);
        Node root = Node(0, 0, 0, vector<bool>(n, false));
        findBound(root);
        int bestUpperBound = root.upperBound;

        vector<Node> visitPath;
        // must initialize, 因為沒有建構子

        // 將根節點放入 queue 中
        priority_queue<Node, vector<Node>> pq;
        pq.push(root);
        while (!pq.empty())
        {
            Node node = pq.top();
            pq.pop(); // 必須要在這裡 pop, 避免後續 push 改變順序
            // cout << node;
            visitPath.push_back(node);
            for (bool choice : {true, false})
            {
                Node newNode = node;
                newNode.choose[newNode.index] = choice;
                ++newNode.index;
                bool feasible = findBound(newNode);

                if (newNode.index < n && feasible && newNode.lowerBound >= bestUpperBound)
                {
                    pq.push(newNode);
                    bestUpperBound = max(bestUpperBound, newNode.upperBound);
                }
            }
        }
        Node resultNode = root;
        bool find = false;
        int i;
        for (i = 0; i < visitPath.size(); ++i)
        {
            if (!find && visitPath[i].upperBound == visitPath[i].lowerBound)
            {
                find = true;
                resultNode = visitPath[i];
            }
            cout << "step:" << i << "\t" << visitPath[i];
        }
        Node::outputFormat = OutputFormat::COMPACT;
        cout << "\nFind the BEST answer when step " << i << ": \n"
             << resultNode;
        // // debug 用
        // queue<Node> pq;
        // pq.push(root);
        // int step = 0;
        // while (!pq.empty())
        // {
        //     int size = pq.size();
        //     cout << "\nstep: " << step++ << "\n";
        //     for (int i = 0; i < size; ++i)
        //     {
        //         Node node = pq.front();
        //         pq.pop(); // 必須要在這裡 pop, 避免後續 push 改變順序
        //         cout << node;
        //         for (bool choice : {true, false})
        //         {
        //             Node newNode = node;
        //             newNode.choose[newNode.index] = choice;
        //             ++newNode.index;
        //             bool feasible = findBound(newNode);

        //             if (newNode.index < n && feasible && newNode.lowerBound >= bestUpperBound)
        //             {
        //                 pq.push(newNode);
        //                 bestUpperBound = max(bestUpperBound, newNode.upperBound);
        //             }
        //         }
        //     }
        // }
    }
};
class DynamicProgramming
{
private:
    Solution &solution;

public:
    DynamicProgramming(Solution &sol) : solution(sol) {}
    void solve()
    {
        int M = solution.M; // 背包大小
        int n = solution.n; // 商品數量
        vector<Product> products = solution.products;
        vector<int> dp(M + 1, 0);
        vector<vector<bool>> choose(n + 1, vector<bool>(M + 1, false));

        for (int i = 1; i <= n; ++i)
        {
            for (int j = M; j >= products[i - 1].weight; --j)
            {
                int newValue = dp[j - products[i - 1].weight] + products[i - 1].profit;
                if (newValue > dp[j])
                {
                    dp[j] = newValue;
                    choose[i][j] = true;
                }
            }
        }

        // 回溯找出選擇的物品
        vector<bool> finalChoose(n, false);
        int j = M;
        for (int i = n; i > 0; --i)
        {
            if (choose[i][j])
            {
                finalChoose[i - 1] = true;
                j -= products[i - 1].weight;
            }
        }

        cout << finalChoose << ", Max Profit: " << dp[M] << "(DP Answer)\n";
    }

    /*
    動態規劃五步法
    1. 構造問題: 在重量限制下找出最佳的價值組合
    2. 定義狀態: f(i, j) = 前 i 個物品, 重量 j 的最高價值
    3. 求解小規模的簡單問題:
        f(0, j) = 0
        f(i, 0) = 0
    4. 狀態轉移方程式:
        f(i, j) =
        {
            不選擇: f(i - 1, j)
            選擇: f(i - 1, j - weight[i - 1]) + value[i - 1]
        }
    5. 判斷複雜度: O(n *  mx)

    因為每次都只需要前一行的資訊, 而自己就可以扮演前一行, 所以能夠壓縮到一維。

    1. 構造問題: 在重量限制下找出最佳的價值組合
    2. 定義狀態: dp[j] = 重量 j 的最高價值
    3. 求解小規模的簡單問題:
        dp[0] = 0
    4. 狀態轉移方程式:
        每一輪都加入新的貨物, 更新一遍
        dp[j] = max(dp[j], dp[j - weight[i]] + value[i])
    5. 判斷複雜度: O(n * mx)
    */
};
OutputFormat Node::outputFormat = OutputFormat::DETAIL;
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        // 使用方式
        cout << "Usage: " << argv[0] << " <input_file_1> <input_file_2> ... <input_file_n>\n";
        return 1;
    }

    vector<Solution> solutions;
    // 傳入資料夾路徑

    // 傳入一堆檔案名稱
    for (int i = 1; i < argc; ++i)
    {
        Solution solution;
        solution.readFile(argv[i]);
        solutions.push_back(solution);
    }

    // 驗證錯誤
    for (auto &solution : solutions)
    {
        DynamicProgramming dp(solution);
        solution.solve();
        dp.solve();
        cout << "Press Enter to continue...";
        cin.ignore();
    }

    return 0;
}
/*
實做分支與定界演算法(branch and Bound)演算法
0/1背包問題 (n < 20)。
輸入檔案： M (容量) n (個數) p1 w1 p2 w2 ...pn wn
輸出：於螢幕輸出
輸出格式： 依搜尋過程展示展開節點的資訊，每節點一行 節點選擇情況 (以二進位格式表示) 輸出目前節點UB與LB。
例如: 1100101001 LB=100 UB=50 最後選擇結果 總獲利  
*/