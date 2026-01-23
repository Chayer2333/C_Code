/*
°´ÐÐÊä³öC program£»VC++6.0£»Data structure×Ö·û´®¡£
*/
//char ch[10]={'C',' ','p','r','o','g','r','a','m'};
//ch[0]='C';ch[1]=  ;¡­¡­ch[8]=m;ch[9]=0

//char ch[2][13]={"C program","Visual studio"};
//ch[0]={"C program"} ch[0]="Visual studio"
//ch[0][0]='C' ch[0][1]= ch[0][2]=p.......ch[0][9]=0...ch[0][12]=0 
//ch[1][0]='V' ch[1][1]='i' ch[1][2]=s........ch[0][12]='o' 
#include"stdio.h"
int main()
{
	char str[3][20]={"C program","VC++6.0","Data structure"};
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<20;j++){
			printf("%c",str[i][j]);
		}
		printf("\n");
	}
	return 0;
}
