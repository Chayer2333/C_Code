/*
编写函数求1+2+3+…+100的和。
*/
#include"stdio.h"
//求从n到m的连续自然数的累加和
//数据类型 函数名称（参数） 
int funsum(int n,int m)//形参 
{
	int i,sum=0;
	for(i=n;i<=m;i++){
		sum=sum+i;
	}//求n~m的累加和 
	return sum;
}
int main()
{
	int sum,a,b;
	a=1;
	b=100;
	sum=funsum(a,b);
	printf("1+2+3+...+100=%d\n",sum);
	int sum1=funsum(1,10);//实参 
	printf("1+2+3+...+10=%d\n",sum1);
	return 0;
}
