import java.util.Scanner;
class CNumber
{
	int num;
	public CNumber(int n)
	{
		num = n;
	}
	public boolean prime()
	{
		int flag = 1;
		if(num == 1)
			return false;
		for(int i = 2; i < num; i++)
		{
			if(num % i == 0)
			{
				flag = 0;
				break;
			}
		}
		if(flag == 1)
			return true;
		else
			return false;
	}
}
public class S1154041
{
	public static void main(String args[])
	{
		boolean first = true;
		int count = 0;
		Scanner s = new Scanner(System.in);
		int a = s.nextInt();
		int b = s.nextInt();
		for(int i = a; i <= b - 4; i++)
		{
			CNumber x = new CNumber(i);
			CNumber y = new CNumber(i+4);
			if(x.prime() && y.prime())
			{
				if(first)
				{
					System.out.print("(" + i + ", " + (i+4) + ")");
					first = false;
				}
				else
				{
					System.out.print(", (" + i + ", " + (i+4) + ")");
				}
				count++;
			}
		}
		System.out.print("共" + count + "組");
	}
}