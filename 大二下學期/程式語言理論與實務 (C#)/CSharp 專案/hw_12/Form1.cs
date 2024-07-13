using System.IO.Compression;
using System.Reflection.Metadata.Ecma335;

namespace hw_12
{
    public partial class Form1 : Form
    {
        List<TreeNode> tree;
        public Form1()
        {
            InitializeComponent();
            tree = new List<TreeNode>();
        }
        void Encode(TreeNode node)
        {
            if (node != null)
            {
                if (node.left != null)
                {
                    node.left.code = node.code + "0";
                    Encode(node.left);
                }
                if (node.right != null)
                {
                    node.right.code = node.code + "1";
                    Encode(node.right);
                }
            }
        }
        void findMin(out TreeNode min1, out TreeNode min2)
        {
            min1 = null!;
            min2 = null!;
            for (int i = 0; i < tree.Count; ++i)
            {
                if (tree[i].hasfather == false)
                {
                    if (min1 == null || tree[i].freq < min1.freq)
                    {
                        min2 = min1!;
                        min1 = tree[i];
                    }
                    else if (min2 == null || tree[i].freq < min2.freq)
                    {
                        min2 = tree[i];
                    }
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // 清空 Tree
            tree.Clear();
            string s = textBox1.Text;
            // 建立 Huffman Tree
            for (int i = 0; i < s.Length; ++i)
            {
                bool found = false;
                for (int j = 0; j < tree.Count; ++j)
                {
                    if (tree[j].data == s[i])
                    {
                        ++tree[j].freq;
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    TreeNode node = new TreeNode(s[i]);
                    tree.Add(node);
                }
            }
            // 建立 Huffman Tree
            BuildHuffManTree();
            textBox2.Text = GetCodeDetail();
            textBox3.Text = GetHuffManCode();
            textBox4.Text = winrar();
        }
        private void BuildHuffManTree()
        {
            TreeNode min1, min2;
            while (true)
            {
                findMin(out min1, out min2);
                if (min1 == null || min2 == null)
                {
                    break;
                }
                min1.hasfather = true;
                min2.hasfather = true;
                // 建立新的 node, 連結兩個最小的節點
                TreeNode node = new TreeNode(' ');
                node.freq = min1.freq + min2.freq;
                node.left = min1;
                node.right = min2;
                node.leaf = false;
                tree.Add(node);
            }
            // 從根結點開始建立編碼
            Encode(tree[tree.Count - 1]);
        }
        private string GetCodeDetail()
        {
            string s = string.Empty;
            // 字元, 次數, 編碼
            foreach (TreeNode node in tree)
            {
                if (node.leaf)
                    s += node.data + "\t" + node.freq + "\t" + node.code + "\r\n";
            }
            return s;
        }
        private string GetHuffManCode()
        {
            string s = string.Empty;
            // 顯示轉換後的編碼
            foreach (char c in textBox1.Text)
            {
                foreach (TreeNode node in tree)
                {
                    if (node.data == c)
                    {
                        s += node.code + " ";
                        break;
                    }
                }
            }
            return s;
        }
        private string winrar()
        {
            double beforePressure = textBox1.Text.Length * 8;
            double afterPressure = 0;
            double res;
            // 葉節點的 freq* code.length
            foreach(TreeNode node in tree)
            {
                if(node.leaf)
                    afterPressure += node.freq * node.code.Length;
            }
            res = (beforePressure - afterPressure) / beforePressure;
            res = Math.Round(res, 2);
            string s = beforePressure + "bits 壓縮成" + afterPressure + "bits，壓縮率為" + (beforePressure - afterPressure) + "/" + beforePressure + " = " + res*100 + "%";
            return s;
        }
    }
}
