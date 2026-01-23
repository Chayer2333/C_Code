#include<stdio.h>
int Fibonacci(int); 
int main()
{
	int i,Ent=1;
	printf("斐波那契前二十项为：\n");
	for(i=1;i<=20;i++)
	{
		printf("%d\t",Fibonacci(i));
		if(Ent%5==0)
			printf("\n");
		Ent++;
	}
	return 0;
}

int Fibonacci(int n)
{
	if(n==1||n==2)
		return 1;
	else
		return  Fibonacci(n-1)+Fibonacci(n-2);
}
