#include <stdio.h>
int main()
{
	float x,y;
	printf("请输入x的值:\n     \n    ");
	scanf("%f",&x);
	if(x<=0){
		if(x<=-10){
			y=2*x;
		} 
		else{
			y=2+x;
		}
	}
	else{
		if(x<=10){
			y=x-2;
		}
		else{
			y=x/10;
		}
	}
	printf("\ny的值为：%f",y);
	return 0;
}
