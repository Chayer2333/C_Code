#include<stdio.h>
int main()
{
	int i,j,m=1;
	for(i=100;i<=1000;i++)
	{
		for(j=2;j*j<=i;j++)
		{
			if(i%j==0)
			break;
		}
		if(j*j>i)
		{
			printf("%d\t",i);
			if(m++%5==0)
				printf("\n");
		}
	} 
	return 0;
} 
