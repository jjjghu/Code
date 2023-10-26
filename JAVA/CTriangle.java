class CTriangle
{
	private int base, height;
	private String color;
	public CTriangle()
	{
		base = 10;
		height = 5;
		color = "blue";
	}
	public CTriangle(int b, int h, String c)
	{
		base = b;
		height = h;
		color = c;
	}
	public void setB(int base)
	{
		this.base = base;
	}
	public void setH(int height)
	{
		this.height = height;
	}
	public void setColor(String color)
	{
		this.color = color;
	}
	public void show()
	{
		System.out.println("Color=" + color);
		System.out.println("base=" + base + ", height=" + height);
		System.out.println();
	}
}
public class S1154041
{
	public static void main(String args[])
	{
		CTriangle a = new CTriangle();
		CTriangle b = new CTriangle(30,10,"Red");

		a.show();
		b.show();
		System.out.print("Process completed.");
	}
}