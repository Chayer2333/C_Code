#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// 验证字段标志位
#define VALIDATE_NULL    0x00	// ->0
#define VALIDATE_ID      0x01	// ->1
#define VALIDATE_SEX     0x02	// ->3
#define VALIDATE_AGE     0x04	// ->4
#define VALIDATE_CHINESE 0x08	// ->5
#define VALIDATE_MATHS   0x10	// ->6
#define VALIDATE_ENGLISH 0x20	// ->8
#define VALIDATE_ALL     0x3F	// 00111111
//( 通过 0x01 | 0x02 | 0x04 | 0x08 | 0x10 | 0x20 得到的 )

#define VALIDATION_SUCCESS	0   // 验证成功（无错误）
#define VALIDATION_FAILED   1   // 验证失败


#define maxStuds 100			// 最大学生数量 
#define FLOAT_EPSILON 0.0001f	// 处理浮点数比较的精度问题

typedef struct
{
    long id;
    char name[20];
    char sex;       		// 男：M 女：F 
    short age;
    float Chinese;
    float Maths;
    float English;
    float total; 
}Student;

typedef int (*CompareFunc)(const Student*, const Student*);		// 定义比较函数的类型

Student nStud[maxStuds];										// 定义结构体数组 
int studCount=0;												// 定义有效全局容量 


// ** 函数声明 **
void printMenu();												// 打印系统面板
void input(Student *); 											// 录入学生信息
bool idUnique(long, Student *, int, Student *);					// 检验ID唯一性
int validate(Student *, int , int *);							// 输入合法性检验
void disError(int , Student *);									// 打印错误信息 
void print(Student *); 											// 输出学生信息

void search();													// 查找系统
void searchById();												// 通过ID查 
void searchByName(); 											// 通过名字查 

void statsys();													// 统计系统 

void sortsys();													// 排序系统
void sortMain(Student arr[], int , CompareFunc , int );			// 通用排序函数(猫泡排序)
void sortById();												// 排序学号 
void sortByTotal();												// 排序总分 
void sortByName();												// 排序姓名 
int compareById(const Student *, const Student *);				// 学号比较函数
int compareByTotal(const Student *, const Student *);			// 总分比较函数
int compareByName(const Student *, const Student *);			// 姓名比较函数 

void upDatesys();												// 修改系统
void upDate_one(Student *stud, int); 							// 修改成员 
void deleteStudent();											// 删除系统

void save();													// 存储系统
void load();													// 读取系统 

void clearInputBuffer();										// 清空缓冲区

//////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// ** 主函数 **

