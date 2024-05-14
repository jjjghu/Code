using System.Runtime.CompilerServices;
using System.Text;

namespace hw_8
{
    public partial class Form1 : Form
    {
        Picture g = new Picture("Graph");
        List<Component> allPicture = new List<Component>();
        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            allPicture.Add(g);
            UpdateTextBox();
        }
        // 加入的容器
        string newStuff = string.Empty, targetContainer = string.Empty;
        private void button1_Click(object sender, EventArgs e){ solve("Picture"); }
        private void button2_Click(object sender, EventArgs e) { solve("Rectangle"); }
        private void button3_Click(object sender, EventArgs e) { solve("Triangle"); }
        private void button4_Click(object sender, EventArgs e) { solve("Circle"); }
        internal void solve(string newFormType)
        {
            // 要加入的 Picture, Rectangle, Triangle, Circle
            Component component= null!;
            IMyForm form = FormFactory.createForm(newFormType);
            Form myForm = (Form)form;
            if (myForm.ShowDialog() == DialogResult.OK)
            {
                component = form.GetComponent(out newStuff, out targetContainer);
                bool findTarget = false;
                foreach (Picture pic in allPicture)
                {
                    if (pic.getName() == targetContainer)
                    {
                        pic.addComponent(component);
                        findTarget = true;
                        break;
                    }
                }
                if (!findTarget)
                {
                    MessageBox.Show("Can't find target container");
                    return;
                }
                else if (newFormType == "Picture")
                { 
                    allPicture.Add(component);
                } 
            }
            // 更新顯示
            UpdateTextBox();
        }
        private void UpdateTextBox()
        {
            string s = "";
            s += g.show();
            textBox1.Text = s;
        }
        private void button5_Click(object sender, EventArgs e)
        {
            textBox2.Text = Convert.ToString(g.area());
        }
    }
}
