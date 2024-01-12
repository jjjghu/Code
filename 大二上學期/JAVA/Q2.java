import java.util.Scanner;
public class Q2
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		String s = scanner.nextLine();
		int Chinese = scanner.nextInt();
		int English = scanner.nextInt();
		int Math = scanner.nextInt();
		System.out.println(s + ' ' + Chinese + ',' + English + ',' + Math);
	}
}