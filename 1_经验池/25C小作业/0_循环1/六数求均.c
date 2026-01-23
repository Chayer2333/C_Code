#include<stdio.h>
int main()
{
	int i;
	float n,sum=0;
	printf("请键入六个数并依次用回车隔开 :\n");
	for(i=0;i<6;i++)
	{
		scanf("%f",&n);
		sum+=n;
	}
	sum/=6;
	printf("这六个数的平均值为：%f",sum);
	return 0;
}
