#include<stdio.h>
#include<stdlib.h>
int n,count=0;

void towers(int n,char from, char aux, char to)
{
	if(n==1)
	{
		printf("ring %d: %c => %c\n",n,from,to);
		count++;
	}
	else
	{
		towers(n-1,from,to,aux);
		printf("ring %d: %c => %c\n",n,from,to);
		count++;
		towers(n-1,aux,from,to);
	}
}
int main(void)
{
	
	printf("請輸入A柱當中的環個數");
	scanf("%d",&n);
	towers(n,'A','B','C');
	printf("共需%d個步驟",count);
}
