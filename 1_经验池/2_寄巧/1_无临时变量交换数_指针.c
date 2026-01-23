#include<stdio.h>
int main()
{
	int a,b;
	printf("请输入两个树：");
	scanf("%d%d",&a,&b);
	a+=b;b=a-b;a-=b; // 交换a和b 而不使用临时变量
	printf("\n%d,%d",a,b); 
}
