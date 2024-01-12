import java.util.Scanner;
import java.text.*;
public class Q1{
	public static void main(String args[]){
		Scanner scanner = new Scanner(System.in);
		DecimalFormat f1 = new DecimalFormat("0.00");
		double w,h;
		h = Double.parseDouble(scanner.next());
		w = Double.parseDouble(scanner.next());
		
		System.out.print("Height = ");
		System.out.println(f1.format(h));

		System.out.print("Width = ");
		System.out.println(f1.format(w));
		
		System.out.print("Perimeter = ");
		System.out.println(f1.format(2 * (h + w)));
		
		System.out.print("Area = ");
		System.out.println(f1.format(h * w));
	}
}