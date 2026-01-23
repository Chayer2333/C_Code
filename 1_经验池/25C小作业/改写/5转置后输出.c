#include<stdio.h>
int main()
{
	int i,j,k=1;
	int a[4][3],b[3][4];
	printf("请输入数据: \n");
	for(i=0;i<4;i++)
		for(j=0;j<3;j++) 
			scanf("%d",&a[i][j]);
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

