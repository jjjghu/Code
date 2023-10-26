import java.util.Scanner;
public class Q7
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		int n;
		int k;
		n = scanner.nextInt();
		k = scanner.nextInt();
		boolean[] list = new boolean[n+1];
		for(int i = 0; i < list.length; i++) list[i] = true;
		for(int i = 2; i <= k; i++)
		{
			int temp = i;
			while(temp <= n)
			{
				list[temp] = !list[temp];
				temp += i;
			}
		}
		for(int i = 1; i < list.length; i++)
		{
			if(list[i])
				System.out.print(i + " ");
		}
	}
}