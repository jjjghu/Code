#include <stdio.h>
#include <stdlib.h>
void sort(int *enter,int n)
{
	int temp,t;
	for(t=0;t<n-1;t++)
	{
		if(*(enter+t)>*(enter+t+1))
		{
			temp=*(enter+t);
			*(enter+t)=*(enter+t+1);
			*(enter+t+1)=temp;//swap 1 time
		}
	}//swap multiple time to get the biggest
}
int main(void)
{
	int n,i;
	printf("請輸入整數的個數:");
	scanf("%d",&n);
	int enter[n];
	for(i=0;i<n;i++)
	{
		printf("請輸入第%d個數:",i+1);
		scanf("%d",&enter[i]);
	}
	for(i=0;i<n;i++)
	{
		sort(enter,n);
	}
		printf("排序結果:");
		for(i=0;i<n;i++)
		{
			printf("%d ",enter[i]);
		}
		printf("\n");
}
