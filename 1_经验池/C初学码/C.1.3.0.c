#include <stdio.h>
int main()
{
	float f_1;  //单精度实型 
	double f_2; //双精度实型 
	f_1=2.33;
	f_2=10.001;
	
	printf("f_1=%f  ,  f_2=%lf \n\n",f_1,f_2);//%f以实数输出，%lf精度更高，都默认6位 
	printf("f_1=%e  ,  f_2=%e  \n",f_1,f_2);  //%e以科学计数法输出 
	printf("f_1=%10.3f \n\
f_2=%4.2lf",f_1,f_2);                         //%10.3f给该数分配十个字符位，其中小数后三位，注意小数点也是一位

	return 0;
}
