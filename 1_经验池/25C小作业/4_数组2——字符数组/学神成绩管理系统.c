#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define maxStuds 100	// 最大学生数量 

typedef struct
{
    long id;
    char name[20];
    char sex;       // 男：M 女：F 
    short age;
    float Chinese;
    float Maths;
    float English;
    float sum; 
}Student;


Student nStud[maxStuds];
int studCount=0;


// 函数声明
void printMenu();			//打印系统面板 
void input(Student *stud); 	//录入学生信息 
void print(Student *stud); 	//输出学生信息 
void search();
void searchById();
void searchByName();
void clearInputBuffer();	// 清空缓冲区

int main() {
    int choice;
    int i; 
    do {
        printMenu();
        scanf("%d",&choice);
        clearInputBuffer();  

        switch(choice) {
		
			char c= 'Y';		// 控制是否继续输入的标志
		
			case 0: {
                printf("系统已退出。\n");
                break;
            }
        	
            case 1: {
		        int count = 0;// 当前录入的学生计数
				printf("请按如下格式录入学生信息：学号,姓名,性别(M/F),年龄,大学语文,高等数学,英语\n");
		        do{
		            if(studCount >= maxStuds) {
		                printf("学生信息数量已达到上限 %d，无法添加更多学生！\n", maxStuds);
		                break;
		            }
		            printf("请输入第 %d 个学生的信息: ", studCount + 1);
		            input(&nStud[studCount]);
		            studCount++; 							// 增加总学生计数
		            count++;     							// 增加当前批次计数
		            printf("成功录入 %d 名学生信息。\n 当前总计: %d/%d\n", count, studCount, maxStuds);
		            printf("是否继续录入？(Y/N): ");
		            void clearInputBuffer();
		            c=getchar();

		        }while(c=='Y' || c=='y');
		        break;
		    }
            
            case 2: {
                for (i=0; i<studCount; i++) {
                    print(&nStud[i]);
                }
            	printf("回到主菜单? Y/N");
				void clearInputBuffer();
				c=getchar();
				if(c=='y'|| c=='Y')
					main();
                break;
            }
            
            case 3: {
                search();
                printf("回到主菜单? Y/N");
				void clearInputBuffer();
				c=getchar();
				if(c=='y'|| c=='Y')
					main();
                break;
            }
            
            
            
            default: {
                printf("无效的选项，请重新选择。\n");
            }
        }
    } while (choice!=0);

    return 0;
}

void printMenu() {
	system("cls"); 
	printf("***************************************************************\n\n");
	printf("- - - - - - - - - - - -学习成绩管理系统- - - - - - - - - - - -- -\n");
    printf("    1. 录入学生信息               ");
    printf("          2.浏览学生信息   \n");
    printf("    3. 成绩查询                   ");
    printf("          0. 退出系统\n");
    printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");
	printf("*****************************************************************\n");
	printf("请选择(0-3): ");
}

void input(Student *stud) {
    while (1) {
        int ret = scanf("%ld,%19[^,],%c,%hd,%f,%f,%f",
                      &stud->id,
                      stud->name,
                      &stud->sex,
                      &stud->age,
                      &stud->Chinese,
                      &stud->Maths,
                      &stud->English);
        clearInputBuffer();

        if (ret != 7) {
            printf("输入格式错误！请重新输入:\n");
            continue;
        }

        // 验证性别
        if (stud->sex != 'M' && stud->sex != 'F') {
            printf("性别只能是 M 或 F！请重新输入:\n");
            continue;
        }

        // 计算总分
        stud->sum = stud->Chinese + stud->Maths + stud->English;
        break;
    }
}

void print(Student *stud) {
    printf("\n学号: %ld\n姓名: %s\n性别: %c\n年龄: %d\n",
           stud->id, stud->name, stud->sex, stud->age);
    printf("语文: %.1f\n数学: %.1f\n英语: %.1f\n总分: %.1f\n\n",
           stud->Chinese, stud->Maths, stud->English, stud->sum);
}

void search() {
    int choice;
    do {
        printf("\n- - - -学生成绩查询方式- - - -\n");
        printf("          1. 通过学号\n");
        printf("          2. 通过姓名\n");
        printf("          3. 返回主菜单\n");
        printf("  请选择 (1-3): ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
            case 1: searchById(); break;
            case 2: searchByName(); break;
            case 3: return;
            default: printf("无效的选项，请重新选择。\n");
        }
    } while (choice != 3);
}

void searchById() {
	int i;
    long int id;
    bool found = false;
    printf("请输入要查询的学生学号: ");
    scanf("%ld", &id);
    clearInputBuffer();

    for (i = 0; i < maxStuds; i++) {
        if (nStud[i].id == id) {
            found = true;
            printf("找到学生信息：\n");
            print(&nStud[i]);
            break;
        }
    }

    if (!found) {
        printf("未找到学号为 %ld 的学生。\n", id);
    }
}

void searchByName() {
	int i;
    char name[20];
    bool found = false;
    printf("请输入要查询的学生姓名: ");
    scanf("%19s", name);
    clearInputBuffer();

    for (i = 0; i < maxStuds; i++) {
        if (strcmp(nStud[i].name, name) == 0) {
            found = true;
            printf("找到学生信息：\n");
            print(&nStud[i]);
            break;
        }
    }

    if (!found) {
        printf("未找到姓名为 %s 的学生。\n", name);
    }
}

void clearInputBuffer() {
    while (getchar() != '\n');
}
