#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
int main(void)
{
    vector<string> vec;
    vec.push_back("~!@#$%^&*()_+");
    vec.push_back("`1234567890-=");
    vec.push_back("qwertyuiop[]\\");
    vec.push_back("asdfghjkl;'");
    vec.push_back("zxcvbnm,./");
    
    unordered_map<char, char> umap;
    for(string s : vec) {
        for(int j = 2; j < s.length(); ++j) {
            umap[s[j]] = s[j - 2];
        }
    }

    string s;
    while(getline(cin, s)) 
    {
        for(char c : s) 
        {
            if(umap.find(c) != umap.end())
                cout << umap[c];
            else
                cout << c;
        }
        cout << endl;
    }
}
/*
第一行有兩種，按下與放開 shift
~!@#$%^&*()_+
`1234567890-=
qwertyuiop[]\\
asdfghjkl;'
zxcvbnm,./
*/