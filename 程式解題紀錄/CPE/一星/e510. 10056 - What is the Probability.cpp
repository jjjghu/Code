#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double solve(int player, double prob, int target)
{
    if(prob == 0) return 0.0;

    /* 
        x = (1 - prob) ^ (target - 1) * prob
        y = (1 - prob) ^ (player) 
        x + x * y + x * y^2 + ... = x(1 + y + y^2 + y^3 + ...)
        y + y^2 + y^3 + ... =  1 / 1 - y
        res = x / (1 - y)
    */
    double numerator = pow(1 - prob, target - 1) * prob;
    double denominator = 1 - pow(1 - prob, player);
    return numerator / denominator;
}
int main(void)
{
    int s;
    cin >> s;

    int player, target;
    double prob;
    for(int i = 0;i  < s; ++i)
    {
        cin >> player >> prob >> target;
        cout << fixed << setprecision(4) << solve(player, prob, target) << endl;
    }
}