int main() {
	
	load();
    int choice;
    int i;
	 
    do {
    	
        printMenu();
        choice=999;
        scanf("%d",&choice);
        clearInputBuffer();  

        switch(choice) {
		
			char c= 'N';		// 控制是否继续输入的标志
		
			case 0: {			// 退出指令 
				save();
                printf("系统已退出。\n");
                break;
            }
        	
            case 1: {			// 录入操作 
		        int count = 0;	// 当前录入的学生计数
				printf("请按如下格式录入学生信息：学号,姓名,性别(M/F),年龄,大学语文,高等数学,英语\n");
		        do{
		            if(studCount >= maxStuds) {
		                printf("学生信息数量已达到上限 %d，无法添加更多学生！\n", maxStuds);
		                break;
		            }
		            printf("请输入第 %d 个学生的信息: ", studCount+1);
		            input(&nStud[studCount]);
		            studCount++; 							// 增加总学生计数
		            count++;     							// 增加当前批次计数
		            printf("成功录入 %d 名学生信息。\n 当前总计: %d/%d\n", count, studCount, maxStuds);
					printf("是否继续录入？(Y/N): ");
		            c=getchar();
		        }while(c=='Y' || c=='y');
		        break;
		    }
            
            case 2: {			// 显示操作 
                for (i=0; i<studCount; i++) {
                    print(&nStud[i]);
                }
            	printf("回到主菜单? (Y/N) :");
				c=getchar();
				if(c=='y'|| c=='Y')
					continue;
                break;
            }
            
            case 3: {			// 查询操作 
                search();
                printf("回到主菜单? (Y/N) :");
				c=getchar();
				if(c=='y'|| c=='Y')
					continue;
                break;
            }
            
            case 4: {			// 统计操作 
            	sortsys();
                printf("回到主菜单? (Y/N) :");
				c=getchar();
				if(c=='y'|| c=='Y')
					continue;
                break;
            }
            
            case 5: {			// 修改操作 
            	upDatesys();
                printf("回到主菜单? (Y/N) :");
				c=getchar();
				if(c=='y'|| c=='Y')
					continue;
                break;
            }
            
            case 6: {			// 删除操作 
			    deleteStudent();
			    printf("回到主菜单? (Y/N) :");
			    c=getchar();
			    if(c=='y'|| c=='Y')
			        continue;
			    break;
			}
			
			case 7: {			// 储存操作 
			    save();
			    printf("回到主菜单? (Y/N) :");
			    c=getchar();
			    if(c=='y' || c=='Y')
			        continue;
			    break;
			}
			
			case 8: {			// 载入操作 
			    load();
			    printf("回到主菜单? (Y/N) :");
			    c=getchar();
			    if(c=='y' || c=='Y')
			        continue;
			    break;
			}
            
            default: {			// 错误提示 
                printf("无效的选项，请重新选择。\n");
                scanf("%d",&choice);
                continue;;
            }
        }
    } while (choice!=0);

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
    printf("          4.学生信息排序   \n");
    printf("    5. 成绩修改                   ");
    printf("          6.学生信息删除   \n");
    printf("    7. 成绩保存                   ");
    printf("          8.成绩载入       \n");
    printf("    0. 退出系统\n");
    printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");
	printf("*****************************************************************\n");
	printf("请选择(0-8): ");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 录入/显示系统 **

void input(Student *stud) {
	
	int maxAttempts = 3;// 最大容许输错量 
	int errorField=0;	// 示错变量 
	
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

		// 验证输入合法性 
        if (ret!=7) {
            printf("错误：缺少字段或格式错误！请重新输入:\n");
            continue;
        }
		
		// 计算总分
        stud->total = stud->Chinese + stud->Maths + stud->English;
        break;
    }
		
    // 输入验证
	while(maxAttempts-- > 0) {	//防止 upDate_one 调用太多导致栈溢出或死循环
	    if(validate(stud, VALIDATE_ALL, &errorField)) {
	        break;
		}
	    disError(errorField, stud);
	    upDate_one(stud, errorField);
	}
	if(errorField!=0) {
	    printf("输入错误超过3次，已取消录入\n");
	    return;
	}
}

