#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
	int a, x, y, n1 = 0, n2 = 1, print = 0, n, s, Total = 0;
	printf("Please input a number:");
	scanf("%d", &a);
	for (x = 2; x <= a; x++)
	{
		for (y = 2; y < x; y++)
		{
			if (x % y == 0)
			{
				break;
			}
		}
		if (x == y)
		{
			if (n2 > n1)
			{
				n1 = n2;
				n2 = x;
			}
			else if (n2 < n1)
				n2 = x;
			n = n2 - n1 - 4;
			for (s = 1; s <= n; s++)
			{
				printf("(%d,%d,%d,%d)", n1 + s, n1 + s + 1, n1 + s + 2, n1 + s + 3);
				Total++;
				print++;
				if (print == 6)
				{
					printf("\n");
					print = 0;
				}
			}
		}
	}
	printf("Total is %d", Total);
}
