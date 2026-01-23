#include<stdio.h>
int main()
{
	long int n,i,a[40];
	printf("请输入的项数:\n");
	scanf("%d",&n);
	a[0]=a[1]=1;
	for(i=1;i<=n;i++)
	{
		printf("%d \t, ",a[i]);
		a[i+1]=a[i]+a[i-1];
		if(i%5==0)
		printf("\n");
	}
	return 0;
}
