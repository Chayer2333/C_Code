#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define maxStuds 100	// 最大学生数量 
#define maxSubjects 10	// 最多可以处理的科目数量
#define maxGrades 10	// 最多分级数 
#define nameLen 20		// 最长名称 


// 等级范围结构
typedef struct
{
    char grade;         // 定义等级标识
    float minScore;    	// 该等级的最低分
    float maxScore;    	// 该等级的最高分
} GradeRange;


// 科目配置结构
typedef struct
{
    char name[nameLen]; // 科目名称
    int type; 			// 0: 原始分, 1: 等级制
    float minScore;    	// 最低可能分数
    float maxScore;    	// 最高可能分数
    GradeRange ranges[maxGrades]; // 等级分段
    int gradeCount;    	// 实际等级数量
} SubjectConfig;


// 学生成绩结构
typedef struct
{
    float rawScore;		// 原始分数
    char grade;			// 等级成绩
} SubjectGrade;


// 学生信息结构 
typedef struct
{
    long int id;		// 学号 
    char name[nameLen];	// 姓名 
    char sex;       	// 男：M 女：F 
    short int age;		// 年龄 
    SubjectGrade grades[maxSubjects];// 加载成绩结构 
    float total;		// 原始总分 
} Student;

// 系统全局状态
typedef struct 
{
    Student nStuds[maxStuds];
    SubjectConfig subjects[maxSubjects];
    int studCount;
    int subjCount;
} GradeSystem;






// 函数声明
void printMenu0();					// 打印系统菜单 
void init_system(GradeSystem *sys);	// 初始化系统
void setup_subjects(GradeSystem *sys);// 设置科目信息
void input(Student *stud);			// 录入学生信息 
void print(Student *stud);			// 打印学生信息 
void search();
void searchById();
void searchByName();
void clearInputBuffer();			// 清空缓冲区 




void add_student(GradeSystem *sys);
void enter_grades(GradeSystem *sys, int student_index);
void display_students(GradeSystem *sys);
void display_subject_config(GradeSystem *sys);
char convert_to_grade(SubjectConfig *subject, float score);
void save_data(GradeSystem *sys);
void load_data(GradeSystem *sys);


int main() {
	GradeSystem sys;		// 加载系统 
    init_system(&sys);		// 初始化系统 initialize（初始化） 
    int choice;
    int i; 
    do {
        printMenu0();
        scanf("%d",&choice);
        clearInputBuffer();  // 清空缓冲区

        switch(choice) {
            case 1: {
                printf("请按如下格式录入学生信息：学号,姓名,性别(M/F),年龄,大学语文,高等数学,英语\n");
                for (i = 0; i < maxStuds; i++) {
                	if(1) {
		    		printf("学生信息数量已达到上限:\n");
		    		return;
					} 
                    printf("请输入第 %d 个学生的信息:\n", i+1);
                    input(&nStuds[i]);
                }
                break;
            }
            case 2: {
                for (i = 0; i < studCount; i++) {
                    print(&nStuds[i]);
                }
                break;
            }
            case 3: {
                search();
                break;
            }
            case 4: {
                printf("系统已退出。\n");
                break;
            }
            default: {
                printf("无效的选项，请重新选择。\n");
            }
        }
    } while (choice != 4);

    return 0;
}


// 打印系统菜单
void printMenu0() {
	system("cls"); 
	printf("***************************************************************\n\n");
	printf("- - - - - - - - - - - -学习成绩管理系统- - - - - - - - - - - -- -\n");
    printf("\n学生成绩管理系统\n");
    printf("1. 成绩录入\n");
    printf("2. 成绩显示\n");
    printf("3. 成绩查询\n");
    printf("4. 退出系统\n");
    printf("请选择(1-4): ");
    printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");
	printf("*****************************************************************\n");
}


// 初始化系统
void init_system(GradeSystem *sys) {
    sys->studCount=0;
    sys->subjCount=0;
}


// 设置科目信息
void setup_subjects(GradeSystem *sys) {
    printf("\n===== 科目设置 =====\n");
    printf("当前科目数量: %d\n", sys->subjCount);		// 查看已定义科目数目 
    
    if(sys->subjCount >= maxSubjects) {
        printf("已达到最大科目数量(%d)!\n",maxSubjects);
        return;
    }
    
    SubjectConfig *sub = &sys->subjects[sys->subjCount];// 定义操作指针 指向科目结构 
    
    // 输入科目名称
    printf("请输入科目名称: ");
    fgets(sub->name, nameLen, stdin);					// 设定名称 stdin(标准输入流，关联到键盘输入)
    sub->name[strcspn(sub->name, "\n")] = '\0'; 		// 移除换行符
    
    // 选择评分类型
    printf("评分类型 (0-原始分, 1-等级制): ");
    scanf("%d", &sub->is_grade_type);
    
    // 输入分数范围
    printf("最低可能分数: ");
    scanf("%f", &sub->min_score);
    printf("最高可能分数: ");
    scanf("%f", &sub->max_score);
    
    // 如果是等级制，设置等级分段
    if(sub->is_grade_type) {
        printf("请输入等级数量 (最多%d): ", MAX_GRADES);
        scanf("%d", &sub->grade_count);
        
        if(sub->grade_count > MAX_GRADES) {
            sub->grade_count = MAX_GRADES;
        }
        
        printf("请按从高到低的顺序输入等级信息:\n");
        int i = 0;
        for(i = 0; i < sub->grade_count; i++) {
            printf("等级 %d:\n", i+1);
            printf("  等级标识 (如A, B, C): ");
            scanf(" %c", &sub->grade_ranges[i].grade);
            printf("  最低分: ");
            scanf("%f", &sub->grade_ranges[i].min_score);
            printf("  最高分: ");
            scanf("%f", &sub->grade_ranges[i].max_score);
        }
    }
    
    sys->subject_count++;
    printf("科目 '%s' 添加成功!\n", sub->name);
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
        printf("\n学生成绩查询方式\n");
        printf("1. 通过学号\n");
        printf("2. 通过姓名\n");
        printf("3. 返回主菜单\n");
        printf("请选择(1-3): ");
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
