#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using pii = pair<int,int>;
int main(void)
{
    int n = 8;
    int dx[8] = {1, 1, -1, -1, 2, -2, 2, -2};
    int dy[8] = {2, -2, 2, -2, 1, 1, -1, -1};  
    string start, target;
    
    auto solve = [&]()
    {
        
        if(target == start)
        {
            return 0;
        }

        int targetX = target[0] - 'a';
        int targetY = target[1] - '1';
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        
        queue<pii> q;
        q.emplace(start[0] - 'a', start[1] - '1');
        visited[start[0] - 'a'][start[1] - '1'] = true;
        int step = 0;
        while(!q.empty())
        {
            int size = q.size();
            ++step;
            while(size--)
            {
                pii cur = q.front();
                q.pop();
                
                int x = cur.first, y = cur.second;
                for(int i = 0; i < 8; ++i)
                {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= n || visited[nx][ny])
                    {
                        continue;
                    }
                    if(nx == targetX && ny == targetY)
                    {
                        return step;
                    }
                    visited[nx][ny] = true;
                    q.emplace(nx, ny);
                }
            }
        }
        return -1;
    };

    while(cin >> start >> target)
    {
        printf("To get from %s to %s takes %d knight moves.\n", start.c_str(), target.c_str(), solve());
    }
}
/*

a8 b8 c8 d8 e8 f8 g8 h8
a7 b7 c7 d7 e7 f7 g7 h7
a6 b6 c6 d6 e6 f6 g6 h6
a5 b5 c5 d5 e5 f5 g5 h5
a4 b4 c4 d4 e4 f4 g4 h4
a3 b3 c3 d3 e3 f3 g3 h3
a2 b2 c2 d2 e2 f2 g2 h2
a1 b1 c1 d1 e1 f1 g1 h1

騎士的移動方法: L形
*/