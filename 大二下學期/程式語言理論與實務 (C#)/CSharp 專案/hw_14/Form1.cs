using System;
using System.Diagnostics.CodeAnalysis;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Globalization;
using System.Windows.Forms;

namespace hw_14
{
    public partial class Form1 : Form
    {
        TextBox[,] board = new TextBox[10, 10];
        int[,] initial = new int[10, 10];
        int[,] shortest = new int[10, 10];

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            int textBoxSize = 50; // 每個 TextBox 的大小（寬和高）

            // 指定左上角的起始位置
            int startX = 100;
            int startY = 50;

            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    TextBox textBox = new TextBox
                    {
                        Width = textBoxSize,
                        Top = startY + i * 20,
                        Left = startX + j * textBoxSize,
                        Name = $"textBox{i * 10 + j + 1}",
                        TextAlign = HorizontalAlignment.Center, // 置中
                        BorderStyle = BorderStyle.FixedSingle, // 描邊
                        Font = new Font("Arial", 8, FontStyle.Regular) // 設置字體大小和樣式
                    };
                    board[i, j] = textBox;
                    this.Controls.Add(textBox);
                }
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            maskedTextBox1.Text = solve(initial).ToString();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            //存檔
            saveFileDialog1.Filter = "二元檔案(*.dat)|*.dat";
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                FileStream fs = new FileStream(saveFileDialog1.FileName, FileMode.Create);
                BinaryWriter bw = new BinaryWriter(fs);
                int i, j;
                for (i = 0; i < 10; i++)
                {
                    for (j = 0; j < 10; j++)
                    {
                        bw.Write(board[i, j].Text);
                    }
                }
                bw.Flush();
                bw.Close();
                fs.Close();
            }
        }
        private void button3_Click(object sender, EventArgs e)
        {
            // 讀檔
            openFileDialog1.Filter = "二元檔案(*.dat)|*.dat";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                FileStream fs = new FileStream(openFileDialog1.FileName, FileMode.Open);
                BinaryReader br = new BinaryReader(fs);
                int i, j;
                for (i = 0; i < 10; i++)
                {
                    for (j = 0; j < 10; j++)
                    {
                        board[i, j].Text = br.ReadString();
                        board[i, j].ForeColor = Color.Black;
                        // 初始化陣列
                        initial[i, j] = int.Parse(board[i, j].Text);
                    }
                }
                br.Close();
                fs.Close();
            }
        }
        public int solve(int[,] grid)
        {
            int m = grid.GetLength(0); // 獲取長寬
            int n = grid.GetLength(1);
            int[,] dist = new int[m, n]; // 距離陣列
            bool[,] visited = new bool[m, n]; // 標記走訪
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    dist[i, j] = int.MaxValue;
                }
            }
            dist[0, 0] = grid[0, 0];

            PriorityQueue<(int, int), int> pq = new PriorityQueue<(int, int), int>();
            pq.Enqueue((0, 0), grid[0, 0]); // 起點加入 Priority Queue
            int[] dir = { 0, 1, 0, -1, 0 }; // 四方向
            (int, int)[,] prev = new (int, int)[m, n]; // 記錄走過的地方
            prev[0, 0] = (-1, -1);

            while (pq.Count > 0)
            {
                var (x, y) = pq.Dequeue(); // 取出距離最短的點
                if (visited[x, y]) continue; // 走過的點不不能走
                visited[x, y] = true; // 標記為走訪過
                for (int i = 0; i < 4; ++i) // 四方向拓展
                {
                    int nx = x + dir[i];
                    int ny = y + dir[i + 1];
                    if (nx >= 0 && ny >= 0 && nx < m && ny < n && !visited[nx, ny])
                    {
                        int newDist = dist[x, y] + grid[nx, ny];
                        if (newDist < dist[nx, ny])
                        {
                            dist[nx, ny] = newDist;
                            prev[nx, ny] = (x, y);
                            pq.Enqueue((nx, ny), newDist);
                        }
                    }
                }
            }
            for (int x = m - 1, y = n - 1; x != -1 && y != -1;)
            {
                board[x, y].ForeColor = Color.Red;
                (x, y) = prev[x, y];
            }
            return dist[m - 1, n - 1];
        }
    }
}
