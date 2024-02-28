import java.util.Scanner;
class Point
{
	private double x, y;
	public Point(double x, double y)
	{
		this.x = x;
		this.y = y;
	}
	public double distance()
	{
		return Math.sqrt(x*x + y*y);
	}
	public double distance(Point a)
	{
		double xx = this.x - a.x;
		double yy = this.y - a.y;
		return Math.sqrt(xx*xx + yy*yy);
	}
}
public class S1154041
{
	public static void main(String args[])
	{
		Scanner s = new Scanner(System.in);
		while(true)
		{
			System.out.print("請輸入三個點座標: ");
			if(!s.hasNextDouble()) break;
			Point a = new Point(s.nextDouble(), s.nextDouble());
			Point b = new Point(s.nextDouble(), s.nextDouble());
			Point c = new Point(s.nextDouble(), s.nextDouble());
			double ab = a.distance(b);
			double bc = b.distance(c);
			double ca = a.distance(c);
			System.out.print("與原點距離: ");
			System.out.println(a.distance() + " " + b.distance() + " " + c.distance());
			System.out.print("任兩點距離: ");
			System.out.println(ab + " " + bc + " " + ca);
			System.out.print("距離最遠的兩個點: ");

			if(ab > bc && ab > ca)
				System.out.println(" A B");
			else if(bc > ab && bc > ca)
				System.out.println(" B C");
			else if(ca > ab && ca > bc)
				System.out.println(" A C");
			System.out.print("\n");
		}
	}
}
/*
javac -encoding UTF-8 S1154041.java
java -Dfile.encoding=UTF-8 S1154041
*/