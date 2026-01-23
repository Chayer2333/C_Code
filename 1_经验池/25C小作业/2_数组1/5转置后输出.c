#include<stdio.h>
int main()
{
	int i,j,k=1,a[4][3],b[3][4];
	printf("请按以下格式输入四次数据: \n");
	printf("格式为： %%d,%%d,%%d  \n");
	for(i=0;i<4;i++)
	scanf("%d,%d,%d",&a[i][0],&a[i][1],&a[i][2]);
	for(i=0;i<4;i++)
		for(j=0;j<3;j++)
			b[j][i]=a[i][j];
	printf("该矩阵的转置为：\n");
	for(i=0;i<3;i++)
		for(j=0;j<4;j++)
			{
				printf("%d,",b[i][j]);
				if(k++%4==0)
					printf("\n");
			}
	return 0;
}

