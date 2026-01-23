#include<stdio.h>
int main()
{
	int x,y;
	for(x=0;x<=20;x++)
		for(y=0;y<=34;y++) {
			if(14*x+8*y==200)
				printf("\n¹«¼¦£º%d,Ä¸¼¦£º%d£¬Ð¡¼¦:%d\n",x,y,100-x-y);
		}
	return 0;
}
