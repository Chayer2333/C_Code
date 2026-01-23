#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"string.h"
#define M 500
int N=0;
struct student
{
	char name[20];
	long stu_id;
	char sex;
	int score_math;
	int score_Eng;
	int score_C_lang;
	int sum;
}stu[M];

void meun()
{
	system("cls");
	printf("***************************************************************\n\n");
	printf("- - - - - - - - - - - -学习成绩管理系统- - - - - - - - - - - -- -\n");
	printf("1. 录入学生信息               ");                     
	printf("      2.浏览学生信息   \n");
	printf("3.查找学生信息                ");            
	printf("      4.对学生信息排序 \n");
	printf("5.统计学生信息                ");
	printf("      6.添加学生信息   \n");
	printf("7.修改学生信息                ");
	printf("      8.删除学生信息   \n");      
	printf("9.退出程序\n");
	printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");
	printf("*****************************************************************\n");
}

int main()//---------主函数-------------------
{
	int t;
	char c;
    meun();
	printf("输入选择类型1--8:  ");
	scanf("%d",&t);
	switch(t)
	{
	    case 1:
			
			printf("回到主菜单?y/n(若想终止查找按任意键) ");
			getchar();
			c=getchar();
			if(c=='y'||c=='Y')
				main();
			    break;
		case 2:
			
			printf("回到主菜单?y/n(若想终止查找按任意键) ");
			getchar();
			c=getchar();
			if(c=='y'||c=='Y')
				main();
			    break;
		 case 3:
			
			printf("回到主菜单?y/n(若想终止查找按任意键) ");
			getchar();
			c=getchar();
			if(c=='y'||c=='Y')
				main();
			    break;
		case 4:
			
			printf("回到主菜单?y/n(若想终止查找按任意键) ");
			getchar();
			c=getchar();
			if(c=='y'||c=='Y')
				main();
			    break;
		case 5:
				
				printf("回到主菜单?y/n(若想终止查找按任意键) ");
			    getchar();
			    c=getchar();
			    if(c=='y'||c=='Y')
				   main();
			       break;
		case 6:
				
				printf("回到主菜单?y/n(若想终止查找按任意键) ");
			    getchar();
			    c=getchar();
			    if(c=='y'||c=='Y')
				   main();
			       break;
		case 7:
				
				printf("回到主菜单?y/n(若想终止查找按任意键) ");
			    getchar();
			    c=getchar();
			    if(c=='y'||c=='Y')
				   main();
			       break;
		case 8:
				
				printf("回到主菜单?y/n(若想终止查找按任意键) ");
			    getchar();
			    c=getchar();
			    if(c=='y'||c=='Y')
				   main();
			       break;
		case 9:
			printf("请输入任意键退出\n");
	}
	return 0; 
}
