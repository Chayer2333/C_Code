#include<stdio.h>
void fun(int n);

int main()
{
	fun(5);
	return 0;
 } 
 
void fun(int n)
{
	if(n==1)
	{
		printf("a:%d\n",n);
	} else {
		printf("b:%d\n",n);
		fun(n-1);
		printf("c:%d\n",n);
	}
}
