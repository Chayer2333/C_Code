#include<stdio.h>
int main()
{
	int n;
	float sum=0;
	for(n=1;n<=240;n++)
	sum=(sum+100)*(1.0025);
	printf("%.2f",sum);
	return 0;
} 
