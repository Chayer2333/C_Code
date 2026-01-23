#include<stdio.h>
int main()
{
	int n_0=0,n_1=0,n_2=0,n_3=0;
	char c;
	printf("输入一行字符,以回车终止 :\n");
	for(;(c=getchar())!='\n';)
	{
		if(c<='z'&&c>='a'||c<='Z'&&c>='A')
		n_0++;
		else if(c==' ')
		n_1++;
		else if(c<='9'&&c>='0')
		n_2++;
		else
		n_3++;
	}
	printf("英文字母、空格、数字和其他字符的个数分别为：\n");
	printf("%d  %d  %d  %d",n_0,n_1,n_2,n_3);
	return 0;
}
