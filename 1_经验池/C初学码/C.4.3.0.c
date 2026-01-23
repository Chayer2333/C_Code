/*
求100～200之间的不能被3整除的数，并按每行10个数的格式输出。
*/
#include <stdio.h>
int main()
{
	 int n,i=0;//i不被3整除的数的个数 
	 for (n=100;n<=2000;n++)
	 {
		if (n%3==0){ 
			continue;//结束本次循环，继续进行下一次新的循环 
		} 
		printf("%6d",n);
		i++;
		if(i%10==0){ 
			printf("\n");
		} 
	 }
	 printf("\n");
	 return 0;
} 
