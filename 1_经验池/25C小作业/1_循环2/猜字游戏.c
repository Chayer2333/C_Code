#include <stdio.h>
#include <stdlib.h>
#include<time.h>
int main() 
{
    int i,n; 
    srand(time(0));
    int random = rand() % 1000 + 1;
    printf("Random (100-1000): %d\n",random);
    for(i=1;i<=5;i++)
    { 
        printf("随机输入一个数字:\n");
        scanf("%d",&n);
        if(n>random)
        printf("大了\n");
         else if(n<random)
        printf("小了\n");
         else if(n==random)
        {
        printf("获胜");
        break;
        }    
    }
        if(i==6)
        printf("失败\n");
    return 0;
}
