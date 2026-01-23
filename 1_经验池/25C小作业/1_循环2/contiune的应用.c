#include<stdio.h>
int main()
{
	int i,j=1;
	for(i=50;i<=150;i++)
	{
		if(i%5==0)
		continue;
		printf("%d\t",i);
		if(j++%5==0)
		printf("\n");
	} 
	return 0;
} 
