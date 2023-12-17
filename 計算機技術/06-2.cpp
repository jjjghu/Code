#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(void){
	char input[17];
	int n,num[17],a,sum;
	while(1){
		printf("請輸入卡號:");
		scanf("%s",input);
		n=strlen(input);
		if(!(n==15||n==16)){
			printf("Error! 非15或16卡號數字!");
			break;
		}
		for(a=0;a<n;a++){
			num[a]=(int)input[a]-48;
		}
		int check = 0;
		for(a=0;a<n;a++){
			if(num[a]<0||num[a]>9) check=1;
		}
		if(check==1){
			printf("Error! 非15或16卡號數字!");
			break;
		}
		if(n==15){
			for(a=0,sum=0;a<n-1;a++){
				if(a%2!=0){
					num[a]=num[a]*2;
					num[a]=num[a]%10+num[a]/10;
				}
				sum=sum+num[a];
			}
			sum=sum%10;
			if(sum==0&&sum==num[14]){
				printf("卡號正確!!\n");
				continue;
			}
			else sum=10-sum;
			if(sum==num[14]) printf("卡號正確!!");
			else printf("卡號錯誤!!");
			
		}
		else if(n==16){
			for(a=0,sum=0;a<n-1;a++){
				if(a%2==0){
					num[a]=num[a]*2;
					num[a]=num[a]%10+num[a]/10;
				}
				sum=sum+num[a];
			}
			sum=sum%10;
			if(sum==0&&sum==num[15]){
				printf("卡號正確!!\n");
				continue;
			}
			else sum=10-sum;
			if(sum==num[15]) printf("卡號正確!!");
			else printf("卡號錯誤!!");
			
		}
		printf("\n");
		
	}

}
