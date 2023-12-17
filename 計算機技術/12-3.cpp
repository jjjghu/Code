#include <stdio.h>
int years(int y,int ey)
{
	int year4 = (y-1)/4;
	int year100 = (y-1)/100;
	int year400 = (y-1)/400;
	int min = year4 - year100 + year400;
	
	int x4 = (ey-1)/4;
	int x100 = (ey-1)/100;
	int x400 = (ey-1)/400;
	int max = x4 - x100 + x400;
	
	return max-min;
}
int main(void)
{
	bool add,sub;
	int y,m,d;
	int ey,em,ed;
	int result = 0;
	int r1=0,r2=0;
	printf("請輸入西元開始日期(yyyy/mm/dd)為...");
	scanf("%d/%d/%d",&y,&m,&d);
	printf("請輸入西元結束日期(yyyy/mm/dd)為...");
	scanf("%d/%d/%d",&ey,&em,&ed);
	result = years(y,ey);
	if(y%400==0) add = true;
	else if(y%4==0&&y%100!=0) add = true;
	if(y%4!=0) add = false;
	else if(y%100==0&&y%400!=0) add = false;
	if(add)
	{
		if(m<=2&&d<=28)	result++;
	}
	if(ey%400==0) sub = true;
	else if(ey%4==0&&ey%100!=0) sub = true;
	if(ey%4!=0) add = false;
	else if(ey%100==0&&ey%400!=0) sub = false;
	
	if(sub)
	{
		if(em<=2&&ed<=28)	result--;
	}
	printf("此期間的2月29日共有%d次",result);
	
}
