#include <stdio.h>

int main() {
    int n = 0;  // 用于统计数字字符的个数
    char c;     // 存储当前读取的字符

    printf("请输入一串字符（按回车结束）：\n");
    c = getchar();  // 读取第一个字符

    while (c != '\n') {  // 当读取的字符不是换行符时继续循环
        if (c >= '0' && c <= '9') {  // 判断是否是数字字符
            n++;  // 如果是数字字符，计数器加1
        }
        c = getchar();  // 读取下一个字符
    }

    printf("数字字符的个数是：%d\n", n);
    return 0;
}
