#include<stdio.h>
int main()
{
	int i,t,b,m=0,key=0,a[11];
	printf("请逐个输入十个有序元素： \n"); 
	for(i=0;i<10;i++)
	scanf("%d",&a[i]);
	for(;key==0;)
	{
	key=1;
		for(i=0;i<9;i++)
			key*=(a[i]<=a[i+1]);
		for(i=0;i<9;i++)
		    if(a[i]>a[i+1])
		    {t=a[i];a[i]=a[i+1];a[i+1]=t;m++;}
	}
	if(m)
		printf("你个坏人不老实！！！\n");
	printf("十个元素构成的有序数组为: \n");	
	for(i=0;i<10;i++)
		printf("%d\t",a[i]);
	printf("\n请输入待插入的元素：\n");
	scanf("%d",&b);
	for(i=0;i<9;i++)
	{
		if(a[i]>b)
		{
			m=i;
			for(i=11;i>m;i--)
			a[i]=a[i-1];
			a[m]=b;
			break;
		}
		else
			a[10]=b;
	}
	printf("十一个元素构成的有序数组为: \n");	
	for(i=0;i<11;i++)
		printf("%d\t",a[i]);
	return 0; 
}
