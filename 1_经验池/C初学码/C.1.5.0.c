#define Pi 3.1415926535          //定义符号常量  
#include <stdio.h>
int main()
{
	float R,S,l;
	printf("R的地址为%x\n",&R);  //&在内存中寻"R"的地址 
	printf("请不要不输入半径：");
	scanf("%f",&R);              //scanf为控制台输入函数，对向为内存中的"R"，数据型为实数 
	
	S=Pi*R*R;                    //计算面积，无R^2这个写法 
	l=2*Pi*R;                    //从结果定义算式，从右向左计算 
	
	printf("圆的面积为：%f\n",S); 
	printf("圆的周长为：%f\n",l);
	
	return 0;
}
