namespace hw_15
{
    public partial class Form1 : Form
    {
        List<string>[] table = new List<string>[13];
        TextBox[] arr = new TextBox[13];
        private IHashStrategy currentStrategy = null!;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            for (int i = 0; i <= 12; i++)
            {
                table[i] = new List<string>();
            }
            arr[0] = textBox4;
            arr[1] = textBox5;
            arr[2] = textBox6;
            arr[3] = textBox7;
            arr[4] = textBox8;
            arr[5] = textBox9;
            arr[6] = textBox10;
            arr[7] = textBox11;
            arr[8] = textBox12;
            arr[9] = textBox13;
            arr[10] = textBox14;
            arr[11] = textBox15;
            arr[12] = textBox16;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // 新增
            SetStrategy(new AddHashStrategy());
            ExecuteStrategy(textBox1.Text);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // 刪除
            SetStrategy(new DeleteHashStrategy());
            ExecuteStrategy(textBox1.Text);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            // 查詢
            SetStrategy(new SearchHashStrategy());
            ExecuteStrategy(textBox1.Text);
        }
        private void SetStrategy(IHashStrategy strategy)
        {
            currentStrategy = strategy;
        }
        private void ExecuteStrategy(string str)
        {
            if (currentStrategy != null)
            {
                currentStrategy.Execute(this, str);
            }
        }
        public void AddHash(string str)
        {
            try
            {
                string fold;
                int total;
                bool found;
                addHash(str, out fold, out total, out found);
                textBox2.Text = fold;
                textBox3.Text = total + " % 13 = " + total % 13;
                if (found)
                {
                    throw new Exception("授權碼" + str + "重複");
                }
                else
                {
                    table[total % 13].Add(str);
                }
                printHash();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "新增失敗", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        public void DeleteHash(string str)
        {
            try
            {
                bool found;
                searchHash(str, out found);
                if (!found)
                {
                    throw new Exception("授權碼" + str + "不存在");
                }
                else
                {
                    for (int i = 0; i <= 12; i++)
                    {
                        if (table[i].Contains(str))
                        {
                            table[i].Remove(str);
                            break;
                        }
                    }
                }
                printHash();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "刪除失敗", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        public void SearchHash(string str)
        {
            bool found;
            searchHash(str, out found);
            if (!found)
            {
                MessageBox.Show("授權碼" + str + "不存在", "查詢授權碼", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("授權碼" + str + "正確", "查詢授權碼", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
        private void addHash(string str, out string fold, out int total, out bool found)
        {
            // 使用 folding, 單位為 3
            // ex: str = 123456789012 => fold: 123654789210 => total = 123 + 654 + 789 + 210
            fold = "";
            total = 0;

            // not null or empty
            if (string.IsNullOrEmpty(str))
            {
                throw new Exception("請輸入授權碼");
            }

            // folding
            bool reverse = false;
            for (int i = 0; i < str.Length; i += 3)
            {
                // 不超出長度
                int length = Math.Min(3, str.Length - i);
                string part = str.Substring(i, length);
                char[] partArray = part.ToCharArray();
                if (reverse)
                    Array.Reverse(partArray);
                fold += new string(partArray);
                reverse = !reverse;
            }

            // 計算總和
            for (int i = 0; i < fold.Length; i += 3)
            {
                int length = Math.Min(3, fold.Length - i); // 確保不會超出字符串長度
                string part = fold.Substring(i, length);
                // 不足 3 位時右側補 0 以確保能正確轉換為數字
                total += int.Parse(part);
            }
            searchHash(str, out found);
        }
        private void searchHash(string str, out bool found)
        {
            found = false;
            // 檢查是否在表中找到相同的授權碼
            foreach (List<string> list in table)
            {
                if (list.Contains(str))
                {
                    found = true;
                    break;
                }
            }
        }
        private void printHash()
        {
            for (int i = 0; i <= 12; i++)
            {
                arr[i].Text = "";
                for (int j = 0; j < table[i].Count; j++)
                {
                    arr[i].Text += " -> " + table[i][j];
                }
            }
        }
    }
}
