import java.util.Scanner;
import java.text.DecimalFormat;
class Subject // 父類別Subject
{
	double mid_score; // 期中考成績
	double final_score;// 期末考成績
	double quiz; // 小考成績

	public Subject()
	{
	}

	public Subject(double m, double f, double q)
	{
		this.mid_score = m;
		this.final_score = f;
		this.quiz = q;
	}

	public double score()
	{
		return mid_score * 0.4 + final_score * 0.4 + quiz * 0.2;
	}
}
class Chinese extends Subject
{
	Chinese(double m, double f)
	{
		super(m,f,0);
	}
	@Override
	public double score()
	{
		return mid_score * 0.5 + final_score * 0.5;
	}
}
class English extends Subject
{
	English(double f, double q)
	{
		super(0,f,q);
	}
	@Override
	public double score()
	{
		return final_score * 0.7 + quiz * 0.3; 
	}
}
class S1154041
{
	public static void main(String args[])
	{
		Scanner scn = new Scanner(System.in);
		int n = scn.nextInt();
		double ans = 0;
		for(int i = 0; i < n; i++)
		{
			int a, b; // input the grade
			double cur = 0;
			
			int choose = scn.nextInt();
			if(choose == 1)
			{
				a = scn.nextInt();
				b = scn.nextInt();
				Chinese student = new Chinese(a,b);
				cur = student.score();
			}
			else
			{
				a = scn.nextInt();
				b = scn.nextInt();
				English student = new English(a,b);
				cur = student.score();
			}
			
			if(cur > ans)
			{
				ans = cur;
			}
		}
		DecimalFormat f = new DecimalFormat("0.0");
		System.out.println(f.format(ans));
	}
}