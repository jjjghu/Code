#include <stdlib.h>
#include <stdio.h>
int f(int x, int y)
{
	while (x % y != 0 && y % x != 0)
	{
		if (x >= y)
			x = x % y;
		else if (x < y)
			y = y % x;
	}
	if (x > y)
		return y;
	if (x <= y)
		return x;
}

int main(void)
{
	int x, y, n;
	printf("請輸入長方形的長(公分)為...");
	scanf("%d", &x);
	printf("請輸入長方形的寬(公分)為...");
	scanf("%d", &y);
	n = f(x, y);
	printf("最少需要%d個相同的正方形，排成邊長為%d公分的正方形", (x * y) / (n * n), x * y / n);
}
