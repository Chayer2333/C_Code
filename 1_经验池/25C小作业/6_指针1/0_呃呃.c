#include<stdio.h>
void loc_strcpy(char*,char*,int);

int main()
{
	char a[16]={"I am from hubei"};
	char b[]={"©d(¨R¨Œ¨Q*)o"};
	int m=5;
	printf("\n%s\n",a);
	loc_strcpy(a,b,m);
	printf("\n%s\n",a);
	return 0;
}



void loc_strcpy(char *p,char *q,int m)
{
	p+=m;
	while((*p++=*q++)!='\0');
}
