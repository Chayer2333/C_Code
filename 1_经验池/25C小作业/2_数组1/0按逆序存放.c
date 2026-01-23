#include<stdio.h>
int main()
{
	int i,a[8];
	printf("ÇëÖð¸öÊäÈëÔªËØ£º\n");
	for(i=7;i>=0;i--)
	scanf("%d",&a[i]);
	for(i=0;i<8;i++)
	printf("%4d",a[i]);
	return 0;
}

