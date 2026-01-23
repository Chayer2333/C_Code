#include<stdio.h>
int main()
{
	int i,n;
	float a[3],avg;
	printf("要输入的学生个数为: \n");
	scanf("%d",&n);
	printf("请分别输入三门成绩 :\n");
	for(i=1;i<=n;i++)
	{
		scanf("%f%f%f",&a[0],&a[1],&a[2]);
		if(a[0]<0||a[0]>150||a[1]<0||a[1]>150||a[2]<0||a[2]>150)
		{
			printf("输入数据有误请重新输入:\n");
			i--;
			continue;
		}
		avg=(a[0]+a[1]+a[2])/3;
		printf("平均分为: %.1f\n",avg);
		if(i==n)break;
		printf("请输入上一个学生的成绩 : \n");
	}
	return 0;
} 
