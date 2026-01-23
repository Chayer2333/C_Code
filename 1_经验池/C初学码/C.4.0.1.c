#include <stdio.h>
int main()
{
	int i=1,sum=0,n;
	scanf("%d",&n);
	do
	{
		sum=sum+i;
		i++;
	}while(i<=n);//i=n+1
	printf("i=%d,sum=%d\n",i,sum);
	return 0;
}