void print(Student *stud) {
    printf("\n学号: %ld\n姓名: %s\n性别: %c\n年龄: %d\n",
           stud->id, stud->name, stud->sex, stud->age);
    printf("语文: %.1f\n数学: %.1f\n英语: %.1f\n总分: %.1f\n\n",
           stud->Chinese, stud->Maths, stud->English, stud->total);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 检验系统 **

bool idUnique(long id, Student *stud, int count, Student *exclude) {
		   //(   ID  ,结构体数组地址, 数组长度 ,  排除检验的成员 ) 
	int i=0;
	for (i=0; i<count; i++) {
        // 跳过要排除的学生，修改学号时排除当前学生，避免自冲突
        if (exclude!=NULL && &stud[i]==exclude) {
            continue;
        }
	    if(stud[i].id==id) {
	    	return false;
	    }
    }
    return true;
}

int validate(Student *stud, int flags, int *errorField) {
	
	 char tempSex = stud->sex;
	 
    // 验证学号唯一性
    if((flags & VALIDATE_ID) && !idUnique(stud->id, nStud, studCount, stud)) {
        *errorField = 1;
        return VALIDATION_FAILED;
    }

    // 验证性别
    if(flags & VALIDATE_SEX) {
    char upperSex = toupper(stud->sex);
    if (upperSex!='M' && upperSex!='F') {
        *errorField = 3;
        return VALIDATION_FAILED;
    }
    stud->sex = upperSex;
	}
    
    // 验证年龄范围
    if((flags & VALIDATE_AGE) && (stud->age<0 || stud->age>100)) {
        *errorField = 4;
        return VALIDATION_FAILED;
    }
    
    // 验证成绩范围
    if((flags & VALIDATE_CHINESE) && (stud->Chinese<0 || stud->Chinese>150)) {
        *errorField = 5;
        return VALIDATION_FAILED;
    }
    
    if((flags & VALIDATE_MATHS) && (stud->Maths<0 || stud->Maths>150)) {
        *errorField = 6;
        return VALIDATION_FAILED;
    }

    if((flags & VALIDATE_ENGLISH) && (stud->English<0 || stud->English>150)) {
        *errorField = 7;
        return VALIDATION_FAILED;
    }
    // 所有验证通过
    if(errorField) *errorField=0;
    return VALIDATION_SUCCESS;
}

void disError(int errorField, Student *stud) {
    switch(errorField) {
        case 1: 
            printf("错误：学号 %ld 已存在！\n", stud->id);
            break;
        case 3:
            printf("错误：性别只能是 M(男) 或 F(女)！请重新输入:\n");
            break;
        case 4:
            printf("错误：年龄应在0-100岁之间！\n");
            break;
        case 5:
            printf("错误：语文成绩应在0-150分之间！\n");
            break;
        case 6:
            printf("错误：数学成绩应在0-150分之间！\n");
            break;
        case 7:
            printf("错误：英语成绩应在0-150分之间！\n");
            break;
        default:
            printf("未知错误！请重新输入:\n");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 查询系统 **

void search() {
    int choice;
    do {
    	choice=999;
		system("cls");
        printf("\n- - - -学生成绩查询方式- - - -\n");
        printf("         1. 通过学号\n");
        printf("         2. 通过姓名\n");
        printf("         0. 返回主菜单\n");
        printf("  请选择 (0-2): ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
			case 0: return;
            case 1: searchById(); break;
            case 2: searchByName(); break;
            default: printf("无效的选项，请重新选择。\n");
        }
    } while (choice!=0);
}

void searchById() {
	int i;
    long id;
    bool found = false;
    printf("请输入要查询的学生学号: ");
    scanf("%ld", &id);
    clearInputBuffer();

	printf("\n_ _ _ _查询结果：_ _ _ _\n");
    for (i=0; i<studCount; i++) {
        if (nStud[i].id==id) {
            found = true;
            printf("\n找到学生信息：\n");
            print(&nStud[i]);
            printf("按任意键继续....");
			getchar();
            break;
        }
    }

    if (!found) {
        printf("未找到学号为 %ld 的学生。\n", id);
    }
}

void searchByName() {
    char name[20];
	int i=0;
    int count=0; 						// 计数匹配的学生
    printf("请输入要查询的学生姓名: ");
    scanf("%%19[^,]", name);
    clearInputBuffer();

    printf("\n_ _ _ _查询结果：_ _ _ _\n");
    for(i=0; i<studCount; i++) {
        if(strcmp(nStud[i].name, name)==0) {
            count++;
            printf("\n匹配 %d：\n", count);
            print(&nStud[i]);
        }
    }

    if(count==0) {
        printf("未找到姓名为 %s 的学生。\n", name);
    }else {
        printf("共找到 %d 位同名学生。\n", count);
    }
    printf("按任意键继续....");
	getchar();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 排序系统 **

void sortsys() {
    int choice;
    do {
    	choice=999;
    	system("cls");
        printf("\n- - - -学生成绩排序方式- - - -\n");
        printf("         1. 通过学号            \n");
        printf("         2. 通过总分            \n");
        printf("         3. 通过姓名            \n");
        printf("         0. 返回主菜单          \n");
        printf("  请选择 (0-3): ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
			case 0: return;
            case 1: sortById(); 	break;
            case 2: sortByTotal();  break;
            case 3: sortByName(); 	break;
            default: printf("无效的选项，请重新选择。\n");
        }
    } while (choice != 0);
}

// 排序入口 
void sortById() {
    int ascending;
    printf("0/1 降序/升序：");
    while(1) {
        if(scanf("%d", &ascending)!=1) {
            clearInputBuffer();
            printf("输入无效，请重新输入：\n");
            continue;
        }
        if(ascending==0 || ascending==1) break;
        printf("请重新输入：\n");
    } 
    sortMain(nStud, studCount, compareById, ascending);
    printf("\n任务已完成，按任意键继续....");
    getchar();
	clearInputBuffer();
}

void sortByTotal() {
	int ascending;
	printf("0/1 降序/升序：");
	while(1) {
        if(scanf("%d", &ascending)!=1) {
            clearInputBuffer();
            printf("输入无效，请重新输入：\n");
            continue;
        }
        clearInputBuffer();
        if(ascending==0 || ascending==1) break;
        printf("请重新输入：\n");
    } 
    sortMain(nStud, studCount, compareByTotal, ascending);
    printf("\n任务已完成，按任意键继续....");
    getchar();
	clearInputBuffer();
}

void sortByName() {
    int ascending;
    printf("0/1 降序/升序：");
    while(1) {
        if(scanf("%d", &ascending)!=1) {
            clearInputBuffer();
            printf("输入无效，请重新输入：\n");
            continue;
        }
        clearInputBuffer();
        if(ascending==0 || ascending==1) break;
        printf("请重新输入：\n");
    } 
    sortMain(nStud, studCount, compareByName, ascending);
    printf("\n任务已完成，按任意键继续....");
    getchar();
	clearInputBuffer();
}

// 通用排序函数
void sortMain(Student arr[], int count, CompareFunc compare, int ascending) {
		   //( 结构体数组  ， 数组长  ，     比较函数      ，   排序方式  )
    int i,j;
	bool swapped = false;
	Student temp; 
	if (count<=1) return;
    
    for (i=0; i<count-1; i++) {
        swapped=false;
        for (j=0; j<count-i-1; j++) {
        	
            int result = compare(&arr[j], &arr[j+1]);		//接受比较函数 
            
            // 根据排序方向决定比较方式
            bool shouldSwap = ascending ? (result > 0) : (result < 0);
            
            if(shouldSwap) { 
            	temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

//比较函数定义区 
int compareById(const Student *a, const Student *b) {
    if (a->id < b->id) return -1;
    if (a->id > b->id) return  1;
    return 0;
}	//const定义指针常量防止被意外修改

int compareByTotal(const Student *a, const Student *b) {
    float diff = a->total - b->total;
    if (diff >  FLOAT_EPSILON) return  1;
    if (diff < -FLOAT_EPSILON) return -1;
    return 0;
}	

int compareByName(const Student *a, const Student *b) {
    return strcmp(a->name, b->name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 修改系统 **

void upDatesys() {
	long id;
	int i,choice=0;
	bool found = false;
	printf("请输入要修改学生的ID:");
	if(scanf("%ld", &id)!=1) { 
		printf("输入无效！\n");
		clearInputBuffer();
	    return;
    }
	for(i=0;i<studCount;i++) {
		if(nStud[i].id==id) {
			found = true;
			printf("\n找到学生信息：\n");
			printf("请指向待修改的学生信息：学号->1 ,姓名->2 ,性别(M/F)->3 ,年龄->4 ,大学语文->5 ,高等数学->6 ,英语->7 \n");
			scanf("%d",&choice);
			upDate_one(&nStud[i], choice);
			clearInputBuffer();
			return ;
		}
	}
	if(!found) {
	   	printf("未找到ID为 %ld 的学生。\n", id);
   	}
	printf("\n按任意键继续....");
	clearInputBuffer();
}

void upDate_one(Student *stud, int choice) {
	
	int errorField = 0;
    int validateFlags = 0;
    
	switch(choice) {
			
		case 0: {
			printf("警告：信息未修改！");
		}return ; 
		
		case 1: {
			while(1) {
				
				printf("你正在修改ID：");
				if(scanf("%ld", &stud->id)!=1) {
                    printf("输入无效！\n");
                    clearInputBuffer();
                    continue;
                }
                
				// 验证学号唯一性
		        validateFlags = VALIDATE_ID;
                if(validate(stud, validateFlags, &errorField)) break;
                disError(errorField, stud);
            }
		}
		break;
			
		case 2: {
			printf("你正在修改姓名：");
			if(scanf("%19", stud->name)!=1) {
                printf("输入无效！\n");
                clearInputBuffer();
            } else {
                clearInputBuffer();
            }
		}
		break;
			
		case 3: {
			while(1) {
				
				printf("你正在修改性别：");
				if(scanf(" %c", &stud->sex)!=1) {
                    printf("输入无效！\n");
                    clearInputBuffer();
                    continue;
                }
				clearInputBuffer();
							
				// 验证性别
				stud->sex = toupper(stud->sex); // 统一转为大写
				 validateFlags = VALIDATE_SEX;
                if (validate(stud, validateFlags, &errorField)) break;
                disError(errorField, stud);
            }
		}
		break;
			
		case 4: {
			while(1) {
				
				printf("你正在修改年龄：");
				if(scanf("%hd", &stud->age)!=1) {
                    printf("输入无效！\n");
                    clearInputBuffer();
                    continue;
                }
                clearInputBuffer();
				
				// 验证年龄范围
		        validateFlags = VALIDATE_AGE;
                if (validate(stud, validateFlags, &errorField)) break;
                disError(errorField, stud);
            	}
		}
		break;
			
		case 5: {
			while(1) {
				
				printf("你正在修改语文成绩：");
				if(scanf("%f", &stud->Chinese)!=1) {
                    printf("输入无效！\n");
                    clearInputBuffer();
                    continue;
                }
                clearInputBuffer();
					
				// 验证成绩范围
		    	validateFlags = VALIDATE_CHINESE;
                if (validate(stud, validateFlags, &errorField)) break;
                disError(errorField, stud);
            }
		}
		break;
			
		case 6: {
			while(1) {
				
				printf("你正在修改数学成绩：");
				if(scanf("%f", &stud->Maths)!=1) {
                    printf("输入无效！\n");
                    clearInputBuffer();
                    continue;
                }
					
				// 验证成绩范围
		        validateFlags = VALIDATE_MATHS;
                if (validate(stud, validateFlags, &errorField)) break;
                disError(errorField, stud);
            	}
		}
		break;
			
		case 7: {
			while(1) {
					
				printf("你正在修改英语成绩：");
				if (scanf("%f", &stud->English)!=1) {
                    printf("输入无效！\n");
                    clearInputBuffer();
                    continue;
                }
                clearInputBuffer();
					
				// 验证成绩范围
		         validateFlags = VALIDATE_ENGLISH;
                if (validate(stud, validateFlags, &errorField)) break;
                disError(errorField, stud);
            }
		}
		break;

			
		default: {
	        printf("无效的选项，请重新选择。\n");
	        clearInputBuffer();
            return;
		}
	}
	
	// 计算总分
    stud->total = stud->Chinese + stud->Maths + stud->English;
    printf("学生信息修改成功。\n");

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 删除系统 **

void deleteStudent() {
    long id;
    int i,j;
    char confirm; 
    bool found=false;
    
    printf("请输入要删除的学生ID: ");
    if(scanf("%ld", &id)!=1) {
        printf("输入无效！\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    for(i=0; i<studCount; i++) {
        if(nStud[i].id==id) {
            found=true;
            printf("\n找到学生信息：\n");
            print(&nStud[i]);
            
            printf("\n确认删除该学生信息？(Y/N): ");
            confirm=getchar();
            clearInputBuffer();
            
            if(confirm=='Y' || confirm=='y') {
                // 将后续元素向前移动
                for(j=i; j<studCount-1; j++) {
                    nStud[j]=nStud[j+1];
                }
                studCount--;
                printf("学生信息删除成功。\n");
            } else {
                printf("删除操作已取消。\n");
            }
            break;
        }
    }

    if(!found) {
        printf("未找到ID为 %ld 的学生。\n", id);
    }
    printf("\n按任意键继续....");
    clearInputBuffer();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 文件系统 **

void save() {
    FILE *file=fopen("student.dat", "wb");
    if(file == NULL) {
        printf("无法创建文件！\n");
        return;
    }
    
    // 先写入学生数量
    if(fwrite(&studCount, sizeof(int), 1, file)!=1) {
        printf("写入学生数量失败！\n");
        fclose(file);
        return;
    }
    
    // 写入学生数据
    size_t written=fwrite(nStud, sizeof(Student), studCount, file);
    if(written != studCount) {
        printf("部分数据写入失败！期望写入 %d 条，实际写入 %zu 条\n", studCount, written);
    } else {
        printf("成功保存 %d 名学生数据到文件。\n", studCount);
    }
    
    fclose(file);
}

void load() {
    FILE *file=fopen("student.dat", "rb");
    if(file == NULL) {
        printf("无法打开文件！文件可能不存在。\n");
        return;
    }
    
    // 读取学生数量
    int count;
    if(fread(&count, sizeof(int), 1, file) != 1) {
        printf("读取学生数量失败！\n");
        fclose(file);
        return;
    }
    
    // 检查数量是否合法
    if(count > maxStuds || count < 0) {
        printf("文件损坏：无效的学生数量 %d\n", count);
        fclose(file);
        return;
    }
    
    // 读取学生数据
    size_t read=fread(nStud, sizeof(Student), count, file);
    if(read != count) {
        printf("部分数据读取失败！期望读取 %d 条，实际读取 %zu 条\n", count, read);
    } else {
        printf("成功加载 %d 名学生数据。\n", count);
        studCount=count;							// 更新全局计数器
    }
    
    fclose(file);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 清除缓冲区 **

void clearInputBuffer() {
    while(getchar()!='\n');
}
