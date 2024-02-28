import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Collections;
class S1154041
{
	public static void main(String args[])
	{
		CShape shp[] = new CShape[6];
		shp[0]=new CCircle(2.0);
		shp[1]=new CCircle(3.0);
		shp[2]=new CSquare(4.0);
		shp[3]=new CSquare(5.0);
		shp[4]=new CTriangle(3.0,3.0);
		shp[5]=new CTriangle(5.0,4.0);
		
		DecimalFormat f1 = new DecimalFormat("0.0");
		DecimalFormat f2 = new DecimalFormat("0.00");

		for(CShape shape: shp)
		{
			CShape.areas.add(shape.area());
		}
		System.out.println("面積1 = " + f2.format(CShape.areas.get(0)));
		System.out.println("面積2 = " + f2.format(CShape.areas.get(1)));
		System.out.println("面積3 = " + f1.format(CShape.areas.get(2)));
		System.out.println("面積4 = " + f1.format(CShape.areas.get(3)));
		System.out.println("面積5 = " + f1.format(CShape.areas.get(4)));
		System.out.println("面積6 = " + f1.format(CShape.areas.get(5)));
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