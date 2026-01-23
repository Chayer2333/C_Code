#include <stdio.h>
int main()
{
	int i,j,m,n;
	i=5;j=15;
	printf("\ni=%d \n",i);               //代码运行是从上行到下行的，这里i不变 
	m=i++;  //== m=i,i+1                 //先运算再自加1，并储存 
	printf("m=0%d, i=0%d, m=i++ \n",m,i);//11%d与%d11情况相同，与%11d不同
	printf("\nj=%d \n",j); 
	n=++j;  //== j+1,n=j                 //先自加1并储存，再运算
	printf("n=%d, j=%d, n=++j \n\n",n,j);
	printf("i=0%d, j=%d, m=%d, n=%d \n",i,j,m,n);
}
