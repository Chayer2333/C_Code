#include <stdio.h>
int factorsum(int num);
int Prime(int num);
int getPrimes(int primes[], int max);
int Pcount, primes[170];// 质数数组及个数 

int main() 
{
	int i, j, m, n, sum, count=0;
	printf("请输入求解区间：");
	scanf("%d %d", &m, &n);
	
	if(m<1 || n>1000 || m>n)
	{
		printf("输入范围越界！");
		return -1;
	} else {
		printf("\n区间[%d,%d]的完数为：\n\n",m,n);
	}
	
	Pcount=getPrimes(primes,n);
	// 查找完数 
	for(i=m; i<=n; i++) 
	{
		sum=factorsum(i);
		if(sum==i)
		{
			printf("%d\t是完数\n", i);
			count++;
		}
	}
	if(count==0) printf("NULL\n"); 
	
	return 0;
}

int Prime(int num)
{// 质数判断 
	int i;
	if(num==2) return 1;
    if(num<2 || num%2==0) return 0;
    for(i=3; i*i<=num; i+=2)
        if(num%i==0) return 0;
    return 1;
}

int getPrimes(int primes[], int max)
{// 计算范围内的质数 
	int i,count=0,q=1;
	for(i=2; i<=max; i++)
        if(Prime(i))
            primes[count++]=i;
	return count;
}

int factorsum(int num)
{// 计算因子和 
	if(num==1) return 0;
    int i, sum=1;
    int temp=num;
    
    // 质因数分解
    for(i=0; i<Pcount && primes[i]*primes[i]<=num; i++)
        if(temp%primes[i]==0)
		{
            int FactorSum=1;
            int power=1;
            
            // 计算质因数的所有幂次
            while(temp%primes[i]==0)
			{
                power*=primes[i];
                FactorSum+=power;
                temp/=primes[i];
            }
            sum*=FactorSum;
        }
    // 处理剩余的质因数
    if(temp>1)
        sum*=(1+temp);
        
    return sum-num;
}
