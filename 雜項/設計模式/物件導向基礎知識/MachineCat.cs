using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 物件導向基礎知識
{
    internal class MachineCat:Cat, IChange // 繼承 Cat 類別, 實作 IChange 介面
    {
        public MachineCat(): base() // 建構子
        { }
        public MachineCat(string name) :base(name) // 方法重載建構子
        { }
        public string ChangeThing(string thing)
        {
            return base.Shout() + " 我有百寶袋, 可以變出 " + thing;
        }
    }
}
