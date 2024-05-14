using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Permissions;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace hw_8
{
    public partial class AddPicture : Form, IMyForm
    {
        public AddPicture()
        {
            InitializeComponent();
        }
        public Component GetComponent(out string newStuff, out string targetContainer)
        {
            newStuff = textBox1.Text;
            targetContainer = textBox2.Text;
            return new Picture(newStuff);
        }
    }
}
