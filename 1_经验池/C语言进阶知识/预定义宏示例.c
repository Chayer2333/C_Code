#include <stdio.h>
 
/* 
 * 预定义宏演示程序
 * 展示ANSI C标准中常用的预定义宏及其用途
 */
int main() {
    // 打印当前源文件名（字符串常量）
    printf("当前文件: %s\n", __FILE__);
    
    // 打印编译日期（"MMM DD YYYY"格式）
    printf("编译日期: %s\n", __DATE__);
    
    // 打印编译时间（"HH:MM:SS"格式）
    printf("编译时间: %s\n", __TIME__);
    
    // 打印当前行号（十进制整数）
    printf("当前行号: %d\n", __LINE__);
        
    // 检查是否符合ANSI/ISO标准（1表示符合）
    What_Standard();
        
    // 实用示例：调试信息输出
    printf("\n[调试信息] %s (第%d行) 编译于 %s %s\n", 
            __FILE__, __LINE__, __DATE__, __TIME__);
    
    printf("是否结束？");
    getchar();
    
    return 0;
}


int What_Standard() {
#ifdef __STDC__
    printf("此编译器支持ANSI C标准。\n");
    printf("__STDC__ 被定义为：%d\n", __STDC__);
#ifdef __STDC_VERSION__
    printf("C语言标准版本：%ld\n", __STDC_VERSION__);
#if __STDC_VERSION__ >= 201710L
    printf("支持C17或更高版本。\n");
#elif __STDC_VERSION__ >= 201112L
    printf("支持C11标准。\n");
#elif __STDC_VERSION__ >= 199901L
    printf("支持C99标准。\n");
#else
    printf("支持C89/C90标准。\n");
#endif
#else
    printf("支持C89/C90标准。\n");
#endif
#else
    printf("此编译器可能不完全支持ANSI C标准。\n");
#endif
    return 0;
}