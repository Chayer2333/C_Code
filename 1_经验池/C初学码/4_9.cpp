/*
输入三个整数，输出其中的最大数和最小数。
*/
#include"stdio.h"
int main()
{
	int a,b,c,max,min;
	printf("请输入三个数a、b、c:\n");
	scanf("%d%d%d",&a,&b,&c);
	if(a>b)
	{ max=a;min=b;}
	else
	{max=b;min=a;}
	if(max<c)
		max=c;
	if(min>c)
		min=c;
	printf("三数%d,%d,%d中最大数：%d\n",a,b,c,max);
    printf("三数%d,%d,%d中最小数：%d\n",a,b,c,min);
	return 0;
}
