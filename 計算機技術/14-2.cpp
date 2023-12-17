#include <stdio.h>
int main(void)
{
	FILE *enter,*result;
	enter = fopen("t9.txt","r");
	result = fopen("result.txt","w");
	int list[30][30] = {0};
	int n,max=0;
	int time;
	int buy[1000];
	while(fscanf(enter,"%d",&n)!=EOF)
	{
		for(int i=0;i<n;i++)
		{
			fscanf(enter,"%d",&time);
			for(int j=0;j<time;j++)
			{
				fscanf(enter,"%d",&buy[j]);
			}
			for(int x=0;x<time;x++)
			{
				for(int y=x+1;y<time;y++) // buy x and y simotaniously
				{
					list[buy[x]][buy[y]]++;
				}
			}
		}
		for(int x=0;x<30;x++)
		{
			for(int y=0;y<30;y++)
			{
				if(max < list[x][y])
				{
					max = list[x][y];
				}
			}
		}
		for(int x=0;x<30;x++)
		{
			for(int y=0;y<30;y++)
			{
				if(max == list[x][y])
				{
					printf("(%d,%d)%d¦¸\n",x,y,max);
					fprintf(result,"(%d,%d)%d¦¸\n",x,y,max);
				}
			}
		}
	}
	fclose(enter);
	fclose(result);
}
