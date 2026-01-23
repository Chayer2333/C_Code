#include<stdio.h>
void Transletter(char[],char[],int n);
int main()
{
    char a[20],b[20];
    printf("请输入小于二十个字节的字符串：\n");
    scanf("%19s",a);                            	  //限制输入长度防止溢出
    Transletter(a,b,20);
    printf("原字符串: %s\n",a);
    printf("转换后字符串: %s\n",b);
    return 0;
}


void Transletter(char a[],char b[],int n)
{
    int i;
    for(i=0;i<n;i++)       						 	  //循环直到n或遇到字符串结束符
    {
        if(*(a+i)>='A'&&*(a+i)<='Z')  		 		  // 如果是大写字母
            *(b+i)=*(a+i)+32;  					 	  // 转换为小写
        else
        	*(b+i)=*(a+i);  						  // 其他字符不变
    }
    *(b+i)='\0';  								  // 添加字符串结束符
}
