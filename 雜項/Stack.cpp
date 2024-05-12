#include <bits/stdc++.h>
using namespace std;
int order(char c)
{
    string list = "-+>%/*";
    
    if (c == '/' || c == '*')
        return 3;
    else if (c == '%' || c == '>')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}
char check(char c)
{
    if (c == '^')
        return 'R';
    return 'L';
}

void convert(string s)
{
    stack<char> st;
    string result;

    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            result += c;
        else if (c == '(')
            st.push('(');
        else if (c == ')')
        {
            while (st.top() != '(')
            {
                result += st.top();
                st.pop();
            }
            st.pop();
        }
        else
        {
            while (!st.empty() && order(s[i]) < order(st.top()) ||
                   !st.empty() && order(s[i]) == order(st.top()) &&
                       check(s[i]) == 'L')
            {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty())
    {
        result += st.top();
        st.pop();
    }
    cout << result << endl;
}

int main()
{
    string s = "A+B*C%(D+((E*F-G/H)*I-J)*K+L)*M-N*P";
    convert(s);
    return 0;
}
