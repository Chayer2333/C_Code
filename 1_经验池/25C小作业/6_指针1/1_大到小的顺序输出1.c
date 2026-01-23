#include <stdio.h>
void swap(int *,int *);
void sort(int *);
int main() 
{
    int a[3];
    printf("请输入三个整数: ");
    scanf("%d %d %d",&a[0],&a[1],&a[2]);
    sort(a);
    printf("从大到小的排列为:\n");
	printf("%d\t%d\t%d\t",*a,*(a+1),*(a+2));
    return 0;
}


// 交换两个整数的值
void swap(int *a, int *b)
{
    int temp;
	temp=*a;
    *a=*b;
    *b=temp;
}
	
	
//排序 
void sort(int *q) 
{
	int *p;
    for(p=q;p<q+2;p++)  			// 指针遍历前两个元素
        if(*p<*(p+1)) 				// 需要交换时
			{           		
	            swap(p,p+1);
	            p=q-1;				// 重置指针重新扫描
	        }
}



/*
//排序 
void sort(int *q) 
{
	int *p;
    for(p=q;p<q+2;p++)  			// 指针遍历前两个元素
        if(*p>*(p+1)) 				// 需要交换时
			{           		
	            swap(p,q);
	            p=q-1;				// 重置指针重新扫描
	        }
}
为什么你的原代码有问题？
swap(p, q) 错误：

你想交换 *p 和 *(p+1)，但实际传入的是 p 和 q（即 p 和 arr 的首地址），导致错误交换。

修正：应该 swap(p, p + 1)。

指针重置 p = q - 1 导致无限循环：

每次交换后 p 被重置到 q - 1，但 for 循环又会 p++，导致重复比较。

修正：更高效的方式是直接进行 3 次比较，无需循环。
*/
