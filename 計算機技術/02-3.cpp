#include<stdio.h>
#include<stdlib.h>
int main(void){
	int a,at,c,l;
	printf("Please input a number: ");
	scanf("%d",&a);
	for(c=1;c<=a;c++){
		for(at=a-c;at>0;at--) printf(" ");
		for(l=1;l<=c*2-1;l++) printf("%d",c%10);
		printf("\n");
	}
 return 0;
} 
