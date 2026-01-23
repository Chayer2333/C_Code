/*
用数组类型处理求10个学生的平均成绩及高于平均成绩的人数。
*/
#include"stdio.h"
int main()
{
	float score[10],avg,sum=0;
	int num=0,i;
	printf("输入每名学生的成绩:\n");
	for(i=0;i<10;i++)
	{
		scanf("%f",&score[i]);//将输入的每位学生的分数存入数组中 
		sum=sum+score[i];//计算学生分数总和 
	}
	avg=sum/10;//平均分 
	printf("10名学生的平均成绩:%.2f\n",avg);
    for(i=0;i<10;i++){
    	if(score[i]>avg){//高于平均分的计数+1 
    		num++;
		}	
	}
	printf("高于平均成绩学生人数：%d\n",num);
    return 0;
}

