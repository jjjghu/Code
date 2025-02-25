#include <iostream>
using namespace std;
void print(int num, string s)
{
    cout << "Num then s";
}
void print(string s, int num)
{
    cout << "s then num";
}
int main(void)
{
    print(1, "hello");
    print("hello", 1);
    return 0;
}