#include <stdio.h>
int main()
{
	int i,j;
	float f1,f2;
	char ch1,ch2;
	printf("请输入i,f1,ch1,ch2的值：\n");
	scanf("%d%f%c%c",&i,&f1,&ch1,&ch2);//如何定义输入则如何输入!
	                                   //对于%c回车，空格，Tab也是字符(不影响%d,%f) 
									   //坠哄的输入定义为(%d,%f,%c,%c) 
	j=i++;
	f2=++f1;
	printf("i=%d;j=%d\n",i,j);
	printf("f1=%3.3f;f2=%4.2lf\n",f1,f2);
	printf("ch1=%c;ch2=%c\n",ch1,ch2);
	return 0;
}
