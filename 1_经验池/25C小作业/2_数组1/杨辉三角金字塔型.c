#include<stdio.h>
int main()
{
	int i,j,a[12][12];
	for(i=0;i<12;i++)
	a[i][0]=a[i][i]=1;
	for(i=0;i<11;i++)
	{
		for(j=1;j<=i;j++)
		{
			a[i+1][j]=a[i][j-1]+a[i][j];
		}
	}
	for(i=0;i<12;i++)
	{
		for(j=0;j<=(12-i)/2;j++)
			printf("      ");
		if((12-i)%2==1)
			printf("   ");
		for(j=0;j<=i;j++)
		{
			printf("%6d",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
