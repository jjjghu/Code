#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;
int main(void)
{
    // earth radius
    const double R = 6440.0;
    double s, a;
    string unit;
    while(cin >> s >> a >> unit) 
    {
        double radius = R + s;
        double angle = a;
        
        // 單位轉換
        if(unit == "min")
        {
            angle /= 60.0;
        }
        if(angle > 180.0)
        {
            angle = 360 - angle;
        }
        
        // 套公式
        double theta = angle * M_PI / 180.0;

        double arc = radius * theta;
        double chord = 2.0 * radius * sin(theta / 2.0);
        cout << fixed << setprecision(6) << arc << " " << chord << endl;
    }
}
/*
記得這個公式
arc = rθ
chord = 2r * sin(θ/2)
 */