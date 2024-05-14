namespace hw_2
{
    public partial class Form1 : Form
    {
        private const int mxN = 100;
        private string[,] name = new string[mxN, 2];
        private int[,] score = new int[mxN, 2];
        int cnt = 0;
        double sum1 = 0, sum2 = 0;
        string res = "學號\t姓名\t國文\t數學\r\n";
        string begin = "搜尋結果:\r\n學號\t姓名\t國文\t數學\r\n";
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            update();
        }
        private void update()
        {
            textBox1.Text = res;
            textBox2.Text = String.Empty;
            textBox3.Text = String.Empty;
            textBox4.Text = String.Empty;
            textBox5.Text = String.Empty;
            textBox6.Text = Convert.ToString(cnt);
            if (cnt != 0)
            {
                textBox7.Text = Convert.ToString(sum1 / cnt);
                textBox8.Text = Convert.ToString(sum2 / cnt);
            }
            else
            {
                textBox7.Text = "0";
                textBox8.Text = "0";
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox2.Text == String.Empty) throw new Exception("請輸入學號");
                if (textBox3.Text == String.Empty) throw new Exception("請輸入姓名");
                if (textBox4.Text == String.Empty) throw new Exception("請輸入國文成績");
                if (textBox5.Text == String.Empty) throw new Exception("請輸入數學成績");
                name[cnt, 0] = textBox2.Text;
                name[cnt, 1] = textBox3.Text;
                score[cnt, 0] = Convert.ToInt32(textBox4.Text);
                score[cnt, 1] = Convert.ToInt32(textBox5.Text);
                ++cnt;
                sum1 += Convert.ToInt32(textBox4.Text);
                sum2 += Convert.ToInt32(textBox5.Text);
                res = res + textBox2.Text + "\t" + textBox3.Text + "\t" + textBox4.Text + "\t" + textBox5.Text + "\r\n";
                update();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "錯誤訊息", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }
        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                bool find = false;
                for (int i = 0; i < cnt; ++i)
                {
                    if (name[i, 0] == textBox2.Text)
                    {
                        if (find == false)
                        {
                            find = true;
                            textBox1.Text = begin;
                        }
                        textBox1.Text += name[i, 0] + "\t" + name[i, 1] + "\t" + score[i, 0] + "\t" + score[i, 1] + "\r\n";
                    }
                }
                if (find == false) throw new Exception("資料不存在");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "搜尋學號" + textBox2.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

        }

        private void button3_Click(object sender, EventArgs e)
        {
            update();
        }
    }
}
