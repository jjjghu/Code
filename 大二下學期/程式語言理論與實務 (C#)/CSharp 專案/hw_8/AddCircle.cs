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
    public partial class AddCircle : Form, IMyForm
    {
        public AddCircle()
        {
            InitializeComponent();
        }
        public Component GetComponent(out string newStuff, out string targetContainer)
        {
            double radius = Convert.ToDouble(textBox3.Text);
            newStuff = textBox1.Text;
            targetContainer = textBox2.Text;
            return new Circle(newStuff, radius);
        }
    }
}
