#include<stdio.h>
int main()
{
	int i,r=-1;
	double sum;
	for(i=1;i<=100;i++)
	{
		r*=-1;
		sum+=1.0/i;
	}
	printf("%lf",sum);
	return 0;
} 
