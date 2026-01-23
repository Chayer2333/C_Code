#include<stdio.h>
int main()
{
	int k,n,m,key=1;
	scanf("%d",&n);
	m=n;
	for(;n>0;)
	{
		k=n%10;
		if(k%2==0)
			key=0;
		n/100;
	}
	m/10;
	for(;m>0;)		
	{
		k=m%10;
		if(k%2==1)
			key=0;
		m/100;
	}
	printf("%d",key);
	return 0;
 } 
