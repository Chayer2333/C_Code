#include<stdio.h>
void leap_year(int); 
int main()
{
	int n;
	printf("请输入待判断的年份：\n");
	scanf("%d",&n);
	leap_year(n);
	return 0;
}

void leap_year(int year)
{
	if(year%4==0&&year%100!=0||year%400==0)
		printf("该年是闰年\n");
	else
		printf("该年不是闰年\n"); 
}
