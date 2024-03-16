#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int a, as, s, count, num;
	printf("Please input a number:");
	scanf("%d", &a);
	as = a;
	for (count = 0; count <= a; count++)
	{
		for (s = 1; s < as; s++)
		{
			printf(" ");
		}
		as--;
		for (num = 1; num <= count; num++)
		{
			printf("%d", num % 10);
		}
		while (num > 0)
		{
			printf("%d", num % 10);
			num--;
		}
		printf("\n");
	}
}
