using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hw_8
{
    public class FormFactory
    {
        public static IMyForm createForm(string newFormType)
        {
            IMyForm newForm = null!;
            switch (newFormType)
            {
                case "Picture": newForm = new AddPicture(); break;
                case "Rectangle": newForm = new AddRectangle(); break;
                case "Triangle": newForm = new AddTriangle(); break;
                case "Circle": newForm = new AddCircle(); break;
                default: MessageBox.Show("Invalid form type"); break;
            }
            return newForm;
        }
    }
}
