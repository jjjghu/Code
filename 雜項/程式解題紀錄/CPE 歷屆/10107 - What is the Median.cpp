#include <iostream>
#include <set>
using namespace std;
int main(void)
{
    int enter;
    int cnt = 0;
    multiset<int> mset;
    while (cin >> enter)
    {
        mset.insert(enter);
        ++cnt;
        // auto = multiset<int>::iterator
        auto it = mset.begin();
        advance(it, mset.size() / 2);
        if (cnt & 1)
            cout << *it << endl;
        else
            cout << (*it + *(--it)) / 2 << endl;
    }
}