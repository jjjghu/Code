#include <stdlib.h>
#include <stdio.h>
int main(void)
{
	int n, a = 0, b = 1, now, i, Total = 0;
	printf("Please input a number:");
	scanf("%d", &n);
	for (now = 2; now <= n; now++)
	{
		for (i = 2; i <= now; i++)
		{
			if (now % i == 0)
				break;
		}
		if (now == i)
		{
			if (a > b)
				b = now;
			else if (a < b)
				a = now;
		}
		if (a - b == 2)
		{
			printf("(%d,%d)", b, a);
			Total++;
		}
		if (a - b == -2)
		{
			printf("(%d,%d)", a, b);
			Total++;
		}
	}
	printf("\nTotal is %d", Total);
}
