#include <stdio.h>
#include <string.h>
int main(void)
{
	bool dupe = false;
	char word[100][20];
	char test[20];
	int dt[100];
	for (int i = 0; i < 100; i++)
		dt[i] = 1;
	int count = 0;
	int n;
	FILE *enter;
	FILE *result;
	enter = fopen("t3.txt", "r");
	result = fopen("result2.txt", "w");
	if (enter != NULL && result != NULL)
	{
		while ((fscanf(enter, "%s", test)) != EOF)
		{
			n = strlen(test);
			if (test[n - 1] == '.' || test[n - 1] == ',')
				test[n - 1] = '\0';
			if (count == 0)
			{
				strcpy(word[count], test);
				count++;
				continue;
			}
			for (int i = 0; i < count; i++)
			{
				if (strcmp(word[i], test) == 0)
				{
					dt[i]++;
					dupe = true;
					break;
				}
				else
					dupe = false;
			}
			if (dupe == false)
			{
				strcpy(word[count], test);
				count++;
			}
		}
		for (int i = 0; i < count; i++)
		{
			fprintf(result, "%s:", word[i]);
			fprintf(result, "%d\n", dt[i]);
		}
	}
	fclose(enter);
	fclose(result);
}
