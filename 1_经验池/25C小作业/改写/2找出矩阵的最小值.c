#include<stdio.h>
int main()
{
	int i,j,k=1,min,min_1,min_2,a[4][3];
	printf("请逐个输入数据: \n");
	for(i=0;i<4;i++)
		for(j=0;j<3;j++) 
			scanf("%d",&a[i][j]);
	min=a[0][0];
	min_1=0;
	min_2=0;
	for(i=0;i<4;i++)
		for(j=0;j<3;j++)
			if(min>=a[i][j])
			{min=a[i][j];min_1=i;min_2=j;}
	printf("该矩阵中的最小值为: %d，它在第 %d 行，第 %d 列",min,min_1+1,min_2+1);
	return 0;
}

