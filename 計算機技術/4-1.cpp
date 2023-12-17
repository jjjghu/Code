#include<stdio.h>
#include<stdlib.h>
int main(void){
	int num,a,t,Total=0;
	printf("Please input a number:");
	scanf("%d",&num);
	for(t=2;t<=num;t++){
		for(a=2;a<=t;a++){
			if(t%a==0){
				break;
			}
		}
		if(a==t){
			Total++;
			if(a!=2) printf(", %d",t);
			else printf("%d",t);
		}
	}
	printf("\nTotal is %d",Total);
	
}
