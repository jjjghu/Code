#include<stdlib.h>
#include<stdio.h>
int main(void){
 		int n,all,list=0,now;
		printf("Please input a number:");
		scanf("%d",&all);
		for(now=1;list!=all;now++){
			n=now;
			while(n%2==0||n%3==0||n%5==0){
				if(n%2==0) n/=2;
				if(n%3==0) n/=3;
				if(n%5==0) n/=5;
			}
			if(n==1){
				list++;
				if(list==1) printf("%d",now);
				else printf(",%d",now);
				
			}
		}
		














} 
