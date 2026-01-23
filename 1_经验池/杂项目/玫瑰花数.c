#include<stdio.h>

void rose(int n){
	//玫瑰花数：四位数满足 dcba=a*a*a*a + b*b*b*b + c*c*c*c + d*d*d*d
	int a,b,c,d = 0;
 
	a = n % 10;		//个位
	b = n / 10 % 10;	//十位
	c = n / 100 % 10;	//百位
	d = n / 1000;	//千位
 
	if(n == a*a*a*a + b*b*b*b + c*c*c*c + d*d*d*d)
		printf("%d\t",n);
}
 
int main(){
	int i = 0;
	for(i = 1000;i < 10000;i++){
		rose(i);
	}
 
	return 0;
}

