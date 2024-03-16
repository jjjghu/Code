#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int a, max, min, num, c;
	float ave = 0;
	printf("Please input the number of integers:");
	scanf("%d", &a);
	for (c = 1; c <= a; c++)
	{
		printf("Integer#%d....", c);
		scanf("%d", &num);
		ave = ave + num;
		if (c == 1)
		{
			max = num;
			min = num;
		}
		if (max < num)
			max = num;
		if (min > num)
			min = num;
	}
	printf("The average is %.2f\n", ave / a);
	printf("The maximum is %d\n", max);
	printf("The minimum is %d", min);
}
