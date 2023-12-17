#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void){
	char a[100],b[100];
	int n,s,i,j,check,Total=0;
	printf("Please input the string 1:");
	scanf("%s",a);
	printf("Please input the string 2:");
	scanf("%s",b);
	n=strlen(a);
	s=strlen(b);
		for(j=0;j<n;j++){
			if(a[j]==b[0]){
				check=1;
				for(i=1;i<s;i++){
					if(b[i]!=a[j+i]){
						check=0;
						break;
					}
				}
				if(check==1) Total++;
				//printf("check = %d\nTotal = %d\n",check,Total);
			}
		}
		if(Total==0){
			printf("String 2 is not a substring of string 1");
		}
		else{
			printf("String 2 is a substring of string 1\n");
			printf("Reapeated %d times",Total);
		}
}
