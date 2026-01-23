#include <stdio.h>
int main()
{
	int m,a,b,c,n;
	scanf("%d",&m);
	a=m/100;
	b=m/10%10;
	c=m%10;
	n=c*100+b*10+a;
	printf("%d",n);
	return 0;
}
