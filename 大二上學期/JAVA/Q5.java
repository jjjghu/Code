import java.util.Scanner;
public class Q5
{
	static int gcd(int a, int b)
	{
		while(a != 0 && b != 0)
		{
			if(a > b)
				a %= b;
			else
				b %= a;
			// System.out.println("a = " + a);
			// System.out.println("b = " + b);
			// System.out.println(" ");
		}
		return (a > b) ? a:b;
	}
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		// System.out.println("Please enter the first number: ");
		int a = scanner.nextInt();
		// System.out.println("Please enter the second number: ");
		int b = scanner.nextInt();
		int c = gcd(a,b);
		//System.out.println(c);
		System.out.println( (a/c)*(b/c) + " " + (a / c) * b);

	}
}