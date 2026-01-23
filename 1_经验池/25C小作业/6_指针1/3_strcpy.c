#include<stdio.h>
#define N 20

void strcpy(char *,char *);

int main()
{
	char a[N],b[N];
	printf("ÇëÊäÈë´ı¸´ÖÆµÄ×Ö·û´®£º");
	scanf("%19s",a);
	strcpy(a,b);
	printf("%s",b);
	return 0;
}



void strcpy(char *p,char *q)
{
	int i;
	for(i=0;i<N;i++)
	{
		*(q+i)=*(p+i);
	}
}
