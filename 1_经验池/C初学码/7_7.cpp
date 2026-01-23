/*
编写函数求1+2+3+…+100的和。
*/
#include"stdio.h"
//求从n到m的连续自然数的累加和
int funsum(int n,int m)
{
	int i,sum=0;
	for(i=n;i<=m;i++){
		sum=sum+i;
	}
	return sum;
}
int main()
{
	int n,m;
	n=1;
	m=100;	
	printf("1+2+3+...+100=%d\n",funsum(n,m));
	return 0;
}
