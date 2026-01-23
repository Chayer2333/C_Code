#include<stdio.h>
int main()
{
	double i,sum=0;
	printf("1+1/3+бн1/99:\n");
	for(i=1;i<=99;i+=2)
	{
		sum+=1/i;
	}
	printf("%.20f",sum);
	return 0;
}
