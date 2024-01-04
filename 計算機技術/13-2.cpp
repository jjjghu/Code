#include <stdio.h>
#include <string.h>
int main(void)
{
	char test[22];
	FILE *enter, *result;
	enter = fopen("t12.txt", "r");
	result = fopen("result.txt", "w");
	printf("The width of word wrap:");
	int n;
	scanf("%d", &n); // enter
	int max = n;
	if (enter != NULL && result != NULL)
	{
		while ((fscanf(enter, "%s", test)) != EOF)
		{
			if (n == 0)
				n = max;
			// printf("\nstrlen = %d, n = %d\n",strlen(test),n);
			if (strlen(test) < n)
			{
				printf("%s ", test); // 123456789 and space
				fprintf(result, "%s ", test);
				n = n - strlen(test) - 1; // n = 0
				// printf("n = %d",n);
				if (n == 0)
				{
					fprintf(result, "\n");
					printf("\n");
				}
			}
			else if (strlen(test) == n)
			{
				printf("%s\n ", test);
				fprintf(result, "%s\n ", test);
				n = max - 1;
			}
			else if (strlen(test) > n)
			{
				if (strlen(test) == max) // fit perfectly to max
				{
					printf("\n%s\n ", test);
					fprintf(result, "\n%s\n ", test);
					n = max - 1;
				}
				else if (strlen(test) < max)
				{
					printf("\n%s ", test);
					fprintf(result, "\n%s ", test);
					n = max - strlen(test) - 1;
				}
				else if (strlen(test) > max && max - n > 1)
				{
					int time = 0;
					printf("\n");
					fprintf(result, "\n");
					n = max;
					int mpy = 1;
					int length = strlen(test);
					for (int i = 0; i < length; i++)
					{
						if (i == max * mpy)
						{
							printf("\n");
							fprintf(result, "\n");
							mpy++;
							time = 0;
						}
						printf("%c", test[i]);
						fprintf(result, "%c", test[i]);
						time++;
					}
					printf(" ");
					fprintf(result, " ");
					n = max - time - 1;
				}
				else if (strlen(test) > max && max - n <= 1)
				{
					int i;
					int time = 0;
					if (n == max)
					{
						for (i = 0; i < max; i++)
						{
							printf("%c", test[i]);
							fprintf(result, "%c", test[i]);
						}
						printf("\n");
						for (; i < strlen(test); i++)
						{
							printf("%c", test[i]);
							fprintf(result, "%c", test[i]);
							time++;
						}
						n = max - time - 1;
					}
					else if (n == max - 1)
					{
						for (i = 0; i < max - 1; i++)
						{
							printf("%c", test[i]);
							fprintf(result, "%c", test[i]);
						}
						printf("\n");
						fprintf(result, "\n");
						for (; i < strlen(test); i++)
						{
							printf("%c", test[i]);
							fprintf(result, "%c", test[i]);
							time++;
						}
						n = max - time - 1;
					}
				}
			}
		}
	}
	fclose(enter);
	fclose(result);
}

/*
1. enter the list and n
2. if the length is enough then put it in;
	full then next line start with space n = n-1;
	not full then next line start with nothing n = n;
   if the length is not enough then print for n time then print another;
*/
/*
1234567 12345
12345 123 1234
 1234567 123
1234
12345678901234
567890 1234567
 1234567890123
4567890
12345678
12345678901234
 1234
12345678901234
5
12345678901234
56
*/
