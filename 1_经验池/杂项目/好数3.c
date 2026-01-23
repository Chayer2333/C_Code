#include<stdio.h>
int main()
{
	int sup,n1,n2,m,t=1,key,i,j=0;
	printf("«Î ‰»Î…œœﬁ£∫\n");
	scanf("%d",&sup);
	for(m=1;m<=sup;m++)
	{
		n1=m;n2=m/10;key=1;
		for(;n1>0;)
		{	
			if((n1%10)%2!=1)
				key=0;
			n1/=100;
		}
		for(;n2>0;)
		{	
			if((n2%10)%2!=0)
				key=0;
			n2/=100;
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
