#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(void)
{
	bool dupe[2000] = {false};

	char test[100];
	char word[2000][100];
	int counter = 0;
	char word1[2000][100];
	int counter1 = 0;

	FILE *enter, *enter1, *result;
	enter = fopen("t10.txt", "r");
	enter1 = fopen("t11.txt", "r");
	result = fopen("result.txt", "w");
	if (enter != NULL && enter1 != NULL)
	{
		int num = 0; // 用來輸入東西的變數
		while ((fscanf(enter, "%s", test)) != EOF)
		{
			int n = strlen(test);
			if (test[n - 1] == '.' || test[n - 1] == ',')
				test[n - 1] = '\0';		// 蓋掉最後的逗號句號
			for (int i = 0; i < n; i++) // 將輸入轉換成小寫
			{
				test[i] = tolower(test[i]);
			}
			strcpy(word[num], test); // 將文字存入word
			num++;
			counter++; // 計算t10總數
		}
		num = 0;
		while ((fscanf(enter1, "%s", test)) != EOF)
		{
			int n = strlen(test);
			if (test[n - 1] == '.' || test[n - 1] == ',')
				test[n - 1] = '\0';
			for (int i = 0; i < n; i++)
			{
				test[i] = tolower(test[i]);
			}
			strcpy(word1[num], test); // 將文字複製進word1
			num++;
			counter1++; // 計算t11總數
		}
	}
	int i = 0, j, strike = 0;
	int tempi, tempj;
#define target 7
	// printf("%s %s",word[0],word[j]);
	for (i = 0; i < counter; i++)
	{
		for (j = 0; j < counter1; j++)
		{
			// printf("%s vs %s\n",word[i],word1[j]);
			if (strcmp(word[i], word1[j]) == 0) // same check strike
			{
				// printf("same\n");
				strike = 0;
				tempi = i, tempj = j;
				while (strcmp(word[tempi], word1[tempj]) == 0) // 判斷連續相同次數
				{
					if (strlen(word[tempi]) == 0 || word1[tempj] == 0)
						break;
					// printf("extra %s vs %s\n",word[tempi],word1[tempj]);
					strike++;
					tempi++;
					tempj++;
				}
				if (strike >= target) // 連續相同次數超過 7 代表重複
				{
					for (int len = tempi - strike; len < tempi; len++)
					{
						dupe[len] = true;
					}
					// printf("strike = %d,tempi = %d, tempj = %d\n",strike,tempi,tempj);
				}
				else
					strike = 0; // 重置連續相同次數
			}
		}
	}
	float ans = 0;
	float cal = counter; // 使用cal 暫存 (float) counter
	for (int len = 0; len < counter; len++)
	{
		if (dupe[len])
		{
			printf("%s\n", word[len]); // 印出相同物
			// fprintf(result,"%s\n",word[len]);
			ans++;
		}
	}
	printf("%.0f / %d = %.2f%c", ans, counter, (ans / cal) * 100, '%');
	fprintf(result, "%.0f / %d = %.2f%c", ans, counter, (ans / cal) * 100, '%');
	fclose(enter);
	fclose(enter1);
	fclose(result);
}
