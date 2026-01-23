#include<stdio.h>
void oe(int); 
int main()
{
	int n;
	printf("请输入待检验的数：\n");
	scanf("%d",&n);
	printf("该数");
	oe(n);
	printf("奇数");
}

void oe(int n)
{
	if(n%2==1)
		printf("是");
	else
		printf("不是");
}
