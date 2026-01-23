#include <stdio.h>
#include <math.h>
int main()
{
	float a,b,c,dala,x1,x2;
	printf("请输入系数：");
	scanf("%f%f%f",&a,&b,&c);
	dala=b*b-4*a*c;
	if(dala>=0&&a!=0)
	{
	x1=(-b-sqrt(dala))/(2*a);
	x2=(-b+sqrt(dala))/(2*a);
	printf("方程%.3f*x^2+%.3f*x+%.3f=0的解为：\n",a,b,c);
	printf("\n x1=%.3f,x2=%.3f",x1,x2);
	}
	else
	{
	printf("无实数解或不符合定义");	
	}
	return 0;
}
