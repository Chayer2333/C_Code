#include <stdio.h>
int main()
{
	float a,b;
	int i,j;
	char ch1,ch2,ch3;
	printf("请按格式输入数字a,b,i,j\n");
	scanf("%f,%f,%d,%d",&a,&b,&i,&j);
	fflush(stdin);//清屏
	printf("请按格式输入字符ch1,ch2\n");
	ch1=getchar(); 
	ch3=getchar();//字符不是字符串		// 注意！该代码在C89/C90标准与MSVC编译的程序执行方式不同，后者不适用提示的输入规则！
    ch2=getchar();
	printf("a=%.2f,b=%.3f\n",a,b);
	printf("i=%d,j=%d\n",i,j);
	putchar('c');
	putchar('h');
	putchar('1');
	putchar('=');
	putchar(ch1);
	putchar(';');
	putchar('c');
	putchar('h');
	putchar('2');
	putchar('=');
	putchar(ch2);
	putchar('\n');
	return 0;
}
