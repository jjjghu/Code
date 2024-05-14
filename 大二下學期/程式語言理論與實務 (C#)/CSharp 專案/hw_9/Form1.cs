using System.Collections.Generic;
namespace hw_9
{
    public partial class Form1 : Form
    {
        private Stack<char> stk;
        private string res = string.Empty;
        public Form1()
        {
            InitializeComponent();
            stk = new Stack<char>();
        }
        int order(char c)
        {
            if(c == '*' || c == '/' || c == '%')
                return 2;
            else if(c == '+' || c == '-')
                return 1;
            else
                return -1;
        }
        private string InfixToPostfix(string s)
        {
            stk.Clear();
            res = "";
            for (int i = 0; i < s.Length; i++)
            {
                if (s[i] == ' ')
                    continue;
                char c = s[i];
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                    res += c;
                else if (c == '(')
                    stk.Push('(');
                else if (c == ')')
                {
                    while (stk.Peek() != '(')
                    {
                        res += stk.Peek();
                        stk.Pop();
                    }
                    stk.Pop();
                }
                else
                {
                    while (stk.Count != 0 && order(s[i]) <= order(stk.Peek()))
                    {
                        res += stk.Peek();
                        stk.Pop();
                    }
                    stk.Push(c);
                }
            }
            while (stk.Count != 0)
            {
                res += stk.Peek();
                stk.Pop();
            }
            return res;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBox2.Text = InfixToPostfix(textBox1.Text);
        }
    }
}
