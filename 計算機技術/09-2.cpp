#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(void)
{
	int i, j, sum = 1;
	char input[12];
	int count[12], num[12];
	printf("Please input a string:");
	gets(input);
	int n;
	n = strlen(input);
	for (i = 0; i < 12; i++)
	{
		count[i] = 0;
		num[i] = 0;
	}
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (input[i] == input[j] && input[i] != '%')
			{
				count[i]++;
				// printf("count[%d] = %d\n",i,count[i]);
				input[j] = '%';
				// printf("input[%d] = %c\n",j,input[j]);
			}
		}
		// printf("count[%d] = %d\n",i,count[i]);
	}
	for (i = 1; i <= n; i++)
	{
		sum = sum * i;
		// printf("%d! = %d\n",n,sum);
	}
	for (i = 0; i <= n; i++)
	{
		if (count[i] != 0)
			count[i]++;
		if (count[i] != 0)
		{
			for (; count[i] > 0; count[i]--)
			{
				sum = sum / count[i];
				// printf("count[%d] = %d \n",i,count[i]);
			}
			// printf("\n");
		}
	}
	printf("The number of permutation is %d", sum);
}
