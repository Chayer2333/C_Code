#include <stdio.h>
#define M 100

int main() 
{
	int m,i,j;
	printf("请输入数组个数:  ");
	scanf("%d",&m);
	float a[M],Transfer;
	printf("\n请逐个输入数据并用回车隔开:  \n");
	for(i=0;i<m;i++)
	{
		scanf("%f",&a[i]);
	}
	for(i=1;i<=m;i++)
	{
		for(j=0;j<m-i;j++)
		{
		    if(a[j]>a[j+1])
		    {
			    Transfer=a[j]   ;
		        a[j]=a[j+1]     ;
		        a[j+1]=Transfer ;
		    }
		}
	}
	for(i=0;i<m;i++)
	printf("%f\t",a[i]);
	return 0;
}
