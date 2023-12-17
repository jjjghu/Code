#include <stdio.h>
int main(void)
{
	int people,cost,i,j,k,l;//車的數量
	int best[5] = {0};
	bool first = true;
	printf("請輸入乘客總人數:");
	scanf("%d",&people);
	for(i=0;i<=people/4+1;i++)
	{
		for(j=0;j<=people/7+1;j++)
		{
			for(k=0;k<=people/13+1;k++)
			{
				for(l=0;l<=people/16+1;l++)
				{
					if(i*4+j*7+k*13+l*16>=people)
					{
						cost = i*2500+j*3800+k*6400+l*7500;
						if(first)
						{
							best[0] = cost;
							first = false;
						}
						if(best[0]>cost)
						{
							best[0] = cost;
							best[1] = i;
							best[2] = j;
							best[3] = k;
							best[4] = l;
						}
					}
				}
			}
		}
	}
	printf("最少需要%d元\n",best[0]);
	printf("四門房車%d台\n",best[1]);
	printf("商務休旅車%d台\n",best[2]);
	printf("小型巴士%d台\n",best[3]);
	printf("中型巴士%d台\n",best[4]);
	
}
 
