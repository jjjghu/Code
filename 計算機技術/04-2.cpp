#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int a1, a2, a4 = 1, as;
	printf("Please input two integers:");
	scanf("%d %d", &a1, &a2);
	if (a1 < a2)
	{
		as = a1;
		a1 = a2;
		a2 = as;
	}
	while (a4 != 0)
	{
		a4 = a1 % a2;
		a1 = a2;
		a2 = a4;
	}
	printf("GCD is %d", a1);
	return 0;
}
