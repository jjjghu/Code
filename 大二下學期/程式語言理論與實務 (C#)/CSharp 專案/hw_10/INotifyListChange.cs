using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hw_10
{
    public interface INotifyListChange
    {
        public void UpdateList(string displayText);
    }
    public class ListChangeNotifier
    {
        private INotifyListChange _observer;

        public ListChangeNotifier(INotifyListChange observer)
        {
            _observer = observer;
        }

        public void NotifyChange(ListNode head)
        {
            ListNode curr = head.next;
            string displayText = "head -> ";
            while (curr != null)
            {
                displayText += curr.val + " -> ";
                curr = curr.next;
            }
            displayText += "null";

            _observer.UpdateList(displayText);
        }
    }

}
