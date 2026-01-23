#include<stdio.h>
int main()
{
	int inf,n,m,t=1,key,i,j=0;
	printf("«Î ‰»Î…œœﬁ£∫\n");
	scanf("%d",&inf);
	for(m=1;m<=inf;m++)
	{
		n=m;key=1;
		for(i=1;n>0;i++)
		{
			if((n%10)%2!=(i%2==1))
				key=0;
			n/=10;
		}
		if(key==1)
		{
			j++;
			printf("%d\t",m);
			if(t++%5==0)printf("\n");
		}
	}
	printf("\n%d",j);
	return 0;
}
