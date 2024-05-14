using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace hw_8
{
    public partial class AddTriangle : Form, IMyForm
    {
        public AddTriangle()
        {
            InitializeComponent();
        }
        public Component GetComponent(out string newStuff, out string targetContainer)
        {
            int tbase, height;
            newStuff = textBox1.Text;
            targetContainer = textBox2.Text;
            tbase = Convert.ToInt32(textBox3.Text);
            height = Convert.ToInt32(textBox4.Text);
            return new Triangle(newStuff, tbase, height);
        }
    }
}
