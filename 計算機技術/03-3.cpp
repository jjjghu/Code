#include <stdlib.h>
#include <stdio.h>
int main(void)
{
	int n1, n2, n3, n4, sum, total = 0;
	printf("N=");
	scanf("%d", &sum);

	for (n1 = 1; n1 < sum; n1++)
	{
		for (n2 = n1 + 1; n2 < sum; n2++)
		{
			for (n3 = n2 + 1; n3 < sum; n3++)
			{
				for (n4 = n3 + 1; n4 < sum; n4++)
				{
					if (n1 + n2 + n3 + n4 == sum)
						total++;
				}
			}
		}
	}
	printf("Total is %d", total);
}
