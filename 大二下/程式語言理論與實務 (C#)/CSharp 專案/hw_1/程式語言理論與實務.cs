using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace hw1
{
    public partial class 程式語言理論與實務 : Form
    {
        public 註冊帳號和密碼 preForm;
        public 程式語言理論與實務()
        {
            InitializeComponent();
        }
        private void 程式語言理論與實務_Load(object sender, EventArgs e)
        {
            textBox1.Text = "1. 上課認真聽\r\n2. 作業認真寫\r\n3. 晚上認真聽\r\n4. 一天一程式, Fail遠離我\r\n";
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked) { button1.Enabled = true; }
            else { button1.Enabled = false; }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            點餐系統 form3 = new 點餐系統();
            form3.preForm = this;
            form3.Show();
            this.Hide();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            preForm.Show();
            this.Close();
        }

    }
}
