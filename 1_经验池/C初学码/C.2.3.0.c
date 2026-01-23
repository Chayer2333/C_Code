#include <stdio.h>
int main()
{
	float a,b,c,l;
	printf("请输入三个实数: \n");
	scanf("%f%f%f",&a,&b,&c);
	l=(a+b+c)/3;
	printf("平均值为：%f\n",l);
	return 0;
}
