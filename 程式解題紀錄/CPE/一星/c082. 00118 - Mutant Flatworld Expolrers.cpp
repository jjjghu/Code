#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

// 上 {0, -1}
// 右 {1, 0}
// 下 {0, 1}
// 左 {-1, 0}
// 右轉 index + 1
// 左轉 index - 1
vector<int> dx = {0, 1, 0, -1}; // NESW
vector<int> dy = {1, 0, -1, 0};
unordered_map<char, int> umap = {{'N', 0}, {'E', 1}, {'S', 2}, {'W', 3}};
vector<char> dir_char = {'N', 'E', 'S', 'W'};
int m, n;
set<pair<int,int>> scent;
void solve(int x, int y, char facing, string cmd)
{
    int index = umap[facing];
    bool lost = false;
    for(char c : cmd)
    {
        if(c == 'L')
        {
            index = (index + 3) % 4;
        }
        else if(c == 'R')
        {
            index = (index + 1) % 4;
        }
        else if(c == 'F')
        {
            int nx = x + dx[index];
            int ny = y + dy[index];
            if(nx < 0 || ny < 0 || nx > m || ny > n)
            {
                if(scent.find({x, y}) != scent.end())
                {
                    continue;
                }
                else
                {
                    scent.insert({x, y});
                    lost = true;
                    break;
                }
            }
            else
            {
                x = nx;
                y = ny;
            }
        }
    }
    cout << x << " " << y << " " << dir_char[index];
    if(lost) cout << " LOST";
    cout << endl;
    return;
}
int main(void)
{

    cin >> m >> n;

    int x, y;
    char facing;
    string cmd;
    while(cin >> x >> y >> facing >> cmd)
    {
        solve(x, y, facing, cmd);
    }
}