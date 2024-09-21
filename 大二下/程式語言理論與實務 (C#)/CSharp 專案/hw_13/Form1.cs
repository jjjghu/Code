using System.Drawing.Drawing2D;

namespace hw_13
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        Heap heap = new Heap(); // maxHeap

        private void Form1_Load(object sender, EventArgs e)
        {
        }
        void Form1_Paint(object sender, PaintEventArgs e)
        {
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                int newValue = int.Parse(textBox1.Text);
                heap.Insert(newValue);
                textBox1.Text = "";
                refresh();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void button2_Click(object sender, EventArgs e)
        {
            try
            {

                int rootValue = heap.Extract();
                textBox2.Text = rootValue.ToString();
                refresh();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void refresh()
        {
            List<int> heapList = heap.GetHeapList();
            textBox3.Text = heapList.Count > 0 ? heapList[0].ToString() : string.Empty;
            textBox4.Text = heapList.Count > 1 ? heapList[1].ToString() : string.Empty;
            textBox5.Text = heapList.Count > 2 ? heapList[2].ToString() : string.Empty;
            textBox6.Text = heapList.Count > 3 ? heapList[3].ToString() : string.Empty;
            textBox7.Text = heapList.Count > 4 ? heapList[4].ToString() : string.Empty;
            textBox8.Text = heapList.Count > 5 ? heapList[5].ToString() : string.Empty;
            textBox9.Text = heapList.Count > 6 ? heapList[6].ToString() : string.Empty;
            textBox10.Text = heapList.Count > 7 ? heapList[7].ToString() : string.Empty;
            textBox11.Text = heapList.Count > 8 ? heapList[8].ToString() : string.Empty;
            textBox12.Text = heapList.Count > 9 ? heapList[9].ToString() : string.Empty;
            textBox13.Text = heapList.Count > 10 ? heapList[10].ToString() : string.Empty;
            textBox14.Text = heapList.Count > 11 ? heapList[11].ToString() : string.Empty;
            textBox15.Text = heapList.Count > 12 ? heapList[12].ToString() : string.Empty;
            textBox16.Text = heapList.Count > 13 ? heapList[13].ToString() : string.Empty;
            textBox17.Text = heapList.Count > 14 ? heapList[14].ToString() : string.Empty;
        }
    }
}
