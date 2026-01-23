#include<stdio.h>
#include<string.h>
#define N 20
#define M 27

void replace(char *str ,char *a ,char *b);

int main()
{
	char a[M],b[M],c[N];
	printf("请输入要更改的字符集合：");
	scanf("%26s",a);
	printf("请输入替换后的字符集合：");
	scanf("%26s",b);
	if(strlen(a)!=strlen(b)) 
	{
    	printf("错误：替换字符集长度不匹配！\n");
        return 1;
    }
	printf("请输入要更改的字符串：");
	scanf("%19s",c);
	replace(c,a,b);
	printf("%s",c);
	return 0;
}



void replace(char *str ,char *a ,char *b)
{
	while(*str!='\0')
	{
		char *p=a,*q=b;
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
