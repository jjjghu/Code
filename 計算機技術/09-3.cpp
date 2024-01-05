#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main(void)
{
	int N, add, sum = 0;
	bool keep = true, me = false, suck;
	srand(unsigned(time(NULL)));
	do
	{
		N = rand() % 40;
	} while (N < 10); // 10~40

	printf("N=%d\n", N);

	if ((N - 1) % 4 != 0) // nice one
	{
		if (N % 4 == 0)
			add = 3;
		else
			add = N % 4 - 1;
	}
	if ((N - 1) % 4 == 0)
	{
		add = 1;
		suck = true;
	} // suck number
	while (keep == true)
	{
		printf("Sum=%d, ", sum);
		printf("Computer add %d\n", add);
		sum = sum + add;
		me = false;
		if (sum >= N)
		{
			if (me == true)
				printf("You lose!!");
			if (me == false)
				printf("You win!!");
			break;
		}
		printf("Sum=%d, You add:", sum);
		scanf("%d", &add);
		sum = sum + add;
		if (add != 3 && suck == true)
		{
			add = 3 - add;
			suck = false;
		}
		else
			add = 4 - add;
		me = true;
		if (sum >= N)
		{
			if (me == true)
				printf("You lose!!");
			if (me == false)
				printf("You win!!");
			break;
		}
	}
}
