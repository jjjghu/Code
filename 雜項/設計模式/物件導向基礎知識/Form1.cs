namespace 物件導向基礎知識
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            Animal[] arrayAnimal = new Animal[5];
            arrayAnimal[0] = new Cat("和真"); arrayAnimal[0].ShoutNum = 5;
            arrayAnimal[1] = new Dog("墩墩"); arrayAnimal[1].ShoutNum = 3;
            arrayAnimal[2] = new Sheep("泡泡"); arrayAnimal[2].ShoutNum = 2;
            arrayAnimal[3] = new Sheep("落落"); arrayAnimal[3].ShoutNum = 4;
            arrayAnimal[4] = new Cat("甜甜"); arrayAnimal[4].ShoutNum = 1;
            foreach (Animal item in arrayAnimal)
            {
                MessageBox.Show(item.Shout());
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            MachineCat machineCat = new MachineCat("哆啦A夢");
            MessageBox.Show(machineCat.ChangeThing("任意門"));
            StoneMonkey stoneMonkey = new StoneMonkey("孫悟空");
            MessageBox.Show(stoneMonkey.ChangeThing("一隻牛"));
        }
    }
}
