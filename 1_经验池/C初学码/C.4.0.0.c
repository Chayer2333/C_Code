#include <stdio.h>
int main()
{
	int i=1,sum=0,n;
	scanf("%d",&n);
	while(i<=n)
	{
		sum=sum+i;
		i++;
	}//i=n
	printf("i=%d,sum=%d\n",i,sum);
	return 0;
}
