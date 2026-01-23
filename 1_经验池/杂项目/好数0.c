#include<stdio.h>
int main()
{
	int sup,n,m,t=1,key,i,j=0;
	printf("«Î ‰»Î…œœﬁ£∫\n");
	scanf("%d",&sup);
	for(m=1;m<=sup;m++)
	{
		n=m;key=1;
		for(i=1;n>0;i++)
		{	
			if(i%2==1)
			{
				if((n%10)%2!=1)
					key=0;
			}
			else
			{
				if((n%10)%2!=0)
					key=0;
			}
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
