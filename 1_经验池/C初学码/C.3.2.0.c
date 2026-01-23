#include <stdio.h>
int main()
{
	float a,b;
	printf("请输入a,b：\n");
	scanf("%f%f",&a,&b);
	if(a>b){
		printf("%.2f与%.2f较大的数是：%.2f\n",a,b,a);
	}
	else{
		printf("%.2f与%.2f较大的数是：%.2f\n",a,b,b);
	}
	return 0;
}
