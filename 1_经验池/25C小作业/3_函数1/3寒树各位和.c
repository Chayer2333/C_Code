#include<stdio.h>
int cardinality_sum(int); 
int main()
{
	int n;
	printf("请输入待计算的数：\n");
	scanf("%d",&n);
	printf("该数各位数字之和为：%d",cardinality_sum(n));
}

int cardinality_sum(int n)
{
	int sum=0;
	for(;n!=0;) 
	{
		sum+=n%10;
		n/=10;
	}
	return sum;
}
