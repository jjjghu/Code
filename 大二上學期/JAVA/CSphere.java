import java.util.Scanner;
import java.text.DecimalFormat;
class CSphere
{
	private int x;
	private int y;
	private int z;
	private int radius;
	final double pi = 3.14;

	public void setLocation(int x, int y, int z)
	{
		this.x = x;
		this.y = y;
		this.z = z;
	}
	public void setRadius(int radius)
	{
		this.radius = radius;
	}
	public double surfaceArea()
	{
		return 4*pi*radius*radius;
	}
	public double volume()
	{
		return (4.0/3)*pi*radius*radius*radius;
	}
	public void showCenter()
	{
		System.out.println("x=" + x + " y=" + y + " z=" + z);
	}
}
public class S1154041
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		DecimalFormat f = new DecimalFormat("0.00");
		int x = scanner.nextInt();
		int y = scanner.nextInt();
		int z = scanner.nextInt();
		int radius = scanner.nextInt();
		CSphere ball = new CSphere();
		ball.setLocation(x,y,z);
		ball.setRadius(radius);
		ball.showCenter();
		System.out.println(f.format(ball.surfaceArea()));
		System.out.println(ball.volume());
	}
}