#include<stdio.h>
float abs(float); 
int main()
{
	float x;
	printf("请输入待计算的数：\n");
	scanf("%f",&x);
	printf("绝对值为：%f",abs(x));
}

float abs(float x)
{
	if(x>=0)
		return x;
	else
		return -1*x;
}

