import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
public class Q9
{
    public static void main(String args[])
    {
        Scanner scanner = new Scanner(System.in);
        String s = scanner.nextLine();

        int n = s.length();
        int maxLen = 1;
        boolean[][] dp = new boolean[n][n];
        List<String> res = new ArrayList();

        for(int i = 0; i < n; i++)
        {
            dp[i][i] = true;
            res.add(s.substring(i,i+1));
        }

        for(int len = 2; len <= n; len++)
        {
            for(int begin = 0; begin <= n - len; begin++)
            {
                int end = begin + len - 1;
                if(s.charAt(begin) == s.charAt(end) && (len == 2 || dp[begin + 1][end - 1]))
                {
                    dp[begin][end] = true;
                    if(len > maxLen)
                    {
                        maxLen = len;
                        res.clear();
                    }
                    res.add(s.substring(begin, end + 1));
                }
            }
        }
        for(String r:res) System.out.print(r + " ");
    }
}