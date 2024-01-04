#include <stdlib.h>
#include <stdio.h>
int main(void)
{
	int n, x, y, count;
	printf("Please input the size of matrix:");
	scanf("%d", &n);
	int a[n][n], b[n][n], c[n][n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			c[i][j] = 0;
	}
	printf("Please input matrix1:\n");
	for (y = 0; y < n; y++)
	{
		for (x = 0; x < n; x++)
		{
			scanf("%1d", &a[y][x]);
		}
	}
	printf("Please input matrix2:\n");
	for (y = 0; y < n; y++)
	{
		for (x = 0; x < n; x++)
		{
			scanf("%1d", &b[y][x]);
		}
	}
	printf("matrix1 * matrix2 =\n");
	for (y = 0; y < n; y++)
	{
		for (x = 0; x < n; x++)
		{
			for (count = 0; count < n; count++)
			{
				c[y][x] = c[y][x] + a[y][count] * b[count][x];
			}
		}
	}
	for (y = 0; y < n; y++)
	{
		for (x = 0; x < n; x++)
		{
			printf("%d ", c[y][x]);
		}
		printf("\n");
	}
}
