#define Pi 3.1415926535
#include <stdio.h>
int main()
{
	printf("hp world");
	int d,e,a=1,b=2,c;
	c=3; 
	float f1=1.1,r=2.2,area;
	double d1=1.1234567890;
	char ch1='cc';
	area=Pi*r*r;
	printf("输入d,e的只：\n");
	scanf("%d%d",&d,&e);
	printf("\n d=%d,e=%d \n",d,e);
	printf("团的面积area=%.2f \n",area);
	printf("a=%d,b=%d,c=%d \n",a,b,c);
	printf("f1=%.3f,d1=%lf \n",f1,d1);
	printf("ch1=%c \n",ch1);
	return 0;
	
}
