using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Button;

namespace hw1
{
    public partial class 點餐系統 : Form
    {
        public 程式語言理論與實務 preForm;
        public 點餐系統()
        {
            InitializeComponent();
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            Cal();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.preForm.preForm.Close();
            this.preForm.Close();
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.preForm.Show();
            this.Close();
        }

        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox5.Checked == true) { groupBox2.Enabled = true; }
            else
            {
                groupBox2.Enabled = false;
                radioButton1.Checked = false;
                radioButton2.Checked = false; 
            }
        }

        private void checkBox6_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox6.Checked == true) { groupBox3.Enabled = true; }
            else
            {
                groupBox3.Enabled = false;
                radioButton3.Checked = false;
                radioButton4.Checked = false;
                radioButton5.Checked = false;
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            Cal();
        }
        private void Cal()
        {
            int cost = 0;
            if (checkBox1.Checked) { cost += 69; }
            if (checkBox2.Checked) { cost += 49; }
            if (checkBox3.Checked) { cost += 59; }
            if (checkBox4.Checked) { cost += 79; }
            if (radioButton1.Checked) { cost += 35; }
            if (radioButton2.Checked) { cost += 25; }
            if (radioButton3.Checked) { cost += 35; }
            if (radioButton4.Checked) { cost += 25; }
            if (radioButton5.Checked) { cost += 45; }
            textBox1.Text = "" + cost;
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            Cal();
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            Cal();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            Cal();
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            Cal();
        }
        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            Cal();
        }

        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            Cal();
        }
        private void radioButton5_CheckedChanged(object sender, EventArgs e)
        {
            Cal();
        }


    }
}
