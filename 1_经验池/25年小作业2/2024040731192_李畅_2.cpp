#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 最大存储数量 
#define maxStuds 2

typedef struct
{
	char ID[20];
	char name[20];
	short sex;
	short age;
} Student;


Student nStud[maxStuds];	// 定义结构体数组
int studCount=0;			// 定义全局容量 


// ** 函数声明 **
void printMenu();				// 打印系统面板
bool input(Student *stud);		// 录入学生信息
void print(Student *stud);		// 输出学生信息
bool search();					// 查找学生信息
bool idUnique(const char *id);	// ID检验函数	
void clearInputBuffer();		// 清空缓冲区

//////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// ** 主函数 **

int main()
{
    int choice;
    int i;

    do {
    	
        printMenu();
        choice=999;
        scanf("%d",&choice);
        clearInputBuffer();  
		
        switch(choice) {
		
			case 0: {			// 退出指令 
                printf("\n系统已退出。\n");
                break;
            }
        	
            case 1: {			// 录入操作 
            	char c = 'N';	// 控制是否继续输入的标志
		        int count = 0;	// 当前录入的学生计数
				printf("\n请按如下格式录入学生信息：学号,姓名,性别(女:0,男:1),年龄 \n");
		        do{
		            if(studCount >= maxStuds) {
		                printf("\n**学生信息数量已达到上限 %d ,无法添加更多学生！**\n", maxStuds);
		                printf("\n按任意键继续....");
            			c=getchar();
		                break;
		            }
		            printf("\n_ _ _ _请输入第 %d 个学生的信息: _ _ _ _", studCount+1);
		            if(input(&nStud[studCount])) {
		            	studCount++; 						// 增加总学生计数
		            	count++;     							// 增加当前批次计数
		            	printf("\n_ 成功录入 %d 名学生信息,当前总计: %d/%d _\n", 
								count, studCount, maxStuds);
					} else {
						printf("\n**达到输错容许上限,已取消录入！**\n");
					}
					printf("\n是否继续录入？(Y/N): ");
		            c=getchar();
		            clearInputBuffer();
		        }while(c=='Y'||c=='y');
		        break;
		    }
            
            case 2: {			// 显示操作 
            	char c;
            	
            	if(studCount!=0)
	                for (i=0; i<studCount; i++) {
	                    print(&nStud[i]);
	                }
	            else
	            	printf("\n**当前无学生信息！**\n");
	            	
            	printf("\n按任意键继续....");
            	c=getchar();
                break;
            }
            
            case 3: {			// 查询操作
            	char c = 'N';
				do {
	                if(search()) {
	                	printf("\n是否继续查找？(Y/N): ");
		            	c=getchar();
		            	clearInputBuffer();
					} else {
						printf("\n按任意键继续....");
            			c=getchar();
						break;
					}
				}while(c=='y'||c=='Y'); 
            	break;
            }
            
            default: {			// 错误提示 
                printf("\n**无效的选项,请重新选择!**\n");
                printf("\n按任意键继续....");
            	char c=getchar();
                continue;;
            }
        }
    } while(choice!=0);
	
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 控制面板 **

void printMenu() {
	system("cls");
	printf("*****************************************************************\n\n");
	printf("- - - - - - - - - - - -学习成绩管理系统- - - - - - - - - - - - -\n");
    printf("    1. 录入学生信息               ");
    printf("          2.浏览学生信息   \n");
    printf("    3. 成绩查询                   ");
    printf("          0. 退出系统\n");
    printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");
	printf("*****************************************************************\n");
	printf("\n当前选择: ");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 输入/输出 ** 

bool input(Student *stud) {
	
	int maxAttempts=3;// 最大容许输错量
	int count=0;
	Student temp;
	
     while(count < maxAttempts) {
        printf("\n\n	请输入: ");
        int ret=scanf("%19[^,],%19[^,],%hd,%hd", 
                      temp.ID, 
                      temp.name, 
                      &temp.sex, 
                      &temp.age
					  );
        clearInputBuffer();
        
        // 验证输入合法性
        if (ret!=4) {
            printf("\n**错误：缺少字段或格式错误！请重新输入。**\n");
            count++;
            continue;
        }
        
        // 验证学号唯一性
		 
		if (!idUnique(temp.ID)) {
        	printf("\n**错误：学号 %s 已存在！请重新输入。**\n", temp.ID);
            count++;
            continue;
        }
        
        // 验证sex合法性
        if (temp.sex!=0&&temp.sex!=1) {
            printf("\n**错误：性别只能为 女:0 or 男:1 ！请重新输入。**\n");
            count++;
            continue;
        }
        
        // 验证age合法性
        if (temp.age<1||temp.age>110) {
            printf("\n**错误：年龄范围应为 1~110 ！请重新输入。**\n");
            count++;
            continue;
        }
        
        // 所有验证通过，复制数据到目标结构体
        strcpy(stud->ID,temp.ID);
        strcpy(stud->name,temp.name);
        stud->sex=temp.sex;
        stud->age=temp.age;
        
        return true;
    }
    
    return false;
}

void print(Student *stud) {
    printf("\n学号: %s\n姓名: %s\n性别: %s\n年龄: %hd\n",
           stud->ID,
		   stud->name,
           stud->sex==0?"女":"男",
           stud->age
		   );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 查询 ** 

bool search() {
    if (studCount==0) {
        printf("\n**当前无学生信息！**\n");
        return false;
    }
    
    int i=0;
    char id[20];
    bool found=false;
    printf("\n请输入要查询的学生学号: ");
    scanf("%19s", id);
    clearInputBuffer();

    printf("\n_ _ _ _查询结果：_ _ _ _\n");
    for (i=0; i<studCount; i++) {
        if (strcmp(nStud[i].ID, id)==0) {
            found=true;
            printf("\n找到学生信息：\n");
            print(&nStud[i]);
            break;
        }
    }

    if (!found) {
        printf("\n**未找到学号为 %s 的学生。**\n", id);
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 学号唯一性检查 **

bool idUnique(const char *id) {
	int i=0; 
    for (i=0; i<studCount; i++) {
        if (strcmp(nStud[i].ID, id) == 0) {
            return false; // 学号已存在
        }
    }
    return true; // 学号唯一
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 清除缓冲区 **

void clearInputBuffer() { 
    while(getchar()!='\n');
}
