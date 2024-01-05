#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(void)
{
	FILE *input, *output;
	input = fopen("t15.txt", "r");
	output = fopen("result.txt", "w");
	char enter[100];
	while (fscanf(input, "%s", enter) != EOF)
	{
		int i, j = 0, test = 0;
		bool flag = true;
		char alpha[26] = {0};
		char list[26] = {0};
		for (i = 0; i < strlen(enter); i++)
		{
			enter[i] = tolower(enter[i]);
			alpha[enter[i] - 'a']++;
		}
		for (i = 0; i < 26; i++)
		{
			// printf("%d",alpha[i]);
			if (alpha[i] != 0)
				test++;
		}
		// printf("\n");
		if (test == 1)
		{
			printf("NO\n");
			fprintf(output, "NO\n");
			continue;
		}
		for (i = 0; i < 26; i++)
		{
			for (j = 0; j < 26; j++)
			{
				if (alpha[i] != 0 && alpha[j] != 0 && i != j)
				{
					if (alpha[i] == alpha[j])
						flag = false;
				}
			}
		}
		if (flag)
		{
			printf("YES\n");
			fprintf(output, "YES\n");
		}
		else
		{
			printf("NO\n");
			fprintf(output, "NO\n");
		}
	}
	fclose(input);
	fclose(output);
}
