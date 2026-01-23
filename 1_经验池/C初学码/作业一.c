#include <stdio.h>
int main()
{
	float a,b,c,d;
	printf("请输入长、宽：\n");
	scanf("%f%f",&a,&b);
	c=a*b;
	d=2*(a+b);
	printf("面积为：%f\n周长为：%f",c,d);
	return 0;
}
