#include<stdio.h>
#include<string.h>
#define N 20

int Compare(char *str1, char *str2);

int main()
{
	char a[N],b[N];
	printf("请输入要比较的两字符串：\n");
	scanf("%19s %19s",a,b);
	printf("两字符串是否相同：%d",Compare(a,b));
	return 0;
}



int Compare(char *p, char *q)
{
	int i=0;
	while(*(p+i)!='\0')
	{
		if(*(p+i)!=*(q+i)) return 0;
		i++;
	}
	return 1;
}

