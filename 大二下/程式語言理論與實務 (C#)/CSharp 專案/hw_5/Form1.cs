using System.Numerics;

namespace hw5
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "二元檔案(*.dat)|*.dat";
            if(openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                FileStream fs = new FileStream(openFileDialog1.FileName, FileMode.Open);
                BinaryReader br = new BinaryReader(fs);
                textBox1.Text = "";
                // cn 獲取共有幾個候選人
                int cn = br.ReadInt32();
                // bn 獲取有幾個投票人
                int bn = br.ReadInt32();
                // 紀錄投票資訊
                int[,] ballot = new int[bn, cn];
                //紀錄每個候選人的得票情況
                int[] count = new int[cn];
                // 紀錄有哪些候選人被淘汰
                bool[] alive = new bool[cn];
                // 輸入測資
                for(int i=0;i<bn;++i)
                {
                    for(int j=0;j<cn;++j)
                    {
                        ballot[i,j] = br.ReadInt32();
                    }
                }
                // 一開始都活著
                for(int i=0;i<cn;++i)
                {
                    alive[i] = true;
                }
                int death = 0;
                int round = 1;
                /*
                顯示當前投票狀態
                textBox1.Text += cn + " \r\n";
                textBox1.Text += bn + " \r\n";
                for (int i = 0; i < bn; ++i)
                {
                    for (int j = 0; j < cn; ++j)
                    {
                        textBox1.Text += ballot[i, j] + "  ";
                    }
                    textBox1.Text += "\r\n";
                }
                */
                // 正式開始投票
                while (true)
                {
                    textBox1.Text += "第" + round + "回合:\r\n";
                    // 初始化投票狀態
                    for (int i = 0; i < cn; ++i)
                        count[i] = 0;
                    // 紀錄票數
                    for (int i = 0; i < bn; ++i)
                    {
                        for(int j = 0; j < cn; ++j)
                        {
                            // 將第一優先的候選人票數增加, 透過Alive判斷
                            if (alive[ballot[i, j]-1])
                            {
                                count[ballot[i, j]-1]++;
                                break;
                            }
                        }
                    }
                    // 紀錄完票數之後 計算結果
                    int min = int.MaxValue;
                    int max = int.MinValue;
                    //textBox1.Text += "現在投票情況: ";
                    for (int i=0;i<count.Length; ++i)
                    {
                        //textBox1.Text += count[i] + " ";
                        // 確保候選人活著
                        if (alive[i] == true)
                        {
                            // 獲取選票最小和最大的候選人
                            min = Math.Min(min, count[i]);
                            max = Math.Max(max, count[i]);
                        }
                    }
                    //textBox1.Text += "\r\n";
                    // 沒有過半數的時候, 開始淘汰階段
                    if(max <= bn / 2)
                    {
                        bool haveDeath = false;
                        for (int i = 0; i < count.Length; ++i)
                        {
                            // 如果得票數最低, 候選人GG
                            if (count[i] == min && alive[i] == true)
                            {
                                alive[i] = false;
                                textBox1.Text += "號碼" + (int)(i + 1) + "候選人 ";
                                ++death;
                                haveDeath = true;
                            }
                        }
                        if (haveDeath)
                        {
                            textBox1.Text += "本回合最低票被淘汰\r\n\r\n";
                            ++round;
                            continue;
                        }
                    }
                    else // 過半數, 直接宣告勝利
                    {
                        for(int i=0;i<count.Length; ++i)
                        {
                            if (alive[i] == true && max == count[i])
                            {
                                textBox1.Text += "號碼" + (i+1) + "候選人過半數當選\r\n\r\n";
                                return;
                            }
                        }
                    }
                    ++round;
                    // 無人生還
                    if (death == cn)
                    {
                        textBox1.Text += "無法決定當選者\r\n";
                        return;
                    }
                       
                }
            }
        }
    }
}
