using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hw_15
{
    public interface IHashStrategy
    {
        void Execute(Form1 form, string str);
    }
    public class AddHashStrategy : IHashStrategy
    {
        public void Execute(Form1 form, string str)
        {
            form.AddHash(str);
        }
    }

    public class DeleteHashStrategy : IHashStrategy
    {
        public void Execute(Form1 form, string str)
        {
            form.DeleteHash(str);
        }
    }

    public class SearchHashStrategy : IHashStrategy
    {
        public void Execute(Form1 form, string str)
        {
            form.SearchHash(str);
        }
    }
}
