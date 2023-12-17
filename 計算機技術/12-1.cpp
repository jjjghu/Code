#include <stdio.h>
#include <ctype.h>
int main(void)
{
	char test;
	int a=0,e=0,i=0,o=0,u=0;
	FILE *enter;
	FILE *result;
	enter = fopen("t1.txt","r");
	result = fopen("result1.txt","w");
	if(enter!=NULL&&result!=NULL)
	{
		while((test=fgetc(enter))!=EOF)
		{
			test = toupper(test);
			if(test=='A') a++;
			if(test=='E') e++;
			if(test=='I') i++;
			if(test=='O') o++;
			if(test=='U') u++;
		}
		fprintf(result," A E I O U \n");
		fprintf(result," %d %d %d %d %d\n",a,e,i,o,u);
	}
	fclose(enter);
	fclose(result);
}
