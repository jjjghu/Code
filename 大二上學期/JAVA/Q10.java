import java.util.Scanner;

public class Q10
{
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int[][] list = new int[n][2];

        for (int i = 0; i < n; i++)
        {
            list[i][0] = scanner.nextInt();
            list[i][1] = scanner.nextInt();
        }

        // sort job;
        for(int i = 0; i < n; i++)
        {
        	for(int j = 0; j < n; j++)
        	{
        		if(list[i][1] < list[j][1])
        		{
        			int a = list[i][0];
        			int b = list[i][1];

        			list[i][0] = list[j][0];
        			list[i][1] = list[j][1];
        			
        			list[j][0] = a;
        			list[j][1] = b;
        		}
        	}
        }

        int endTime = 0; 
        int res = 0;

        for (int i = 0; i < n; i++)
        {
            if (list[i][0] >= endTime)
            {
                endTime = list[i][1];
                res++;
            }
        }
        System.out.println(res);
    }
}
