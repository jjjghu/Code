import java.util.Scanner;
import java.text.DecimalFormat;
public class Q4{
	public static void main(String args[])
	{
		int[] list = new int[4];
		//System.out.println("Enter the string: ");
		Scanner scanner = new Scanner(System.in);
		String s = scanner.nextLine();
		//System.out.println("This is what you enter: " + s);
		for(int i = 0; i < s.length(); i++)
		{
			switch(s.charAt(i))
			{
				case '2': list[0]++;break;
				case '4': list[1]++;break;
				case '6': list[2]++;break;
				case '8': list[3]++;break;
			}
		}
		System.out.println("2 " + list[0]);
		System.out.println("4 " + list[1]);
		System.out.println("6 " + list[2]);
		System.out.println("8 " + list[3]);
	}
}