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
    public partial class 註冊帳號和密碼 : Form
    {
        public 註冊帳號和密碼()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            if (textBox2.Text != String.Empty)
            {
                label3.Visible = true;
                textBox3.Visible = true;
            }
            else
            {
                label3.Visible = false;
                textBox3.Visible = false;
                textBox3.Text = String.Empty;
            }
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            if (textBox2.Text == textBox3.Text)
            {
                button1.Enabled = true;
            }
            else button1.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            程式語言理論與實務 form2 = new 程式語言理論與實務();
            form2.preForm = this;
            form2.Show();
            this.Hide();
        }
    }
}
