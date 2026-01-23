#include<stdio.h>
#define N 3
void Trs(int (*p)[N]);

int main()
{
	int i,j,a[N][N];
	printf("请输入矩阵的元素：");
	for(i=0;i<N;i++)
	{
		printf("\n正在输入第 %d 行的元素:\n",i+1);
		for(j=0;j<N;j++)
			scanf("%d",&a[i][j]); 
	}
	Trs(a);
	printf("\n转置后的矩阵：\n");
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			{
				printf("%d,",a[i][j]);
				if((j+1)%N==0)
					printf("\n");
			}
	return 0;
}



void Trs(int (*p)[N])
{
	int i,j,tr;
	for(i=0;i<N;i++)
		for(j=i+1;j<N;j++)
			{tr=p[i][j];p[i][j]=p[j][i];p[j][i]=tr;};
}
