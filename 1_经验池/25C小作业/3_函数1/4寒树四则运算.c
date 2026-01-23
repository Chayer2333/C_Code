#include<stdio.h>
float ASMD(float,char,float); 
int main()
{
	float x,y;
	char c;
	printf("请按格式输入待计算的数：x ? y \n");
	scanf("%f%c%f",&x,&c,&y);
	printf("结果为：%.2f%c%.2f=%.2f",x,c,y,ASMD(x,c,y));
}

float ASMD(float x,char c,float y)
{
	float f=0;
	if(c=='+')
		return x+y;
	else if(c=='-')
		return x-y;
	else if(c=='*')
		return x*y;
	else if(c=='/'&&y!=0)
		return x/y;	
	else
		{
			printf("输入错误请重新输入 \n");
			return 0;
		}
}
