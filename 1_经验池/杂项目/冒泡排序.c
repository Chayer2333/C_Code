#include <stdio.h>
#define M 100

int main() 
{
	int m,i,key=0;
	printf("请输入数组个数:  ");
	scanf("%d",&m);
	float a[M],Transfer;
	printf("\n请逐个输入数据并用回车隔开:  \n");
	for(i=0;i<m;i++)
	{
		scanf("%f",&a[i]);
	}
	for(;key==0;)
	{
	key=1;
		for(i=0;i<m-1;i++)
		{
		    if(a[i]>a[i+1])
		    {
			    Transfer=a[i];
		        a[i]=a[i+1];
		        a[i+1]=Transfer;
		    }
		}
		for(i=0;i<m-1;i++)
		{
			key*=(a[i]<=a[i+1]);
		}
	}
	for(i=0;i<m;i++)
	{
		printf("%f\t",a[i]);
	}
	return 0;
}
