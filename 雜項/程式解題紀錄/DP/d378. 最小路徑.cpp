#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(void)
{
    int n, m;
    int t = 1;
    while (cin >> n >> m)
    {
        cout << "Case #" << t++ << " :\n";
        vector<vector<int>> grid(n, vector<int>(m, 0));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                cin >> grid[i][j];
            }
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (!i && !j)
                    continue;
                if (!i)
                {
                    grid[i][j] += grid[i][j - 1];
                    continue;
                }
                if (!j)
                {
                    grid[i][j] += grid[i - 1][j];
                    continue;
                }
                grid[i][j] = min(grid[i - 1][j], grid[i][j - 1]) + grid[i][j];
            }
        }
        cout << grid[n - 1][m - 1] << "\n";
    }
}
/*
動態規劃五步法
1. 構造問題: 輸出走到右下角的最小總和
2. 定義狀態: f(i, j) 表示走道座標 i, j 的最小總和
3. 求解小規模的簡單問題:
    f(0, 0) = 0
    f(0, j) = 列總和
    f(i, 0) = 行總和
4. 狀態轉移方程式:
    f(i, j) = min(f(i - 1, j), f(i, j - 1)) + grid[i][j]
5. 判斷複雜度: O(n)
*/