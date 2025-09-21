#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int solve()
{
    int n, p, num;
    cin >> n >> p;
    vector<bool> days(n + 1, false);
    for(int i = 0; i < p; ++i)
    {
        cin >> num;
        int current = num;
        while(current <= n)
        {
            days[current] = true;
            current += num;
        }
    }

    //days[0] = Sunday
    int day = 6; // Friday
    while(day <= n)
    {
        days[day] = false; // Friday
        if(day + 1 <= n) days[day + 1] = false; // Saturday
        day += 7;
    }
    return count(days.begin(), days.end(), true);
}
int main(void)
{
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i)
    {
        cout << solve() << endl;
    }
}