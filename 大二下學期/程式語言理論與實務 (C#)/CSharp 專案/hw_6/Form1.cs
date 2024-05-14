using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms.Design;
using System.Windows.Forms.VisualStyles;

namespace hw_6
{

    public partial class Form1 : Form
    {
        string[,] relation = new string[200, 40];
        int recNo, rank;
        string KING;
        public Form1()
        {
            InitializeComponent();
        }
        string findParent(string king)
        {
            for(int i=0; i < recNo; i++)
            { 
                for(int j = 2; j < 40; ++j)
                {
                    string temp = relation[i,j];
                    if(temp == king)
                    {
                        return relation[i,0];
                    }
                }
            }
            return string.Empty;
        }

        void solve(string p)
        {
            // 從頭到尾找一遍
            for (int i = 0; i < recNo; ++i)
            {
                // 找到當前這個人
                string temp = relation[i, 0];

                if (temp == p)
                {
                    // relation[i] 全部看一遍, 先看男生, 再看女生
                    for (int j = 2; j < 40; j += 2)
                    {
                        // 沒死且為男生
                        if (relation[i, j + 1] == "(M)")
                        {
                            // 輸出他和他的solve
                            if (KING != relation[i, j])
                            {
                                textBox1.Text += rank + ": " + relation[i, j] + "\r\n";
                                ++rank;
                            }
                            solve(relation[i, j]);

                        }
                        else if (relation[i, j + 1] == "(MD)")
                            solve(relation[i, j]);
                    }
                    for (int j = 2; j < 40; j += 2)
                    {
                        // 沒且為女生, 或是不合法的男生 (???
                        if (relation[i, j + 1] == "(F)" || relation[i,j+1] == "(MN)")
                        {
                            // 輸出她和她的solve
                            if (KING != relation[i, j])
                            {
                                textBox1.Text += rank + ": " + relation[i, j] + "\r\n";
                                ++rank;
                            }
                            solve(relation[i, j]);
                        }
                        else if (relation[i, j + 1] == "(FD)"|| relation[i, j + 1] == "(MND)")
                            solve(relation[i, j]);
                    }
                }
            }
            // 解決掉國王的兄弟姊妹? YES

            return;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            // reset memory
           for(int i=0;i<200; ++i)
            {
                for(int j=0;j<40;++j)
                {
                    relation[i, j] = "";
                }
            }
            textBox1.Text = string.Empty;
            // 開啟檔案, 類型為 string
            openFileDialog1.Filter = "文字文件(*.txt)|*.txt";
            // 判斷檔案正確打開
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                // 讀取檔案
                StreamReader sr = new StreamReader(openFileDialog1.FileName);
                string[] king = sr.ReadLine().Split();
                // 獲取當前國王
                recNo = 0;
                rank = 1;
                while(sr.Peek() >= 0)
                {
                    string[] s = sr.ReadLine().Split();
                    if (s[0] == string.Empty) continue;
                    //textBox1.Text += "relation[" + recNo + "] = \r\n";
                    for (int i = 0; i < s.Length; i++)
                    {
                        relation[recNo, i] = s[i];
                        //textBox1.Text += s[i] + "\trecNo = " + recNo + "\ti = " + i + "\r\n";
                    }
                    //textBox1.Text += "\r\n";
                    recNo++;
                }
                // 從國王開始解
                KING = king[0];
                // 將陣列歸零
                
                solve(findParent(king[0]));
                sr.Close();
            }
        }
    }
}
