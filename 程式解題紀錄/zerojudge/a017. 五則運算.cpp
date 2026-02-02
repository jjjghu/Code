#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
using namespace std;
int where;
void push(vector<int>& nums, vector<char>& oper, int cur, char op) {
    int n = nums.size();
    if(n == 0 || oper.back() == '+' || oper.back() == '-') {
        nums.push_back(cur);
        oper.push_back(op);
    }
    else { // * / % 
        if(oper.back() == '*') {
            nums.back() *= cur;
        }
        else if(oper.back() == '/') {
            nums.back() /= cur;
        }
        else { // % 
            nums.back() %= cur;
        }
        oper.back() = op;
    }
}
int dfs(string& s, int i) {
    vector<int> nums;
    vector<char> oper;
    int cur = 0;
    while(i < s.length() && s[i] != ')') {
        if(isdigit(s[i])) {
            cur = cur * 10 + (s[i++] - '0');
        }
        else if(s[i] != '(') { // + - * / %
            push(nums, oper, cur, s[i++]);
            cur = 0;
        }
        else { // (
            cur = dfs(s, i + 1);
            i = where + 1;
        }
    }
    push(nums, oper, cur, '+');
    where = i;
    int res = nums[0];
    for(int i = 1; i < nums.size(); ++i) {
        res += oper[i - 1] == '+' ? nums[i] : -nums[i];
    }
    return res;
}
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while(getline(cin, line)) {
        stringstream ss(line);
        string temp, s;
        while(ss >> temp) {
            s += temp;
        }
        if(!s.empty()) {
            cout << dfs(s, 0) << "\n";
        }
    }
}