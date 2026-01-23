#include<stdio.h>
int main()
{
	int i;
	printf("1000以内能够被3整除但是不能被7整除的数:\n");
	for(i=0;i<=999;i+=3)
	{
		if(i%7!=0)
		printf("%d\t",i);
	}
	return 0;
}
