#include<stdio.h>
#include<stdlib.h>
int main(void){
	char name[20],dep;
	int s1,s2;
	float aver;
	printf("Please input your name.....");
	scanf("%s",&name);
	printf("Please input your department....(a:資工b:電機c:電子)");
	scanf("%*c%c",&dep);
	printf("Please input your score on test 1....");
	scanf("%d",&s1);
	printf("Please input your score on test 2....");
	scanf("%d",&s2);
	aver = float(s1+s2)/2;
	printf(":-------------------------------------------:\n");
	printf(":   Name   :Department:Test 1:Test 2:Average:\n");
	printf(":----------+----------+------+------+-------:\n");
	printf(":%-10s:%-10c:%6d:%6d:%7.2f:\n",name,dep,s1,s2,aver);
	printf(":----------+----------+------+------+-------:");
} 
