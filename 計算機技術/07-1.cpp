#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main(void){
	int a,count=0,i,c,s,sum=0;
	char b[30000];
	printf("Please input a decimal number:");
	scanf("%d",&a);
	c=a;//暫存c用來算陣列要的大小count 
	while(c!=0){
		c=c/2;
		count++;
	}
	i=count;
	int d[count];//宣告陣列大小
	for(count=i-1;count>=0;count--){
		d[count]=a%2;
		a=a/2;
	}
	for(count=0;count<i;count++){
		printf("%d",d[count]);
	}
	printf("\nPlease input a binary number:");
	scanf("%s",b);
	int n=strlen(b);
	for(s=0;n>0;n--,s++){
		b[s]=b[s]-'0';
		sum=sum+b[s]*pow(2,n-1);
	}
	printf("%d",sum);
}
