#include <stdlib.h>
#include <stdio.h>
int main(void)
{
	int a, as, i = 7, num[8], sum = 0, power = 1;
	printf("Please input a decimal number:");
	scanf("%d", &a);
	if (a < 0)
	{
		as = a * (-1);
	}
	else
	{
		as = a;
	}
	while (i >= 0)
	{
		num[i] = as % 16;
		i--;
		as /= 16;
	}
	if (a < 0)
	{
		for (i = 0; i <= 7; i++)
		{
			num[i] = 15 - num[i];
		}
		for (i = 7; i >= 0; i--)
		{
			num[i]++;
			if (num[i] < 16)
				break;
			else
				num[i] = 0;
		}
	}
	for (i = 0; i <= 6; i = i + 2)
	{
		as = num[i];
		num[i] = num[i + 1];
		num[i + 1] = as;
	}
	for (i = 7; i >= 0; i--)
	{
		sum = sum + num[i] * power;
		power = power * 16;
	}
	if (num[0] >= 8)
		sum = sum - 4294967296;
	printf("%d", sum);
}
