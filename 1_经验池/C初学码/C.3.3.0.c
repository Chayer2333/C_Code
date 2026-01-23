#include <stdio.h>
int main()
{
	float a,b,c,x;
	printf("请输入a,b,c:\n");
	scanf("%f%f%f",&a,&b,&c);
	if(a>b){
		x=a;
		a=b;
		b=x;
	}
	if(a>c){
		x=a;
		a=c;
		c=x;
	}
	if(b>c){
		x=b;
		b=c;
		c=x;
	}
	printf("从小到大的顺序为:\n%f\n%f\n%f",a,b,c);
	return 0;
}
