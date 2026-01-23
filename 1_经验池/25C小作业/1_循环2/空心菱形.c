#include<stdio.h>
int main()
{
	int i,j;
	for(i=1;i<=5;i++)
	{
		for(j=1;j<=5-i;j++)
		printf(" ");
		printf("*");
		if(i>=2)
		{
			for(j=1;j<=2*i-3;j++)
			printf(" "); 
			printf("*\n");	
		}
		else printf("\n");
	}
	for(i=1;i<=4;i++)
	{
		for(j=1;j<=i;j++)
		printf(" ");
		printf("*");
		if(i<=3)
		{
			for(j=1;j<=7-2*i;j++)
			printf(" ");
			printf("*\n");
		}
		else printf("\n");
	}
	return 0;
} 
