#include<stdio.h>
#define N 8 
void Bule_Sort(float *);

int main()
{
	int i;
	float a[N];
	printf("请输入待排序的八个树: \n");
	for(i=0;i<N;i++)
		scanf("%f",a+i);
	Bule_Sort(a);
	return 0;
}



void Bule_Sort(float *p)
{
	int i,j;
	float Transfer;
	for(i=1;i<=N;i++)
		for(j=0;j<N-i;j++)
		    if(p[j]>p[j+1])
		    {
			    Transfer=p[j]   ;
		        p[j]=p[j+1]     ;
		        p[j+1]=Transfer ;
		    }
	printf("这八个树从小到大的排列为 :\n");
	for(i=0;i<N;i++)
	printf("%.3f\t",*(p+i));
}
