#include<stdio.h>
int main()
{
    int i,j,n;
    char a;
    printf("请输入行数: ");
    if(scanf("%d", &n) != 1 || n<1 || n>26) {
        printf("请输入 1 到 26 之间的整数\n");
        return -1;
    }
printf("\n");//%%%%%%%%%%%%%%%%%%%%%% 标准 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    for(i=1; i<=n; i++) {  
        for(j=0; j<=n-1-i; j++)
            printf(" ");
        for(a='A'; a<'A'+i; a++)
            putchar(a);
        for(a=a-2; a>='A'; --a)
            putchar(a);
        printf("\n");
    }
printf("\n");//%%%%%%%%%%%%%%%%%% 只用俩个环循 %%%%%%%%%%%%%%%%%%%%%%%%%%% 推荐
    for(i=1; i <= n; i++) {
        printf("%*s", n-i, "");          // 一次性打印 n-i 个空格 算是一个循环
        for(j=0; j<2*i-1; j++)
            putchar('A'+( j<i ?j : 2*i-2-j));
        putchar('\n');
    }
printf("\n");//%%%%%%%%%%%%%%%%%% 只用一个环循 %%%%%%%%%%%%%%%%%%%%%%%%%%%
    for(i=1; i<=n; i++) {
        for (j=0; j < n+i-1; j++) {
            int d = j-(n-i);           // 相对字母区的下标
            if (d<0)
                putchar(' ');
            else
                putchar('A'+( d<i ?d : 2*i-2-d ));
        }
        putchar('\n');
    }
    return 0;
}