#include <stdio.h>
int main(void)
{
	int n, now;
	FILE *enter, *result;
	enter = fopen("t16.txt", "r");
	result = fopen("result.txt", "w");
	while (fscanf(enter, "%d", &n) != EOF)
	{
		bool check = true;
		int list[n];
		for (int i = 0; i < n; i++)
		{
			list[i] = i + 1;
		}
		long long suma, sumb;
		suma = 1;
		if (n % 2 == 0)
		{
			sumb = (n / 2) * (n + 1);
		}
		else
		{
			sumb = ((n + 1) / 2) * n;
		}
		sumb = sumb - 3; // now == 2 situation
		if (suma == sumb)
		{
			printf("2");
			fprintf(result, "2");
			break;
		}
		for (now = 3; now < n; now++)
		{
			suma += now - 1;
			sumb -= now;
			if (suma == sumb)
			{
				printf("%d\n", now);
				fprintf(result, "%d\n", now);
				check = false;
				break;
			}
		}
		if (check)
		{
			printf("NULL\n");
			fprintf(result, "NULL\n");
		}
	}
	fclose(enter);
	fclose(result);
}
