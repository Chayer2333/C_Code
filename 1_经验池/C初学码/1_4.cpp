#include <stdio.h>

int main()                          /*主函数*/ 
{ 
	 int max(int a,int b);  /* 对被调函数的max的声明*/ 
	 int value1,value2,largenumber;         /* 定义三个变量 */
	 printf("请通过键盘输入两个整数：\n"); /* 提示输入两个整数 */
	 scanf("%d%d",&value1,&value2);      /* 输入value1,value2变量的值 */
	 largenumber=max(value1,value2);      /* 调用max函数，得到的值赋给largenumber*/
	 printf("largenumber=%d\n",largenumber);
	 return 0;
}
//自定义函数放在main函数后面，在main里面要进行声明（第五行代码） 
int max(int a,int b)     /*定义max函数，其值为整型，形式参数a、b也是整型*/
{
	int c;               /* max函数中声明部分，定义本函数中用到的变量c */
	if(a>b){ 
		c=a;
	} 
	else{
		c=b;
	}	
	 return c ;           /* 将c的值返回，通过max带回到调用函数的位置 */
}
