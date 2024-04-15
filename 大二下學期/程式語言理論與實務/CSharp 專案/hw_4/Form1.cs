using System.Diagnostics;
using System.IO;
using System.Text;
namespace hw_4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                openFileDialog1.Filter = "Excel檔案(*.csv)|*.csv";
                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    StreamReader sr = new StreamReader(openFileDialog1.FileName, Encoding.Default);
                    string[] input = new string[4];
                    string[] name = new string[100];
                    int[] num = new int[100];
                    double[,] coord = new double[100, 2];
                    double x = Convert.ToDouble(textBox1.Text);
                    double y = Convert.ToDouble(textBox2.Text);
                    textBox6.Text = "姓名\t需求量\tX座標\t\tY座標\r\n";
                    int demand = 0;
                    int cnt = 0;
                    double distance = 0;
                    while (sr.Peek() >= 0)
                    {
                        // 逗號分割
                        input = sr.ReadLine().Split(',');
                        cnt++;
                        demand += Convert.ToInt32(input[1]);
                        distance += Math.Sqrt(Math.Pow(Convert.ToDouble(input[2]) - x, 2)+Math.Pow(Convert.ToDouble(input[3]) - y, 2));
                        for (int i = 0; i < input.Length; i++)
                        {
                            textBox6.Text += input[i];
                            textBox6.Text += "\t";
                        }
                        textBox6.Text += "\r\n";
                    }
                    textBox3.Text = "" + cnt;
                    textBox4.Text = "" + demand;
                    textBox5.Text = "" + distance/cnt;
                    sr.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"{ex.Message}"); // 跳出訊息框框 ! 
            }
        }
    }
}
