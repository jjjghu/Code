#include <iostream>
#include <map>
#include <iomanip>
using namespace std;
int main(void) 
{
    int n; 
    cin >> n;
    
    string s;
    cin.ignore();// \n
    getline(cin, s);// 空白行
    while(n--)
    {
        int sum = 0;
        map<string, int> freq;
        while(getline(cin, s) && s != "")
        {
            ++freq[s];
            ++sum;
        }
        for(auto& kv : freq)
        {  
            cout << kv.first << " " << fixed << setprecision(4) << 1.0 * kv.second / sum * 100 << endl;
        }
        cout << endl;
    }
}