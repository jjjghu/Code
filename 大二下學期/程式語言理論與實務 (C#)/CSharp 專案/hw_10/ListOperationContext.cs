using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hw_10
{
    public interface IListOperationStrategy
    {
        public void Execute(ListNode head, int value);
    }
    public class ListOperationContext
    {
        private IListOperationStrategy _strategy;

        public ListOperationContext(IListOperationStrategy strategy)
        {
            _strategy = strategy;
        }

        public void SetStrategy(IListOperationStrategy strategy)
        {
            _strategy = strategy;
        }

        public void ExecuteStrategy(ListNode head, int value)
        {
            _strategy.Execute(head, value);
        }
    }

    public class AddNodeStrategy : IListOperationStrategy
    {
        public void Execute(ListNode head, int value)
        {
            ListNode curr = head.next;
            ListNode prev = head;

            while (curr != null)
            {
                if (curr.val == value)
                {
                    throw new Exception("資料" + value + "重複");
                }
                else if (curr.val > value)
                {
                    ListNode newNode = new ListNode(value);
                    prev.next = newNode;
                    newNode.next = curr;
                    return;
                }
                else
                {
                    prev = curr;
                    curr = curr.next;
                }
            }
            prev.next = new ListNode(value);
        }
        public class DeleteNodeStrategy : IListOperationStrategy
        {
            public void Execute(ListNode head, int value)
            {
                ListNode curr = head.next;
                ListNode prev = head;

                while (curr != null)
                {
                    if (curr.val == value)
                    {
                        prev.next = curr.next;
                        return;
                    }
                    else
                    {
                        prev = curr;
                        curr = curr.next;
                    }
                }
                throw new Exception("串列中沒有 " + value);
            }
        }

    }


}
