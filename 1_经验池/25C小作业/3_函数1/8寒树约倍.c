#include<stdio.h>
int GCD(int,int);
int LCM(int,int); 
int main()
{
	int m1,m2;
	printf("请输入计算的两数：\n");
	scanf("%d%d",&m1,&m2);
	printf("最大公约数与最小公倍数分别为 :\n");
	printf(" %d , %d ",GCD(m1,m2),LCM(m1,m2));
	return 0;
}

int GCD(int m1,int m2)
{
	int r=1;
	if(m2>m1){r=m2;m2=m1;m1=r;};
	for(;r!=0;)
	{
		r=m1%m2;
		m1=m2;
		m2=r;
	}
	return m1;
}

int LCM(int m1,int m2)
{
	return m1*m2/GCD(m1,m2);
}
