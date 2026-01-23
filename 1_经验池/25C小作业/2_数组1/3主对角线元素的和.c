#include<stdio.h>
int main()
{
	int i;
	float sum=0,a[3][3];
	printf("请按以下格式输入三次数据: \n");
	printf("格式为： %%f,%%f,%%f  \n");
	for(i=0;i<3;i++)
	scanf("%f,%f,%f",&a[i][0],&a[i][1],&a[i][2]);
	for(i=0;i<3;i++)
	sum+=a[i][i];
	printf("该矩阵主对角元素之和为: %f",sum);
	return 0;
}

