#include<stdio.h>
int main()
{
	int a[10],i,t,tmp;
	printf("请输入十个整数：\n");
	for(i=0;i<10;i++)
		scanf("%d",&a[i]);
	for(i=0;i<9;i++)
	{
		t=0;
		if(a[i]<a[t])
			t=i;
	}
	printf("最小元素为：%d,是第%d个\n",a[t],t);
	{tmp=a[0];a[0]=a[t];a[t]=tmp;};
	for(i=0;i<10;i++)
		printf("%d\t",a[i]);
	return 0; 
}
