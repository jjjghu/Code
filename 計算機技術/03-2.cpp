#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int a = 0, b = 1, as, n, count = 0;
	printf("Please input a number:");
	scanf("%d", &n);
	if (n == 1)
		printf("%d", a);
	else if (n == 2)
		printf("%d, %d", a, b);
	else if (n > 2)
	{
		printf("%d", a);
		while (count < n)
		{
			printf(", %d", b);
			as = a;
			a = b;
			b = as + b;
			count++;
		}
	}
}
