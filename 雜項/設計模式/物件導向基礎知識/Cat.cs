using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 物件導向基礎知識
{
    internal class Cat:Animal
    {
        public Cat():base() { } // 建構子
        public Cat(string name) : base(name) { } // 方法重載建構子
        protected override string getShoutSound() { return " 喵"; } // 多型
    }
}
