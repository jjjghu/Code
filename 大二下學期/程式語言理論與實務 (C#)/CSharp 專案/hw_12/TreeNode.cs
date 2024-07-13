using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hw_12
{
    public class TreeNode
    {
        public char data;
        public int freq;
        public string code;
        public bool leaf;
        public bool hasfather;
        public TreeNode left;
        public TreeNode right;
        public TreeNode(char ch)
        {
            data = ch;
            freq = 1;
            code = string.Empty;
            leaf = true;
            hasfather = false;
            left = null!;
            right = null!;
        }
    }
}
