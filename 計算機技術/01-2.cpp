#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int a;
	float b;
	while (scanf("%d", &a) != EOF)
	{
		b = a;
		b /= 5;
		if (a > 100)
		{
			printf("%d is a latge integer.\n", a);
			switch (a % 5)
			{
			case 0:
				printf("%d is divided by 5", a);
				break;
			case 1:
				printf("%d+5=%d", a, a + 5);
				break;
			case 2:
				printf("%d-5=%d", a, a - 5);
				break;
			case 3:
				printf("%d*5=%d", a, a * 5);
				break;
			case 4:
				printf("%d/5=%.2f", a, b);
				break;
			}
		}
		else if (a > 10)
		{
			printf("%d的十位數為%d\n", a, a / 10);
			printf("%d的個位數為%d", a, a % 10);
		}
		else if (a > 0)
			printf("%d is a small integer", a);
		else
			printf("%d is not a positive number!", a);
		printf("\n");
	}
}
