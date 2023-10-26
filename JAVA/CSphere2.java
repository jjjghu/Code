import java.util.Scanner;
import java.text.DecimalFormat;
class CSphere
{
	private int x;
	private int y;
	private int z;
	private double radius;
	final double pi = 3.14;

	public CSphere(int a, int b, int c, double r)
	{
		x = a;
		y = b;
		z = c;
		radius = r;
	}
	public double distance(CSphere a, CSphere b)
	{
		int xx = a.x - b.x;
		int yy = a.y - b.y;
		int zz = a.z - b.z;
		return Math.sqrt(xx*xx + yy*yy + zz*zz);
	}
	public void isIntersect(CSphere a, CSphere b)
	{
		if(distance(a,b) <= a.radius + b.radius)
			System.out.println("2 球有碰觸");
		else
			System.out.println("2 球無碰觸");
	}
	public void setLocation(int x, int y, int z)
	{
		this.x = x;
		this.y = y;
		this.z = z;
	}
	public void setRadius(double radius)
	{
		this.radius = radius;
	}

	public void show()
	{
		DecimalFormat f = new DecimalFormat("0");
		System.out.println("x=" + x + " y=" + y + " z=" + z + ", radius=" + f.format(radius));
	}
}
public class S1154041
{
	public static void main(String args[])
	{
		Scanner s = new Scanner(System.in);
		CSphere ballA = new CSphere(s.nextInt(), s.nextInt(), s.nextInt(), s.nextDouble());
		CSphere ballB = new CSphere(s.nextInt(), s.nextInt(), s.nextInt(), s.nextDouble());
		ballA.show();
		ballB.show();
		System.out.println("2 球圓心的距離 = " + CSphere.distance(ballA, ballB));
		CSphere.isIntersect(ballA, ballB);
	}
}
/*

javac -encoding UTF-8 S1154041.java
java -Dfile.encoding=UTF-8 S1154041
*/