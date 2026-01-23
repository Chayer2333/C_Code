#include<stdio.h>
#include<string.h>
#define N 20

void delStr(char *str,char ch); 

int main()
{
	char a[N],b;
	printf("请输入待处理的字符串：\n");
	scanf("%19s",a);
	printf("请输入待删除的字符：");
    while(getchar()!='\n');				// 清除输入缓冲区中的换行符
	b=getchar();
	delStr(a,b);
	printf("\n：%s",a);
	return 0;
}



void delStr(char *p, char ch)
{
    char *src=p;  		// 源指针  （读取位置）
    char *dst=p;  		// 目标指针（写入位置）
	 
    while(*src)
	{
        if(*src!=ch)
		{
            *dst=*src;  // 保留非删除字符
            dst++;
        }
        src++;			//核心是跳过与目标相同的字符，提前复制下一个字符 
    }
    *dst='\0';  		// 添加字符串结束符
}

