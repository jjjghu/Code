#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void){ 
	char a[100];
	bool t[100][2],check=false,find=false;
	int x,y,n,ns,time,z,xs,ys,c1,c2,count=0,i,dot=0;
	printf("請輸入一個字串:");
	scanf("%s",a);
		n=strlen(a);
		ns=n;
		for(c1=0;c1<=99;c1++){
			for(c2=0;c2<2;c2++)t[c1][c2]=false;
		}
		for(;ns>0;ns--){
			for(time=n-ns+1;time>0;time--){
				if(time==n-ns+1){
					x=0;
					y=ns-1;
				}
				else{
					z=(n-ns+1)-time;
					x=0+z;
					y=ns-1+z;
				}
				xs=x;
				ys=y;
				for(;x<=ys&&y>=xs;x++,y--){
					if(a[x]!=a[y]) check = false;
					else check = true;
				//	printf("a[%d] vs a[%d] = %c vs %c\n",x,y,a[x],a[y]);
					if(check) count++;
					if(count==ns){
						t[y][0]=true;//起點 
						t[x][1]=true;//終點
						dot++;
						/*printf("\ncount = %d OH YES\n",count);
						printf("起點t[%d][0]==%d\n",y,t[y][0]);
						printf("終點t[%d][1]==%d\n",x,t[x][1]);*/
						
					}
				//	printf("count = %d\n",count);
				}
				count=0;
				}
				for(c1=0;c1<=99;c1++){
					for(c2=0;c2<2;c2++){
						if(t[c1][c2]==true){
							find = true;
							//printf("t[%d][%d]==%d\n",c1,c2,t[c1][c2]);
						}
					}
				}
				if(find){
					//printf("I found it!!!\n");
					printf("最長迴文為:");
					for(c1=0,c2=0;c1<=99;c1++){
						if(t[c1][0]==true){
							for(i=0;i<ns;i++){
								printf("%c",a[c1+i]);
							}
							if(dot>1){
								printf(",");
								dot--;
							}
						}
					}
					break;
				}
		}			
} 
