import java.util.Scanner;
public class Q8
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		int r = scanner.nextInt();
		int c = scanner.nextInt();
		int[][] list = new int[r][c];
		for(int i = 0; i < r; i++)
		{
			for(int j = 0; j < c; j++)
			{
				list[i][j] = scanner.nextInt();
			}
		}
		for(int i = 0; i < c; i++)
		{
			for(int j = 0; j < r; j++)
			{
				System.out.print(list[j][i] + " ");
			}
			System.out.println();
		}
	}
}