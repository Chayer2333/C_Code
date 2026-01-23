#include <stdio.h>
int main()
{
	int a=3,b=5,c=8;
	float x,y,z;
	
	printf("输入 x,y,z:\n" );
	scanf("%f%f%f",&x,&y,&z);               //连着定义、输入，输入时用空格分开 
	
	printf("a=%d;b=%d;c=%d\n",a,b,c);
	printf("x=%.2f;y=%.3f;z=%.30f\n",x,y,z);//%.nf显示n位实数 
	
	return 0;
}
