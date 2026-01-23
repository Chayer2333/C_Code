#include <stdio.h>
int main()
{
	int a=5,b,d;   //运算中的优先级为：double>float>int,char会依表转化成int再运算 
	float c;
	char e='e';
	d=(int)e/2;    //自动转化（int)e/2=101/2=50.5 
	b=a/2;
	c=(float)a/2;  //=(float)强制声明类型转化 
	printf("\n b=%d, c=%f, d=%d \n",b,c,d);
	return 0;
}
