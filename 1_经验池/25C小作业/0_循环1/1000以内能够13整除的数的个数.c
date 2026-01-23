#include<stdio.h>
int main()
{
	int i,j=0;
	printf("1000以内能够被13整除的数的个数为:\n");
	for(i=0;i<=1000;i++)
	{
		if(i%13==0)
		j++;
	}
	printf("%d",j);
	return 0;
}
