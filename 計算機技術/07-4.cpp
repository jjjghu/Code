#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int main(void){
	char a[50]="",b[50]="";
	int c[26],d[26];
	int n,s,i,check=1;
	memset(c, 0, 26); memset(d, 0 ,26);
	printf("Please input string #1:");
		gets(a);//字串輸入到a當中 
		for(i=0;i<strlen(a);i++){
			a[i]=toupper(a[i]);//字串內容全改大寫 
			if(isalpha(a[i])&&isupper(a[i])) c[a[i]-'A']++;	//a[i]代表你輸入的字元,字元減標準A=把A訂為原點 
		}
	//	for(i=0;i<26;i++) printf("%d",c[i]);
	printf("Please input string #2:");
		gets(b);
		for(i=0;i<strlen(b);i++){
			b[i]=toupper(b[i]);
			if(isalpha(b[i])&&isupper(b[i])) d[b[i]-'A']++;
		}
		//for(i=0;i<26;i++) printf("%d",d[i]);
	for(i=0;i<26;i++){
		if(c[i]!=d[i]){
			check=0;
			break;
			}
		}
		if(check==1) printf("Yes");
		else if(check==0) printf("No");
	}
