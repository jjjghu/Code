import java.util.Scanner;
import java.text.DecimalFormat;
public class Q3{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		DecimalFormat f1 = new DecimalFormat("0.00");

		System.out.println("Please enter a number: ");
		double d = Double.parseDouble(scanner.next());
		double d2 = ((d - 32) * 5) / 9;
		System.out.println("Fahrenheit " + f1.format(d) + " ---> Celsius " + f1.format(d2));

	}
}