#include<stdio.h>
int main()
{
	int i,j,k=1,min,min1,min2,a[4][3];
	printf("请按以下格式输入四次数据: \n");
	printf("格式为： %%d,%%d,%%d  \n");
	for(i=0;i<4;i++)
	scanf("%d,%d,%d",&a[i][0],&a[i][1],&a[i][2]);
	min=a[0][0];min1=0;min2=0;
	for(i=0;i<4;i++)
		for(j=0;j<3;j++)
			if(min>=a[i][j])
			{min=a[i][j];min1=i;min2=j;}
	printf("该矩阵中的最小值为: %d，它在第 %d 行，第 %d 列",min,min1+1,min2+1);
	return 0;
}

