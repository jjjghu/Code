#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main(void)
{
    vector<string> lines;
    string s;
    int mx = 0;
    while(getline(cin, s))
    {
        lines.push_back(s);
        mx = max(mx, (int)s.length());
    }
    for(int i = 0; i < mx; ++i)
    {
        for(int j = lines.size() - 1; j >= 0; --j)
        {
            if(i < lines[j].size())
            {
                cout << lines[j][i];
            }
            else
            {
                cout << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}