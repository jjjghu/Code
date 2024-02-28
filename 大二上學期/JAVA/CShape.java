import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Collections;
class S1154041
{
	public static void main(String args[])
	{
		CCircle cir1 = new CCircle(2.0);
		CCircle cir2 = new CCircle(3.0);
		CSquare squ1 = new CSquare(4.0);
		CSquare squ2 = new CSquare(5.0);
		CTriangle tri1 = new CTriangle(3.0, 3.0);
		CTriangle tri2 = new CTriangle(5.0, 4.0);
		DecimalFormat f1 = new DecimalFormat("0.0");
		DecimalFormat f2 = new DecimalFormat("0.00");
		CShape.areas.add(cir1.area());
		CShape.areas.add(cir2.area());
		CShape.areas.add(squ1.area());
		CShape.areas.add(squ2.area());
		CShape.areas.add(tri1.area());
		CShape.areas.add(tri2.area());
		System.out.println("面積1 = " + f2.format(cir1.area()));
		System.out.println("面積2 = " + f2.format(cir2.area()));
		System.out.println("面積3 = " + f1.format(squ1.area()));
		System.out.println("面積4 = " + f1.format(squ2.area()));
		System.out.println("面積5 = " + f1.format(tri1.area()));
		System.out.println("面積6 = " + f1.format(tri2.area()));
		double mx = CShape.largest();
		System.out.println("面積最大 = " + mx);
	}
}
class CShape
{
	public static final double pi = 3.14;
	public static ArrayList<Double> areas = new ArrayList<>();
	public double area()
	{
		return 0.0;
	}
	public static double largest()
	{
		return Collections.max(areas);
	}
}
class CCircle extends CShape
{
	double radius;
	CCircle(double radius)
	{
		this.radius = radius;
	}
	@Override
	public double area()
	{
		return this.radius * this.radius * CShape.pi; 
	}
}
class CSquare extends CShape
{
	double length;
	CSquare(double length)
	{
		this.length = length;
	}
	@Override
	public double area()
	{
		return this.length * this.length; 
	}
}
class CTriangle extends CShape
{
	double width, height;
	CTriangle(double width, double height)
	{
		this.width = width;
		this.height = height;
	}
	@Override
	public double area()
	{
		return this.width * this.height / 2; 
	}
}
class Nothing
{
	
}