#include <stdio.h>
int main() 
{
	int i,j;
	float a[8],Transfer;
	printf("请逐个输入数据并用回车隔开:  \n");
	for(i=0;i<8;i++)
	{
		scanf("%f",&a[i]);
	}
	for(i=1;i<=8;i++)
		for(j=0;j<8-i;j++)
		    if(a[j]>a[j+1])
		    {
			    Transfer=a[j]   ;
		        a[j]=a[j+1]     ;
		        a[j+1]=Transfer ;
		    }
	printf("这八个时候从小到大的排列为 :\n");
	for(i=0;i<8;i++)
	printf("%f\t",a[i]);
	return 0;
}

