#include <stdio.h>
int factorsum(int num);

int main() 
{
	int i, j, sum, p=0, m, n;
	printf("请输入所选范围下限：");
	scanf("%d", &m);
	printf("请输入所选范围上限：");
	scanf("%d", &n);
	
	if(m<1 || n>1000 || m>n)
	{
		printf("输入范围越界！");
		return -1;
	} else {
		printf("区间[%d,%d]的完数为：\n",m,n);
	}
	
	for(i=m; i<=n; i++) 
	{
		sum=factorsum(i);
		if(sum==i)
		{
			printf("%d是完数\n", i);
			p++;
		}
	}
	if(p==0) printf("NULL"); 
	return 0;
}

int factorsum(int num)
{
	int i,sum=0;
		for(i=1; i<=num/2; i++)
		{
			if (num%i==0)
			{
				sum+=i;
			}
		}
	return sum;
}
