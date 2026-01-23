#include<stdio.h>
#include<string.h>
#define N 2

struct student
{
	long int id;
	char name[20];
	char sex;		//男：M 女：F 
	short int age;
	float Chinese;
	float Maths;
	float English;
	float sum; 
};

struct student stnum[N];

void printMenu();
void input(struct student *stud);
void print(struct student *stud);
void Srch();
void srch_by_id();
void srch_by_name();
//结构体要先于其函数定义！ 

int main()
{
	int i,choice;
	do {
		printMenu();
        scanf("%d", &choice);
        while(getchar()!='\n');
        
        switch(choice)
        {
        	case 1:
        		{
        			printf("请按如下格式录入学生信息：学号,姓名,性别(M/F),年龄,大学语文,高等数学,英语\n");
					for(i=0;i<N;i++)
					{
						printf("请输入第 %d 个学生的信息:\n",i+1);
						input(stnum+i);	
					}
				}break;
			
			case 2:
				{
					for(i=0;i<N;i++)
						print(stnum+i);
				}break;
			
			case 3:
				{
					Srch();
				}break;
			
			case 4:
				{
					printf("系统已退出。\n");
				}break;
			
			default:
				{
					printf("无效的选项，请重新选择。\n");
				}break;
		}
       
	}while(choice != 4);
	
	
	return 0;
}



void printMenu()
{
    printf("\n学生成绩管理系统\n");
    printf("1. 成绩录入\n");
    printf("2. 成绩显示\n");
    printf("3. 成绩查询\n");
    printf("4. 退出系统\n");
    printf("请选择(1-4): ");
}



void input(struct student *stud)
{
	scanf("%ld,%19[^,],%c,%hd,%f,%f,%f",
		&stud->id,
         stud->name,
        &stud->sex,
        &stud->age,
        &stud->Chinese,
        &stud->Maths,
        &stud->English);
	stud->sum=stud->Chinese+stud->Maths+stud->English;
		
    while(getchar()!='\n');// 清空输入缓冲区（防止后续输入被残留的换行符影响）
}



void print(struct student *stud) 
{
    printf("\nNO.%ld\n 姓名:%s\n 性别:%c\n 年龄:%d\n 语数英成绩:%5.1f,%5.1f,%5.1f\n 总成绩:%.1f\n\n",
           stud->id,
           stud->name,
           stud->sex,
           stud->age,
           stud->Chinese,
           stud->Maths,
           stud->English,
           stud->sum);
}



void Srch()
{
	int choice;
	do {
		
	    printf("\n学生成绩查询方式\n");
	    printf("1. 通过学号\n");
	    printf("2. 通过姓名\n");
	    printf("3. 返回主菜单\n");
	    printf("请选择(1-3): ");
	    scanf("%d",&choice);
	    while(getchar()!='\n');
    
    	switch(choice)
		{
        	case 1: srch_by_id();  break;
        	case 2: srch_by_name();break;
        	case 3:				  return;
        	default:printf("无效的选项，请重新选择。\n");
		}
	}while(choice!=3);
}



void srch_by_id()
{
	int id,i,found=0;// 标记是否找到学生
    printf("请输入要查询的学生学号: ");
    scanf("%d",&id);						
    for(i=0;i<N;i++) 
	{
        if((stnum+i)->id==id)
		{
            found = 1;
            printf("找到学生信息：\n");
            print(stnum+i);
            break;
    	}
    }
    if(found==0)
    	printf("未找到学号为 %d 的学生。\n",id);     
}



void srch_by_name()
{
	int i,found=0;// 标记是否找到学生
	char name[20];
    printf("请输入要查询的学生姓名: ");
    scanf("%19s",name);						
    for(i=0;i<N;i++) 
	{
        if(strcmp((stnum+i)->name,name)==0)
		{
            found = 1;
            printf("找到学生信息：\n");
            print(stnum+i);
            break;
    	}
    }
    if(found==0)
    	printf("未找到姓名为 %s 的学生。\n",name);     
}
