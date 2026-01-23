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



void delStr(char *p,char ch)
{
	int i,j;
	for(i=0;*(p+i)!='\0';i++)
		if(*(p+i)==ch)
			for(j=i;*(p+j)!='\0';j++)
				*(p+j)=*(p+j+1);
}

