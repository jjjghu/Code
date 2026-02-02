#include <iostream>
#include <stack>
#include <random>
using namespace std;
int getDepth(stack<int>& stk) {
    if(stk.empty()) {
        return 0;
    }
    int top = stk.top(); stk.pop();
    int depth = 1 + getDepth(stk);
    stk.push(top);
    return depth;
}
int findMax(stack<int>& stk, int depth) {
    if(depth == 0) {
        return INT_MIN;
    }
    int top = stk.top(); stk.pop();
    int mx = max(top, findMax(stk, depth - 1));
    stk.push(top);
    return mx;

}
int cnt(stack<int>& stk, int depth, int mx) {
    if(depth == 0) {
        return 0;
    }
    int top = stk.top(); stk.pop();
    int res = top == mx ? 1 : 0;
    res += cnt(stk, depth - 1, mx);
    stk.push(top);
    return res;
}
void down(stack<int>& stk, int depth, int mx, int k) {
    if(depth == 0) {
        for(int i = 0; i < k; ++i) {
            stk.push(mx);
        }
    }
    else {
        int top = stk.top(); stk.pop();
        down(stk, depth - 1, mx, k);
        if(top != mx) {
            stk.push(top);
        }
    }
}
void sort(stack<int>& stk) {
    int depth = getDepth(stk);
    while(depth > 0) {
        int mx = findMax(stk, depth);
        int k = cnt(stk, depth, mx);
        down(stk, depth, mx, k);
        depth -= k;
    }
}
int main(void) {
    const int n = 10;
    stack<int> stk;
    srand(NULL);
    for(int i = 0; i < n; ++i) {
        stk.push(rand());
    }
    sort(stk);
    while(!stk.empty()) {
        cout << stk.top() << endl;
        stk.pop();
    }
}