#include<stdio.h>
int main()
{
	int i,j,k=1,max,max1,max2;
	int a[3][4]={
		{3,2,2,1},
		{2,1,5,4},
		{1,1,5,8}
				}; 
	for(i=0;i<3;i++)
	{
		max=a[i][0];max1=i;max2=0;
		for(j=0;j<4;j++)
		{
			if(a[i][j]>=max)
			{max=a[i][j];max1=i;max2=j;}
		}
		a[max1][max2]=a[i][3];
		a[i][3]=max;
	}
	for(i=0;i<3;i++)
	for(j=0;j<4;j++)
	{
		printf("%5d",a[i][j]);
		if(k++%4==0)
		printf("\n");
	}
	return 0;
}
