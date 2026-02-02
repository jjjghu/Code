#include <iostream>
#include <stack>
using namespace std;

int bottomOut(stack<int>& stk) {
    int res = stk.top();
    stk.pop();
    if(stk.empty()) { 
        return res; // 這是最底的元素
    }
    else {
        int last = bottomOut(stk); // 先取出最底的元素
        stk.push(res); // 再把原本的數值壓回去
        return last;
    }
}

void reverse(stack<int>& stk) {
    if(stk.empty()) {
        return;
    }
    else {
        int last = bottomOut(stk); // 取出最底的元素
        reverse(stk); // 反轉剩下的
        stk.push(last); // 壓回
    }
}

int main(void) {
    const int n = 5;
    stack<int> stk;
    for(int i = 1; i <= n; ++i) {
        stk.push(i);
    }
    reverse(stk);
    while(!stk.empty()) {
        cout << stk.top() << endl;
        stk.pop();
    }
}