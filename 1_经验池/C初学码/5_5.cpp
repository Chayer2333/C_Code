/*
在全系1000名学生中，征集慈善募捐，当募捐款达到10万元时就停止募捐活动，统计此时捐款的人数，以及平均每人捐款的数目。
*/
#include <stdio.h>               
int main()
{
	float amount,aver,total; 
	int i;
	for (i=1,total=0;i<=1000;i++)          
	{
		 printf("please enter amount:");
		 scanf("%f",&amount);              
		 total= total+amount;               
		 if (total>=100000) 
		 {
		 	break; //跳出循环，立即停止 
		 }            
	}
	aver=total/i;
	printf("num=%d\naver=%10.2f\n",i,aver); 
	return 0;
}   
