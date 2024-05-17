using System.ComponentModel.Design.Serialization;

namespace hw_11
{
    public partial class Form1 : Form
    {
        public class TreeNode
        {
            public int val;
            public TreeNode left;
            public TreeNode right;
            public TreeNode(int val = 0, TreeNode left = null!, TreeNode right = null!)
            {
                this.val = val;
                this.left = left;
                this.right = right;
            }
        }
        TreeNode root;
        public Form1()
        {
            InitializeComponent();
            root = null!;
        }

        private void AddValue(TreeNode newNode)
        {
            if (root == null)
            {
                root = newNode;
                return;
            }
            TreeNode prev = null!;
            TreeNode curr = root;
            while (curr != null)
            {
                if (curr.val == newNode.val)
                {
                    throw new Exception("資料" + newNode.val + "已存在, 新增失敗");
                }
                prev = curr;
                if (newNode.val < curr.val)
                    curr = curr.left;
                else
                    curr = curr.right;
            }
            if (newNode.val < prev.val)
                prev.left = newNode;
            else
                prev.right = newNode;
        }
        private TreeNode SearchValue(int n)
        {
            TreeNode prev = root;
            TreeNode curr = root.left;
            while (curr != null)
            {
                if (curr.val == n)
                {
                    break;
                }
                prev = curr;
                if (n < curr.val)
                    curr = curr.left;
                else
                    curr = curr.right;
            }
            if (curr == null)
            {
                throw new Exception("資料" + n + "不存在");
            }
            else // 找到資料
            {
                return curr;
            }
        }
        private (TreeNode node, TreeNode parent) FindNodeAndParent(int value)
        {
            TreeNode parent = null!;
            TreeNode node = root;
            while (node != null && node.val != value)
            {
                parent = node;
                if (value < node.val)
                    node = node.left;
                else
                    node = node.right;
            }
            return (node, parent)!;
        }
        private void DeleteValue(int n)
        {
            var (target, parent) = FindNodeAndParent(n);
            if (target == null)
            {
                throw new Exception("資料" + n + "不存在");
            }

            // 0 child
            if (target.left == null && target.right == null)
            {
                if (parent == null)
                {
                    root = null; // The node to delete is the root
                }
                else if (parent.left == target)
                {
                    parent.left = null;
                }
                else
                {
                    parent.right = null;
                }
            }
            // 1 child
            else if (target.left == null || target.right == null)
            {
                TreeNode? child = target.left ?? target.right;
                if (parent == null)
                {
                    root = child; // The node to delete is the root
                }
                else if (parent.left == target)
                {
                    parent.left = child;
                }
                else
                {
                    parent.right = child;
                }
            }
            // 2 child
            else
            {
                TreeNode ptr3 = target.left;
                TreeNode ptr3Parent = target;
                while (ptr3.right != null)
                {
                    ptr3Parent = ptr3;
                    ptr3 = ptr3.right;
                }

                target.val = ptr3.val;

                if (ptr3Parent.left == ptr3)
                {
                    ptr3Parent.left = ptr3.left;
                }
                else
                {
                    ptr3Parent.right = ptr3.left;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox1.Text == "")
                {
                    throw new Exception("請輸入數字");
                }
                int n = int.Parse(textBox1.Text);
                AddValue(new TreeNode(n));
                textBox2.Text = string.Empty;
                inorder(root);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "新增失敗", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                if (textBox1.Text == "")
                {
                    throw new Exception("請輸入數字");
                }
                int n = int.Parse(textBox1.Text);
                DeleteValue(n);
                textBox2.Text = string.Empty;
                inorder(root);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "刪除失敗", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void preorder(TreeNode node)
        {
            if (node == null)
                return;
            textBox2.Text += node.val + " ";
            preorder(node.left);
            preorder(node.right);
        }
        private void inorder(TreeNode node)
        {
            if (node == null)
                return;
            inorder(node.left);
            textBox2.Text += node.val + " ";
            inorder(node.right);
        }
        private void postorder(TreeNode node)
        {
            if (node == null)
                return;
            postorder(node.left);
            postorder(node.right);
            textBox2.Text += node.val + " ";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            textBox2.Text = string.Empty;
            preorder(root);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            textBox2.Text = string.Empty;
            inorder(root);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            textBox2.Text = string.Empty;
            postorder(root);
        }
    }
}
