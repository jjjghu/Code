#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
#define pdd pair<double, double>

int main(void) 
{
    vector<pdd> points(4);
    while(cin >> points[0].first >> points[0].second)
    {
        for(int i = 1; i < 4; ++i)
        {
            cin >> points[i].first >> points[i].second;
            // cout << fixed << setprecision(3) << points[i].first << " " << points[i].second;
        }
        // 0, 1, 2, 3
        pdd res;
        if(points[0] == points[2] || points[0] == points[3])
        {
            // 重複的是 0 
            double dx = points[1].first - points[0].first;
            double dy = points[1].second - points[0].second;
            if(points[0] == points[2])
            {
                res = {points[3].first + dx, points[3].second + dy};
            }
            else
            {
                res = {points[2].first + dx, points[2].second + dy};
            }
        }
        else 
        {
            // 重複的是 1 
            double dx = points[0].first - points[1].first;
            double dy = points[0].second - points[1].second;
            if(points[1] == points[2])
            {
                res = {points[3].first + dx, points[3].second + dy};
            }
            else
            {
                res = {points[2].first + dx, points[2].second + dy};
            }
        }
        cout << fixed << setprecision(3) << res.first << " " << res.second << endl;
    }
}