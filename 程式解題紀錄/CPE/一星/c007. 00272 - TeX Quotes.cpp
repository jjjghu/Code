#include <iostream>
using namespace std;
int main(void)
{
    string line;
    bool open = true;
    while(getline(cin, line))
    {
        for(char ch : line)
        {
            if(ch == '"')
            {
                if(open)
                    cout << "``";
                else
                    cout << "''";
                open = !open;
            }
            else
            {
                cout << ch;
            }
        }
        cout << endl;
    }
    return 0;
}