#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int a, b, x, y;
	while (1 > 0)
	{
		printf("總數量+總腳數");
		scanf("%d+%d", &a, &b);
		if (a == 0 || b == 0)
			break;
		y = (b - 2 * a) / 2;
		x = a - y;
		if (x * 2 + y * 4 == b)
		{
			printf("雞%d隻 兔%d隻\n", x, y);
		}
		else
			printf("無解\n");
	}

	return 0;
}
