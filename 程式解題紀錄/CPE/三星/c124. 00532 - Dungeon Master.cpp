#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;
int main(void)
{
    int layer, row, col;
    while(cin >> layer >> row >> col)
    {
        if(layer == 0 && row == 0 && col == 0)
        {
            return 0;
        }
        // layer, row, col;
        vector<vector<vector<char>>> grid(layer, vector<vector<char>>(row, vector<char>(col)));
        queue<tuple<int,int,int,int>> q; // l, r, c, step;
        for(int l = 0; l < layer; ++l)
        {
            for(int r = 0; r < row; ++r)
            {
                for(int c = 0; c < col; ++c)
                {
                    cin >> grid[l][r][c];
                    if(grid[l][r][c] == 'S')
                    {
                        grid[l][r][c] = '#';
                        q.emplace(l, r, c, 0);
                    }
                }
            }
        }

        int dz[6] = {-1, 1, 0, 0, 0, 0};
        int dx[6] = {0, 0, -1, 1, 0, 0};
        int dy[6] = {0, 0, 0, 0, -1, 1};

        auto bfs = [&](){
            while(!q.empty())
            {
                tuple<int,int,int,int> cur = q.front(); // layer, x, y, dist
                q.pop();
                int l = get<0>(cur);
                int x = get<1>(cur);
                int y = get<2>(cur);
                int d = get<3>(cur);
                for(int i = 0; i < 6; ++i)
                {
                    int nl = l + dz[i];
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    // 越界或是牆壁
                    if(nl < 0 || nl >= layer || nx < 0 || nx >= row || ny < 0 || ny >= col || grid[nl][nx][ny] == '#')
                    {
                        continue;
                    }
                    if(grid[nl][nx][ny] == 'E')
                    {
                        return d + 1;
                    }
                    grid[nl][nx][ny] = '#';
                    q.emplace(nl, nx, ny, d + 1);
                }
            }
            return 0;
        };

        int res = bfs();
        if(res)
        {
            cout << "Escaped in " << res << " minute(s)." << endl;
        }
        else
        {
            cout << "Trapped!" << endl;
        }
    }
}