#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int grid[25][25];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> grid[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            grid[i][j] += grid[i - 1][j] + grid[i][j - 1] - grid[i - 1][j - 1];
        }
    }

    int result = 0;
    for (int a = 1; a <= n; a++)
    {
        for (int b = 1; b <= n; b++)
        {
            for (int c = 0; c < a; c++)
            {
                for (int d = 0; d < b; d++)
                {
                    int temp = grid[a][b] - grid[a][d] + grid[c][d] - grid[c][b];
                    if (temp > result)
                        result = temp;
                }
            }
        }
    }
    cout << result << "\n";
}