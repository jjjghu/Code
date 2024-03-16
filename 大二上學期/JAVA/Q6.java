import java.util.Scanner;
public class Q6
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		String s1 = scanner.next();
		String s2 = scanner.next();
		int x = 0, y = 0;
		int[] list = new int[60];
		for(int i = 0; i < s1.length(); i++)
		{
			if(s1.charAt(i) == s2.charAt(i))
			{
				x++;
			}
			else
			{
				list[s1.charAt(i) - 'A']++;
				list[s2.charAt(i) - 'A']++;
			}
		}
		for(int i = 0; i < 60; i++)
		{
			y += list[i] / 2;
		}
		System.out.println(x + " " + y);
	
	}
}
/*
ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz
abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
*/