#include<stdio.h>
int main()
{
	int t=0; 
	while(printf("*"))
	{t++;if(t>3)break;};
	printf("%d",t);
	return 0;
} 
