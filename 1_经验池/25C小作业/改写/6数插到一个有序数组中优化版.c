#include<stdio.h>
int main()
{
	int i,t,n,m=0,key=0; 
	int a[11];
	printf("请输入十个有序元素： \n"); 
	for(i=0;i<10;i++)
	scanf("%d",&a[i]);
	printf("数组为: \n");	
	for(i=0;i<10;i++)
		printf("%d\t",a[i]);
	printf("\n请输入待插入的元素：\n");
	scanf("%d",&n);
	for(i=9;i>=0;i--)
	{
		if(n<a[i])
			a[i+1]=a[i];
		else
			{
				a[i+1]=n;
				break;
			}
	}
	printf("新的有序数组为: \n");	
	for(i=0;i<11;i++)
		printf("%d\t",a[i]);
	return 0; 
}
