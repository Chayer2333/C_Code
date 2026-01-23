#include <stdio.h>
int main()
{
	int i,sum=0,n;
	scanf("%d",&n);
	for(i=1;i<=n;i++)//两个分号一个都不能少 
	{
		sum=sum+i;
	}//i=n+1
	printf("i=%d,sum=%d\n",i,sum);
	return 0;
}
