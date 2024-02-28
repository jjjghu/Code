import java.util.Scanner;
public class Q12
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		int[] weight = new int[n];
		int[] value = new int[n];
		for(int i = 0; i < n; i++)
		{
			weight[i] = scanner.nextInt();
			value[i] = scanner.nextInt();
		}
		int MaxWeight = scanner.nextInt();
		int[][] dp = new int[n+1][MaxWeight+1];
		for(int item = 1; item <= n; item++)
		{
			for(int w = 1; w <= MaxWeight; w++)
			{
				if(weight[item - 1] <= w) // 這裡的偏移是因為陣列中為 0 ~ n-1
				{
					dp[item][w] = Math.max(dp[item-1][w], dp[item-1][w - weight[item-1]] + value[item-1]);
					// dp 當中沒有偏移, item - 1 代表沒有放入的狀態
				}
				else
				{
					dp[item][w] = dp[item-1][w];
				}
			}
		}
		System.out.println(dp[n][MaxWeight]);
	}
}