#include<stdio.h>
int main()
{
	int mum,a,b,c;
	printf("水仙花数为: \n");
	for(mum=100;mum<=999;mum++)
	{
		a=mum/100;
		b=mum/10%10;
		c=mum%10;
		if(mum==a*a*a+b*b*b+c*c*c)
		printf("%d\t",mum);
	}
	return 0;
} 
