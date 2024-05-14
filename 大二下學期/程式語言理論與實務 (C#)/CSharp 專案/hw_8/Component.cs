using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms.Design;

namespace hw_8
{
    public abstract class Component
    {
        protected string name = string.Empty;
        public string getName()
        {
            return name;
        }
        public abstract double area();
        public abstract string show();
    }

    internal class Picture : Component
    {
        private List<Component> coms = new List<Component>();
        public Picture(string name)
        {
            this.name = name;
        }
        public override double area()
        {
            double total = 0.0;
            for (int i = 0; i < coms.Count; i++) { total = total + coms[i].area(); }
            return total;
        }
        public override string show()
        {
            string s = "{Picture " + name + ":";
            for (int i = 0; i < coms.Count; i++)
            {
                s = s + " " + coms[i].show();
            }
            return s + "}";
        }
        public void addComponent(Component c)
        {
            coms.Add(c);
        }
    }

    internal abstract class Shape : Component
    {}
    internal class Triangle : Shape
    {
        private double tbase;
        private double height;
        public Triangle(string name, double tbase, double height)
        {
            this.name = name;
            this.tbase = tbase;
            this.height = height;
        }
        public override string show()
        {
            return "Triangle " + name + "(" + tbase + "," + height + ")";
        }
        public override double area()
        {
            return 0.5 * tbase * height;
        }
    }
    internal class Rectangle : Shape
    {
        private double length;
        private double width;
        public Rectangle(string name, double length, double width)
        {
            this.name = name;
            this.length = length;
            this.width = width;
        }
        public override string show()
        {
            return "Rectangle " + name + "(" + length + "," + width + ")";
        }
        public override double area()
        {
            return length * width;
        }
    }
    internal class Circle : Shape
    {
        private double radius;
        public Circle(string name, double radius)
        {
            this.name = name;
            this.radius = radius;
        }
        public override string show()
        {
            return "Circle " + name + "(" + radius + ")";
        }
        public override double area()
        {
            return radius * radius * double.Pi;
        }
    }
}
