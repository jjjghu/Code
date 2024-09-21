#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int a, b;
	for (a = 1; a < 10; a++)
	{
		for (b = 1; b < 10; b++)
		{
			printf("%d*%d=%-3d", b, a, b * a);
		}
		printf("\n");
	}
}
