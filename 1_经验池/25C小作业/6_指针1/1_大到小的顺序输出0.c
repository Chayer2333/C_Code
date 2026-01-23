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
void sort(int *a)
{
    if (*a<*(a+1))	  swap(a,a+1);      // 比较前两个
    if (*a<*(a+2))	  swap(a,a+2);      // 比较第一个和第三个
    if (*(a+1)<*(a+2))swap(a+1,a+2);    // 比较后两个
}
