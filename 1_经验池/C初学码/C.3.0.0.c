#include <stdio.h>
int main()
{
	int a,b,c;
	printf("请输入俩个待交换的整数：\n");
	scanf("%d%d",&a,&b);
	c=a;
	a=b;
	b=c;
	printf("%d,%d\n",a,b);
	a=a+b;
	b=a-b;
	a=a-b;
	printf("%d,%d\n",a,b);	// 该方式有可能导致算数溢出或精度丢失
	return 0;
}

