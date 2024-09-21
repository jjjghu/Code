using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hw_8
{
    public interface IMyForm
    {
        public Component GetComponent(out string newStuff, out string targetContainer);
    }
}
