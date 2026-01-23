#include<stdio.h>
int main()
{
	int i,sum;
	printf("3+6+……+99 的结果为:\n");
	for(i=3;i<=99;i+=3)
		sum+=i;
	printf("%d",sum); 
	return 0;
}
