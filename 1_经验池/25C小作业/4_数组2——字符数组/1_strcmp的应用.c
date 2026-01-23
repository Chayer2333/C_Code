#include<stdio.h>
#include<string.h> 
void strswap(char*, char*);
void sort(char[][20],int);
int main()
{
    int i;char str[10][20];
    printf("请重复输入十个不大于二十字的字符串: \n");
    for(i=0;i<10;i++)
		scanf("%19s",str[i]);
	sort(str,10);
	printf("按字典序升序排列后为：\n");
	for(i=0;i<10;i++)
		printf("%s\n",str[i]);
	return 0;
}


void strswap(char *a,char *b) 
{
    char temp[20];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}


void sort(char a[][20],int n)
{
	int i,j,k;
	for(i=0;i<n-1;i++)
	{
		k=i;
		for(j=i+1;j<n;j++)
			if(strcmp(a[j],a[k])<0)
				k=j;
		strswap(a[k],a[i]);
	}
}

/*
如果允许输入空格，可以改用 fgets：

fgets(str[i], 20, stdin);
str[i][strcspn(str[i], "\n")] = '\0';  //移除末尾的换行符

strcspn 检索字符串 str1 开头连续有几个字符都不含字符串 str2 中的字符。

*/
