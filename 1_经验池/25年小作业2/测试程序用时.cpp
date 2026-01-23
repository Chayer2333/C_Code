#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 100000

void Sort(int *a,long int m);

int main() 
{
	int a[M];
	long i;
	clock_t StartTime,EndTime;
	double time;
	
	for(i=0;i<M;i++)
		a[i]=rand();
	
	StartTime=clock();
	
	Sort(a,M);

	EndTime=clock();
	time=(double)(EndTime-StartTime)/CLOCKS_PER_SEC;
	
	for(i=0;i<M-1;i++)
		printf("%d\t",a[i]); 
		
	printf("\n\nÖ´ÐÐÊ±¼ä£º%f Ãë\n",time);
	return 0;
}

void Sort(int *a,long int m)
{
	long int i,j;
	int ts;
	for(i=1;i<=m;i++)
		for(j=0;j<m-i;j++)
		    if(a[j]>a[j+1])
		    {	ts=a[j];a[j]=a[j+1];a[j+1]=ts;	};
}
