#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int a, b, N, sum = 0, as, bestsum;
	printf("Please input the Lowerbound and the upperbound:");
	scanf("%d %d", &a, &b);
	N = a;
	while (a <= b)
	{
		as = a;
		sum = as;
		while (as != 1)
		{
			if (as % 2 == 0)
				as = as / 2;
			else
				as = as * 3 + 1;
			sum = sum + as;
		}
		if (N == a)
			bestsum = sum;
		else if (bestsum < sum)
		{
			N = a;
			bestsum = sum;
		}
		a++;
	}
	printf("N=%d Sum=%d", N, bestsum);

	return 0;
}
