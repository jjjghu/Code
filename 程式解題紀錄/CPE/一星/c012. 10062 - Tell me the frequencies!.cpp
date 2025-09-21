#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
int main(void)
{
    string s;
    while(getline(cin, s))
    {
        unordered_map<char, int> freq;
        for(char c : s)
        {
            ++freq[c];
        }
        vector<pair<char, int>> vec(freq.begin(), freq.end());
        sort(vec.begin(), vec.end(), [](pair<char, int> a, pair<char, int> b){
            if(a.second != b.second) return a.second < b.second;
            return a.first > b.first;
        });
        for(pair<char, int>& p : vec)
        {
            cout << (int)(p.first) << " " << p.second << endl;
        }
        cout << endl;
    }
}