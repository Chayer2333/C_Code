#include<stdio.h>
void Rose(int);
int Exponent4(int);
int main()
{
	int n;
	printf("请输入待判断的四位数：\n");
	scanf("%d",&n);
	Rose(n);
	return 0;
}

void Rose(int n)
{
	int i,m=n,sum=0;
	for(i=0;i<4;i++)
	{
		sum+=Exponent4(n%10);
		n/=10;
	}
	if(m==sum)
		printf("yes\n");
	else
		printf("no\n"); 
}

int Exponent4(int n)
{
	return n*n*n*n;
}
