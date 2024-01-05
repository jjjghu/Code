#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
int main(void)
{
	char x[16]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	char hex[8]{'0', '0', '0', '0', '0', '0', '0', '0'};
	char temp[8]{'0', '0', '0', '0', '0', '0', '0', '0'};
	char complement[8];
	int i = 0, j, a, as, count = 0, sum = 0, time, n;
	bool sign;
	printf("Please input a decimal number:");
	scanf("%d", &a);
	as = a;
	if (as > 0)
		sign = true;
	else
		sign = false;
	a = abs(a);
	if (as > 0)
	{
		while (a > 0 || count < 8)
		{
			hex[i++] = x[a % 16];
			a = a / 16;
			count++;
		}
	}
	else if (as < 0)
	{
		// complement
		while (a > 0 || count <= 8)
		{
			hex[i++] = x[15 - (a % 16)];
			if (count == 0 && hex[0] != 'F')
			{
				hex[0] = x[(15 - (a % 16)) + 1];
			}
			a = a / 16;
			count++;
		}
		// 進位
		if (hex[0] == 'F')
		{
			for (count = 0; count < 8; count++)
			{
				if (hex[count] == 'F')
				{
					hex[count] = '0';
					switch (hex[count + 1])
					{
					case 'A':
						hex[count + 1] = 'B';
						break;
					case 'B':
						hex[count + 1] = 'C';
						break;
					case 'C':
						hex[count + 1] = 'D';
						break;
					case 'D':
						hex[count + 1] = 'E';
						break;
					case 'E':
						hex[count + 1] = 'F';
						break;
					case '9':
						hex[count + 1] = 'A';
						break;
					default:
						hex[count + 1] = hex[count + 1] + 1;
						break;
					}
					count++;
				}
			}
		}
	}
	for (i = 0; i <= 6; i = i + 2)
	{ // 加密
		temp[i] = hex[i + 1];
		temp[i + 1] = hex[i];
	}
	/*for(i=7;i>=0;i--){-
			printf("%d位數%c , ",i+1,temp[i]);
		}
		printf("\n");*/
	if (temp[7] - '0' <= 7)
		sign = true;
	else
		sign = false;
	if (sign == false)
	{ // 二次complement加密內容，輸出加上負號;
		// printf("還原\n");
		for (i = 7; i >= 0; i--)
		{
			time = 0;
			for (count = 0; count <= 15; count++)
			{
				if (temp[i] == x[count])
				{
					time++;
					if (time <= 1)
					{
						temp[i] = x[15 - count];
						// printf("%d位數%c ,i=%d, count=%d, time=%d\n",i+1,temp[i],i,count,time);
					}
				}
			}
		}
	}
	/*for(i=7;i>=0;i--){
		printf("%c ",temp[i]);
	}
	printf("\n");*/
	if (temp[7] - '0' >= 8)
	{
		n = 6;
		sum = -2147483648;
	}
	else
	{
		n = 7;
		sum = 0;
	}
	for (i = 0; i <= n; i++)
	{
		switch (temp[i])
		{
		case 'A':
			sum = sum + 10 * pow(16, i); /*printf("%d\n",sum)*/
			;
			break;
		case 'B':
			sum = sum + 11 * pow(16, i); /*printf("%d\n",sum)*/
			;
			break;
		case 'C':
			sum = sum + 12 * pow(16, i); /*printf("%d\n",sum)*/
			;
			break;
		case 'D':
			sum = sum + 13 * pow(16, i); /*printf("%d\n",sum)*/
			;
			break;
		case 'E':
			sum = sum + 14 * pow(16, i); /*printf("%d\n",sum)*/
			;
			break;
		case 'F':
			sum = sum + 15 * pow(16, i); /*printf("%d\n",sum)*/
			;
			break;
		default:
			sum = sum + (temp[i] - '0') * pow(16, i); // printf("%d\n",sum);
		}
	}
	if (sign == true)
		printf("%d\n", sum);
	else if (sign == false)
		printf("-%d\n", sum + 1);
}
