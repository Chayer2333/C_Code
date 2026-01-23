#include<stdio.h>
void Transletter(char[],char[],int);
int main()
{
	char a[20],b[20];
	int i;
	char *p;
	printf("请输入小于二十个字节的字符串：\n");
	p=a;scanf("%19s",p);
	Transletter(a,b,20);
	printf("%s\n",a);
	printf("%s\n",b);
	return 0;
}

void Transletter(char a[],char b[],int n)
{
	int i;char *p,*q;
	for(i=0;i<n;i++)
	{
		p=a;q=b;
		switch(*(p+i))
		{
			case 'A':*(q+i)=*(p+i)+32;break;case 'N':*(q+i)=*(p+i)+32;break;
			case 'B':*(q+i)=*(p+i)+32;break;case 'O':*(q+i)=*(p+i)+32;break;
			case 'C':*(q+i)=*(p+i)+32;break;case 'P':*(q+i)=*(p+i)+32;break;
			case 'D':*(q+i)=*(p+i)+32;break;case 'Q':*(q+i)=*(p+i)+32;break;
			case 'E':*(q+i)=*(p+i)+32;break;case 'R':*(q+i)=*(p+i)+32;break;
			case 'F':*(q+i)=*(p+i)+32;break;case 'S':*(q+i)=*(p+i)+32;break;
			case 'G':*(q+i)=*(p+i)+32;break;case 'T':*(q+i)=*(p+i)+32;break;
			case 'H':*(q+i)=*(p+i)+32;break;case 'U':*(q+i)=*(p+i)+32;break;
			case 'I':*(q+i)=*(p+i)+32;break;case 'V':*(q+i)=*(p+i)+32;break;
			case 'J':*(q+i)=*(p+i)+32;break;case 'W':*(q+i)=*(p+i)+32;break;
			case 'K':*(q+i)=*(p+i)+32;break;case 'X':*(q+i)=*(p+i)+32;break;
			case 'L':*(q+i)=*(p+i)+32;break;case 'Y':*(q+i)=*(p+i)+32;break;
			case 'M':*(q+i)=*(p+i)+32;break;case 'Z':*(q+i)=*(p+i)+32;break;
			default :*(q+i)=*(p+i);break;
		}
	}
}
