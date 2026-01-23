#include <stdio.h>		// new 是cpp的关键字 

typedef int ElemType;

int main()
{
	int i,n;
	printf("请输入数组长度:");
	scanf("%d",&n);
	printf("\n");
	///////////////////////////////////////////////////
	ElemType *a = new ElemType[n];		// 建立动态数组
	///////////////////////////////////////////////////
	for(i=0;i<n;i++) {
		a[i]=i;
		printf("%d\t\v",a[i]);
	}
	
	printf("\n请输入数组长度:");
	scanf("%d",&n);
	
	for(i;i<n;i++) {
		a[i]=i;
		printf("%d\t\v",a[i]);
	}
	///////////////////////////////////////////////////
	delete[] a; 						// 释放数组
	///////////////////////////////////////////////////
} 

