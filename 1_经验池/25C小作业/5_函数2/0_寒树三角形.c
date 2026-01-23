#include<stdio.h>
void print_triangle(int);//再加一个参数控制形状 
int main()
{
	int n;
	printf("请输入行数: ");
	scanf("%d",&n);
	print_triangle(n);
	return 0;
}



void print_triangle(int n)
{
	int i,j;
	for(i=0;i<=n;i++)
	{
		for(j=0;j<i;j++)
			printf("*");
		printf("\n");
	}
}
