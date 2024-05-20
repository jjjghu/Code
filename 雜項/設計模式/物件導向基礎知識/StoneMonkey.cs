using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 物件導向基礎知識
{
    internal class StoneMonkey : Animal, IChange // 繼承 Animal, IChange 介面
    {
        public StoneMonkey() : base() { }
        public StoneMonkey(string name) :base(name) { }
        protected override string getShoutSound() { return " 吱"; }
        public string ChangeThing(string thing) // 介面實作
        {
            return base.Shout() + "我會七十二變, 可以變成" + thing;
        }

    }
}
