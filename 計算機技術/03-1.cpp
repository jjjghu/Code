#include<stdlib.h>
#include<stdio.h>
int main(void){
	int a,b,sum;
	char c='y';
	do{
		printf("Number 1:");
		scanf("%d",&a);
		printf("Number 2:");
		scanf("%d",&b);
		if(a>b){
		printf("Error!!Number1>Number2!!\n");
		continue;}
		sum=0;
		while(a<b+1){
			sum=sum+a;
			a++;
		}
		printf("Sum=%d",sum);
		printf("\nAgain(Y/N)??");
		scanf("%*c%c",&c);
	}while(c=='y'||c=='Y');
}
