#include <iostream>
#include <string>
#include <vector>
using namespace std;

void solve(long long num, string& res, bool addSpace = false)
{
    if(num == 0) return;

    vector<pair<string, long long>> units = 
    {
        {" kuti", 10000000LL}, 
        {" lakh", 100000LL}, 
        {" hajar", 1000LL}, 
        {" shata", 100LL}
    };

    for(auto& p : units) 
    {
        if(num >= p.second)
        {
            long long div = num / p.second;
            num %= p.second;

            // 處理多層 kuti
            if(p.first == " kuti") 
            {
                solve(div, res, addSpace);
                addSpace = true;
                res += " kuti";
            }
            else
            {
                if(addSpace) res += " ";
                res += to_string(div) + p.first;
                addSpace = true;
            }
        }
    }

    if(num != 0)
    {
        if(addSpace) res += " ";
        res += to_string(num);
    }
}

int main(void)
{
    long long num;
    int t = 1;
    while(cin >> num)
    {
        string res;
        if(num == 0)
        {
            res = "0";
        }
        else
        {
            solve(num, res);
        }
        cout << "    " << t << ". " << res << endl;
        ++t;
    }
}
