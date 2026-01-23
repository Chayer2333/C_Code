#include<stdio.h>
int main()
{
	int i,j;
	float sum=0,a[3][3];
	printf("请输入数据: \n");
	for(i=0;i<3;i++)
		for(j=0;j<3;j++) 
			scanf("%f",&a[i][j]);
	for(i=0;i<3;i++)
	sum+=a[i][i];
	printf("该矩阵主对角元素之和为: %f",sum);
	return 0;
}

