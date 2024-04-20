using System;
using System.Collections.Generic;
using System.Drawing.Text;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 物件導向基礎知識
{
    abstract class Animal // 抽象類別, 因為實例化一個 Animal 物件沒有任何意義
    {
        // 設計模式, 範本方法
        protected string name = string.Empty; // 會繼承下去的變數
        public Animal(string name) // 方法重載
        {
            this.name = name;
        }
        public Animal() // 無參數建構子
        {
            this.name = "無名";
        }
        protected int shoutNum = 3; // 會繼承下去的變數
        public int ShoutNum{   get { return shoutNum; } set {  shoutNum = value; }} // 屬性 
        protected abstract string getShoutSound();
        public string Shout()
        {
            string result = string.Empty;
            for (int i = 0; i < shoutNum; ++i)
                result += getShoutSound();
            return "我的名字叫 " + name + " " + result;
        }
    }
}
