#include <stdio.h>
int main()
{
	int m,a,b,c;
	scanf("%d",&m);
	a=m/100;
	b=m/10%10;
	c=m%10;
	printf("%d%d%d",c,b,a);
	return 0;
}
