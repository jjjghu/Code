import java.util.Scanner;
import java.util.ArrayList;
public class Q11
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		ArrayList<Long> dp = new ArrayList<Long>();
		dp.add(0L);
		dp.add(1L);
		for(int i = 2; i <= n; i++)
		{
			Long value = dp.get(i-1) + dp.get(i-2);
			dp.add(value);
		}
		System.out.print(dp.get(n));
	}
}