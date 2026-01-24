#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== MSVC 标准模式诊断 ===\n");
    
    // 测试 __STDC__ 宏
    #ifdef __STDC__
        printf("__STDC__ 已定义，值为: %d\n", __STDC__);
    #else
        printf("__STDC__ 未定义\n");
    #endif

    // 测试 __STDC_VERSION__ 宏
    #ifdef __STDC_VERSION__
        printf("__STDC_VERSION__ 已定义，值为: %ld\n", __STDC_VERSION__);
    #else
        printf("__STDC_VERSION__ 未定义\n");
    #endif

    // 测试特定于 MSVC 的 _MSVC_LANG 宏 (更能反映MSVC自身认可的标准)
    #ifdef _MSVC_LANG
        printf("_MSVC_LANG 值为: %ld\n", _MSVC_LANG);
        if (_MSVC_LANG >= 201710L) printf("(编译器自认为处于 C++17 或更高模式)\n");
    #endif

    system("pause");    // 输出："请按任意键继续. . ." 且需要按键确认 
    return 0;
}