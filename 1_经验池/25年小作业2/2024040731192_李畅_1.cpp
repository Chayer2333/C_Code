#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 10000
bool mod(int a,int b);

int main()
{
	int a[N];
	int i,count;
	//生成10000个随机数 
	for(i=0; i<N; i++)
		printf("%d\t",a[i]=rand());
	//判断程序
	for(i=0, count=0; i<N; i++)
		if(mod(a[i],3)&&mod(a[i],7))
			count++;
	printf("\n\n共生成%d个数,满足条件的数共有：%d 个",N,count);
}

bool mod(int a,int b)	// 模运算函数
{
	if(b==0) return false;
	else	 return a%b==0;
}
