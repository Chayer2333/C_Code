#include<stdio.h>
#include<string.h>
#define N 20
#define M 27

void replace(char *str ,char *old_chars ,char *new_chars);
void replace_optimized(char *str, char *old_chars, char *new_chars);
void replace_case_insensitive(char *str, char *old_chars, char *new_chars);
int replace_debug(char *old_chars, char *new_chars);

int main()
{
	char a[M],b[M],c[N];
	printf("请输入要更改的字符集合：");
	scanf("%26s",a);
	printf("请输入替换后的字符集合：");
	scanf("%26s",b);
	if(!replace_debug(a,b))
	{
        return 1;  			// 如果长度不匹配，提前退出
    }
	printf("请输入要更改的字符串：");
	scanf("%19s",c);
	replace(c,a,b);
	printf("%s",c);
	return 0;
}



void replace(char *str ,char *old_chars ,char *new_chars)
{
	if(str==NULL) return;
	while(*str!='\0')
	{
		char *p=old_chars,*q=new_chars;
        while(*p!='\0') 
		{
            if(*str==*p) 
			{
                *str=*q;
                break;
            }
            p++;q++;
        }
    str++;
	}
}


//使用查找表方法:
void replace_optimized(char *str, char *old_chars, char *new_chars)
{
	if(str==NULL) return;
	int i;
    char lookup[256]={0};			// 创建查找表（ASCII 256个字符）
    for(i=0;i<256;i++)     			// 初始化查找表
	{
        lookup[i]=i;  				// 默认不替换
    }
    char *p=old_chars,*q=new_chars;	// 设置替换映射
    while (*p!='\0')
	{
        lookup[(unsigned char)*p]=*q;
        p++;q++;
    }
    while (*str!='\0')				// 执行替换
	{
        *str=lookup[(unsigned char)*str];
        str++;
    }
}


//大小写不敏感替换：
void replace_case_insensitive(char *str, char *old_chars, char *new_chars)
{
	if(str==NULL) return;
    while(*str!='\0')
	{
        char *p=old_chars,*q=new_chars;
        int replaced=0;
        while (*p!='\0')
		{
        	if 	(*str==*p|| 
            	(*str>='A'&&*str<='Z'&&*str+32==*p)||
                (*str>='a'&&*str<='z'&&*str-32==*p))	// 检查小写和大写形式
			{
                *str=*q;
                replaced=1;
                break;
            }
            p++;q++;
        }
        str++;
    }
}



int replace_debug(char *old_chars, char *new_chars)
{
    if(strlen(old_chars) != strlen(new_chars))				// 检查长度是否匹配
    {
        printf("错误：替换字符集长度不匹配！\n");
        printf("原字符集长度: %zu\n", strlen(old_chars));
        printf("新字符集长度: %zu\n", strlen(new_chars));
        return 0;  											// 返回失败状态
    }
    printf("开始替换...\n");
    printf("替换映射:\n");
    char *p=old_chars,*q=new_chars;
    while(*p)
	{
        printf("  %c->%c\n",*(p++),*(q++));
    }
    printf("\n");
    return 1;  												// 返回成功状态
}



/*
(unsigned char)*p 详解
在 C 语言中，表达式 (unsigned char)*p 包含两个关键部分，理解它需要分析类型转换和指针解引用：

组成部分解析
*p:

解引用指针 p，获取它指向的值

类型取决于 p 的声明（通常是 char）

(unsigned char):

类型转换操作符

将右侧的值转换为 unsigned char 类型

为什么需要这种转换？

1. 解决符号问题
当处理可能为负值的字符时：

c
char c = '\xFF'; // 在 signed char 中这是 -1
unsigned char uc = (unsigned char)c; // 转换为 255

2. 确保有效的数组索引
c
char lookup[256]; // 索引范围 0-255

// 错误：当 *p 为负时会导致越界访问
lookup[*p] = ...; 

// 正确：确保索引在 0-255 范围内
lookup[(unsigned char)*p] = ...;

3. 位操作安全
c
// 避免符号扩展问题
char c = '\x80'; // -128 (signed) 或 128 (unsigned)
int a = c;       // 可能为 -128 (符号扩展)
int b = (unsigned char)c; // 总是 128
内存表示对比
     值	   二进制表示	signed char	unsigned char
	0xFF	11111111      -1          	255
	0x80	10000000	 -128        	128
	0x7F	01111111      127	        127
实际应用场景
在查找表优化中
c
void replace_optimized(char *str, char *a, char *b) {
    char lookup[256] = {0};
    
    // 创建映射表
    char *p = a, *q = b;
    while (*p) {
        lookup[(unsigned char)*p] = *q; // 安全转换
        p++;
        q++;
    }
    
    // 执行替换
    while (*str) {
        *str = lookup[(unsigned char)*str]; // 安全访问
        str++;
    }
}
在字符分类函数中
c
int is_alpha(char c) {
    // 避免负值问题
    unsigned char uc = (unsigned char)c;
    return (uc >= 'A' && uc <= 'Z') || (uc >= 'a' && uc <= 'z');
}
在哈希函数中
c
unsigned int hash(char *str) {
    unsigned int h = 0;
    while (*str) {
        h = h * 31 + (unsigned char)*str; // 确保正值
        str++;
    }
    return h;
}
为什么使用 unsigned char 而不是 int？
内存效率：

unsigned char 只占 1 字节

int 通常占 4 字节

明确意图：

清楚地表明我们处理的是字节数据

避免意外的整数提升

范围保证：

unsigned char 总是 0-255

int 的值范围更大，可能包含无效值

关键注意事项
ASCII 扩展字符：

许多扩展 ASCII 字符（128-255）在 signed char 中是负数

转换为 unsigned char 确保正确处理这些字符

平台无关性：

c
// 依赖平台的行为（char 可能有符号或无符号）
int index = *p; 

// 平台无关的解决方案
int safe_index = (unsigned char)*p;
C 标准保证：

C 标准规定 unsigned char 没有陷阱表示

可以安全地表示内存中的所有字节模式

总结
(unsigned char)*p 是一种确保安全处理原始字节数据的强大技术。它解决了以下关键问题：

正确处理负值字符

避免数组越界访问

确保位操作的可预测性

创建平台无关的代码

安全处理扩展 ASCII 字符集

在需要精确处理字节值（如字符串处理、加密算法、网络协议等）的场景中，这种转换是必不可少的最佳实践。
*/
