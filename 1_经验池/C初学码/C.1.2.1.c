#include <stdio.h>
int main()//这里的int是 return 0 的 
{

int a,b,c;// 这里的int是仅与a,b,c有关的 
a=10;
b=012;
c=0xa;
//int a=10 也可以                       //单反斜杠会让后面所有字符都成输出内容，\加空个就不行 
printf("a=%d, b=%d, c=%d\n\
a=%o, b=%o, c=%o\n\
a= %x, b= %x, c= %x",a,b,c,a,b,c,a,b,c);//(给了几个% 就给几个变量） 

return 0;

}
