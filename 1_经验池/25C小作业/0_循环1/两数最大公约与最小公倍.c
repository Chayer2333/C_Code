#include<stdio.h>
int main()
{
	int m1,m2,r=1,LCM;
	printf("请输入两个正整数 :\n");
	do
	{
		scanf("%d%d",&m1,&m2);
		if(m1>0&&m2>0)
		break;
		printf("输入数据有误请重新输入:\n");
	}while(m1<0||m2<0);
	LCM=m1*m2;
	if(m2>m1){r=m2;m2=m1;m1=r;};
	for(;r!=0;)
	{
		r=m1%m2;
		m1=m2;
		m2=r;
	}
	printf("最大公约数和最小公倍数分别为 :\n");
	printf("%d , %d",m1,LCM/m1);
	return 0;
} 
