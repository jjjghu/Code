#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main(void)
{
    int n;
    cin >> n;

    string s;
    vector<pair<int,int>> alpha(26);// cnt, index
    for(int i = 0; i < 26; ++i)
    {
        alpha[i] = {0, i};
    }
    while(getline(cin, s))
    {
        for(char c : s)
        {
            if(isalpha(c))
            {
                c = tolower(c);
                ++alpha[c - 'a'].first;
            }
        }
    }
    sort(alpha.begin(), alpha.end(), [](pair<int,int> a, pair<int,int> b){
        if(a.first != b.first)
            return a.first > b.first;
        return a.second < b.second;
    });
    for(pair<int,int> p : alpha)
    {
        if(p.first == 0) break;
        cout << (char)(p.second + 'A') << " " << p.first << endl;  
    }
    return 0;
}