#include<stdio.h>
void strcat(char*,char*);

int main()
{
	char a[11]={"asdfg"};
	char b[]={"zxcvb"};
	strcat(a,b);
	printf("\n%s\n",a);
	return 0;
}



void strcat(char *p,char *q)
{
	int i;
	for(i=0;*p!='\0';i++)
		p++;
	for(;*q!='\0';p++,q++)
		*p=*q;
	*p='\0';
}
