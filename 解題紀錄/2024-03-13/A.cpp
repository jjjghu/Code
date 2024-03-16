// UVA 1225 Digit Counting
#include <iostream>
using namespace std;
int main(void)
{
    int n;
    cin >> n;
    while (n--)
    {
        int appear[10] = {0};
        int enter;
        cin >> enter;
        for (int i = 0; i <= enter; ++i)
        {
            // count for each number
            int temp = i;
            while (temp)
            {
                appear[temp % 10]++;
                temp /= 10;
            }
        }
        for (int i = 0; i < 10; i++)
        {
            if (i == 0)
                cout << appear[i];
            else
                cout << " " << appear[i];
        }
        cout << endl;
    }
    return 0;
}
/*
 0 1 2 3 4 5 6 7 8 9
10111213141516171819
20212223242526272829
...
90919293949596979899
*/