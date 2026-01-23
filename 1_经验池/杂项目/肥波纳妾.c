#include <stdio.h> 
int main( ) 
{ 
    long f1 = 1, f2 = 1; 
    int i; 
    for (i = 1; i <= 20; i++) 
    { 
        printf("%-12ld%-12ld", f1, f2); 
        if (i % 2 == 0) printf("\n");  // 每行输出4个数后换行
        f1 = f1 + f2;  // 计算下一个斐波那契数
        f2 = f2 + f1;  // 计算下一个斐波那契数
    } 
    return 0; 
}
