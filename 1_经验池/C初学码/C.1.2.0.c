#include <stdio.h>
int main()//这里的int是 return 0 的 
{

int a,b,c;// 这里的int是仅与a,b,c有关的 
a=10;     //值为10 
b=012;    //值为1*8^1+2*8^0 
c=0xa;    //值为10*16^0 
          //int a=10 也可以
          
printf("a=%d,  b=%d,   c=%d\n",a,b,c);//%d以十进制输出 
printf("a=%o,  b=%o,   c=%o\n",a,b,c);//%o以八进制输出 
printf("a=%x,  b=%x,   c=%x\n",a,b,c);//%x以十六进制输出 

return 0;

}
