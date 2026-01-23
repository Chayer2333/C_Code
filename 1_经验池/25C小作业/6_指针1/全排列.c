#include <stdio.h>
void swap(int *a,int *b);
void permute(int *array,int start,int end);

int main() 
{
    int numbers[3];
    printf("请输入三个整数: ");
    scanf("%d %d %d",&numbers[0],&numbers[1],&numbers[2]);
    printf("所有可能的排列:\n");
    permute(numbers,0,2);
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
	
	
//递归函数生成排列
void permute(int *array,int start,int end)
{
	int i;
    if(start==end) 
	{
        //当到达最后一个元素时,打印当前排列
        printf("%d %d %d\n",array[0],array[1],array[2]);
    } else 
	{
        for(i=start;i<=end;i++)
		{
            // 交换当前元素与起始元素
            swap(&array[start],&array[i]);
            
            // 递归生成剩余元素的排列
            permute(array,start+1,end);
            
            // 恢复原始顺序（回溯）
            swap(&array[start],&array[i]);
        }
    }
}
