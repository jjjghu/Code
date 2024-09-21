using System.CodeDom;
using static hw_10.AddNodeStrategy;

namespace hw_10
{
    public partial class Form1 : Form, INotifyListChange
    {
        private ListNode head;
        private ListOperationContext _listOperationContext;
        private ListChangeNotifier _listChangeNotifier;
        public Form1()
        {
            InitializeComponent();
            head = new ListNode();
            _listOperationContext = new ListOperationContext(new AddNodeStrategy());
            _listChangeNotifier = new ListChangeNotifier(this);
            textBox1.Text = "head -> null";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                if (string.IsNullOrEmpty(textBox2.Text))
                {
                    throw new Exception("Please enter data");
                }

                int n = Convert.ToInt32(textBox2.Text);
                _listOperationContext.SetStrategy(new AddNodeStrategy());
                _listOperationContext.ExecuteStrategy(head, n);
                _listChangeNotifier.NotifyChange(head);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                if (string.IsNullOrEmpty(textBox2.Text))
                {
                    throw new Exception("Please enter data");
                }
                int n = Convert.ToInt32(textBox2.Text);
                _listOperationContext.SetStrategy(new DeleteNodeStrategy());
                _listOperationContext.ExecuteStrategy(head, n);
                _listChangeNotifier.NotifyChange(head);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        public void UpdateList(string displayText)
        {
            textBox1.Text = displayText;
        }
    }
}
