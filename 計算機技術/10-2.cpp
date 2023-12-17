#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void check_ISBN10(char *enter)
{
	int mpy,i,sum=0;
	for(mpy=10,i=0;mpy>=1;mpy--,i++)
	{
		if(48<=*(enter+i)&&*(enter+i)<=57)
		{
			*(enter+i)=*(enter+i)-48;
			*(enter+i)=*(enter+i)*mpy;
		}
		else if(*(enter+i)=='X'||*(enter+i)=='x')
		{
			*(enter+i)=10;
			*(enter+i)=*(enter+i)*mpy;
		}
		sum=sum+*(enter+i);
	}
	if(sum%11==0) printf("The ISBN code is correct!!\n");
	else printf("The ISBN code is wrong!!\n");
}
void check_ISBN13(char *enter)
{
	int i,sum=0,check;
	for(i=0;i<=11;i++)
	{
		if(48<=*(enter+i)&&*(enter+i)<=57)
		{
			*(enter+i)=*(enter+i)-48;//turn to numbers;
		}
		if(i%2!=0)//place
		{
		 *(enter+i)=*(enter+i)*3;
		}
		sum=sum+*(enter+i);
	}
	sum=sum%10;
	*(enter+12)=*(enter+12)-48;
	if(*(enter+12)==0)
	{
		check=0;
	}
	else check=10-*(enter+12);
	if(sum==check)
	{
		printf("The ISBN code is correct!!\n");
	}
	else printf("The ISBN code is wrong!!\n");
}
int main(void)
{
	char enter[14];
	while(true)
	{
		printf("Please input an ISBN code:");
		scanf("%s",&enter);
		int n=strlen(enter);
		if(n==10)
		{
			check_ISBN10(enter);
		}
		else if(n==13)
		{
			check_ISBN13(enter);
		}
		else
		{
			printf("Error!");
			break;
		}
	}
	
}
