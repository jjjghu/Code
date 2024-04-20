using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 物件導向基礎知識
{
    class Dog : Animal
    {
        public Dog() : base() // 建構子
        { }
        public Dog(string name) : base(name) // 方法重載建構子
        { }
        protected override string getShoutSound() // 多型
        {
            return " 汪!";
        }
    }
}
