#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 10
#define MAX_GRADES 10
#define NAME_LEN 50

// 等级范围结构
typedef struct {
    char grade;         // 等级标识 (A, B, C, ...)
    float min_score;    // 该等级的最低分
    float max_score;    // 该等级的最高分
} GradeRange;

// 科目配置结构
typedef struct {
    char name[NAME_LEN]; // 科目名称
    int is_grade_type;   // 0: 原始分, 1: 等级制
    float min_score;     // 最低可能分数
    float max_score;     // 最高可能分数
    GradeRange grade_ranges[MAX_GRADES]; // 等级分段
    int grade_count;     // 实际等级数量
} SubjectConfig;

// 学生成绩结构
typedef struct {
    float raw_score;     // 原始分数
    char grade;          // 等级成绩
} SubjectGrade;

// 学生信息结构
typedef struct {
    long id;
    char name[NAME_LEN];
    char sex;            // M: 男, F: 女
    short age;
    SubjectGrade grades[MAX_SUBJECTS]; // 各科成绩
    float total;         // 总分（仅计算原始分科目）
} Student;

// 系统全局状态
typedef struct {
    Student students[MAX_STUDENTS];
    SubjectConfig subjects[MAX_SUBJECTS];
    int student_count;
    int subject_count;
} GradeSystem;

// 函数声明
void init_system(GradeSystem *sys);
void setup_subjects(GradeSystem *sys);
void add_student(GradeSystem *sys);
void enter_grades(GradeSystem *sys, int student_index);
void display_students(GradeSystem *sys);
void display_subject_config(GradeSystem *sys);
char convert_to_grade(SubjectConfig *subject, float score);
void save_data(GradeSystem *sys);
void load_data(GradeSystem *sys);
void print_menu();

int main() {
    GradeSystem sys;
    init_system(&sys);
    
    int choice;
    do {
        print_menu();
        printf("请选择操作: ");
        scanf("%d", &choice);
        while(getchar() != '\n'); // 清除输入缓冲区
        
        switch(choice) {
            case 1:
                setup_subjects(&sys);
                break;
            case 2:
                add_student(&sys);
                break;
            case 3:
                if(sys.student_count > 0) {
                    printf("请输入学生序号 (1-%d): ", sys.student_count);
                    int index;
                    scanf("%d", &index);
                    if(index > 0 && index <= sys.student_count) {
                        enter_grades(&sys, index-1);
                    } else {
                        printf("无效的学生序号!\n");
                    }
                } else {
                    printf("没有学生记录!\n");
                }
                break;
            case 4:
                display_students(&sys);
                break;
            case 5:
                display_subject_config(&sys);
                break;
            case 6:
                save_data(&sys);
                break;
            case 7:
                load_data(&sys);
                break;
            case 0:
                printf("退出系统...\n");
                break;
            default:
                printf("无效的选择，请重新输入!\n");
        }
    } while(choice != 0);
    
    return 0;
}

// 初始化系统
void init_system(GradeSystem *sys) {
    sys->student_count = 0;
    sys->subject_count = 0;
    
    // 添加默认科目配置
    strcpy(sys->subjects[0].name, "语文");
    sys->subjects[0].is_grade_type = 0;
    sys->subjects[0].min_score = 0;
    sys->subjects[0].max_score = 100;
    sys->subject_count++;
    
    strcpy(sys->subjects[1].name, "数学");
    sys->subjects[1].is_grade_type = 0;
    sys->subjects[1].min_score = 0;
    sys->subjects[1].max_score = 100;
    sys->subject_count++;
    
    strcpy(sys->subjects[2].name, "英语");
    sys->subjects[2].is_grade_type = 0;
    sys->subjects[2].min_score = 0;
    sys->subjects[2].max_score = 100;
    sys->subject_count++;
}

// 打印菜单
void print_menu() {
    printf("\n===== 学生成绩管理系统 =====\n");
    printf("1. 设置科目信息\n");
    printf("2. 添加学生\n");
    printf("3. 录入学生成绩\n");
    printf("4. 查看所有学生信息\n");
    printf("5. 查看科目设置\n");
    printf("6. 保存数据\n");
    printf("7. 加载数据\n");
    printf("0. 退出系统\n");
    printf("============================\n");
}

// 设置科目信息
void setup_subjects(GradeSystem *sys) {
    printf("\n===== 科目设置 =====\n");
    printf("当前科目数量: %d\n", sys->subject_count);
    
    if(sys->subject_count >= MAX_SUBJECTS) {
        printf("已达到最大科目数量(%d)!\n", MAX_SUBJECTS);
        return;
    }
    
    SubjectConfig *sub = &sys->subjects[sys->subject_count];
    
    // 输入科目名称
    printf("请输入科目名称: ");
    fgets(sub->name, NAME_LEN, stdin);
    sub->name[strcspn(sub->name, "\n")] = '\0'; // 移除换行符
    
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

// 添加学生
void add_student(GradeSystem *sys) {
    if(sys->student_count >= MAX_STUDENTS) {
        printf("学生数量已达上限(%d)!\n", MAX_STUDENTS);
        return;
    }
    
    Student *stu = &sys->students[sys->student_count];
    
    printf("\n===== 添加学生 =====\n");
    printf("学号: ");
    scanf("%ld", &stu->id);
    while(getchar() != '\n'); // 清除输入缓冲区
    
    printf("姓名: ");
    fgets(stu->name, NAME_LEN, stdin);
    stu->name[strcspn(stu->name, "\n")] = '\0'; // 移除换行符
    
    printf("性别 (M/F): ");
    scanf(" %c", &stu->sex);
    stu->sex = toupper(stu->sex); // 转换为大写
    
    printf("年龄: ");
    scanf("%hd", &stu->age);
    
    // 初始化成绩
    int i = 0;
    for(i = 0; i < sys->subject_count; i++) {
        stu->grades[i].raw_score = -1; // -1 表示未录入
        stu->grades[i].grade = 'N';    // N 表示未录入
    }
    stu->total = 0;
    
    sys->student_count++;
    printf("学生 '%s' 添加成功!\n", stu->name);
}

// 录入学生成绩
void enter_grades(GradeSystem *sys, int student_index) {
    Student *stu = &sys->students[student_index];
    
    printf("\n===== 录入成绩 [学生: %s] =====\n", stu->name);
    
    stu->total = 0; // 重置总分
    
    int i = 0;
    for(i = 0; i < sys->subject_count; i++) {
        SubjectConfig *sub = &sys->subjects[i];
        SubjectGrade *grade = &stu->grades[i];
        
        printf("\n科目: %s\n", sub->name);
        
        if(sub->is_grade_type) {
            printf("1. 输入原始分自动转换等级\n");
            printf("2. 直接输入等级\n");
            printf("请选择: ");
            int choice;
            scanf("%d", &choice);
            
            if(choice == 1) {
                printf("原始分 (%.1f-%.1f): ", sub->min_score, sub->max_score);
                scanf("%f", &grade->raw_score);
                
                // 转换为等级
                grade->grade = convert_to_grade(sub, grade->raw_score);
            } else {
                printf("等级: ");
                scanf(" %c", &grade->grade);
                grade->grade = toupper(grade->grade);
                grade->raw_score = -1; // 原始分未知
            }
        } else {
            printf("分数 (%.1f-%.1f): ", sub->min_score, sub->max_score);
            scanf("%f", &grade->raw_score);
            stu->total += grade->raw_score; // 累加到总分
        }
    }
    
    printf("\n成绩录入完成!\n");
}

// 将分数转换为等级
char convert_to_grade(SubjectConfig *subject, float score) {
	int i = 0;
    for(i = 0; i < subject->grade_count; i++) {
        if(score >= subject->grade_ranges[i].min_score && 
           score <= subject->grade_ranges[i].max_score) {
            return subject->grade_ranges[i].grade;
        }
    }
    return '?'; // 未知等级
}

// 显示所有学生信息
void display_students(GradeSystem *sys) {
    printf("\n===== 学生列表 =====\n");
    printf("%-5s %-10s %-15s %-4s %-4s %-10s\n", 
           "序号", "学号", "姓名", "性别", "年龄", "总分");
    
    int i = 0;
    for(i = 0; i < sys->student_count; i++) {
        Student *stu = &sys->students[i];
        printf("%-5d %-10ld %-15s %-4c %-4d %-10.1f\n", 
               i+1, stu->id, stu->name, stu->sex, stu->age, stu->total);
    }
    
    // 查看详细成绩
    if(sys->student_count > 0) {
        printf("\n输入学生序号查看详细成绩 (0返回): ");
        int index;
        scanf("%d", &index);
        
        if(index > 0 && index <= sys->student_count) {
            Student *stu = &sys->students[index-1];
            printf("\n===== 详细成绩 [%s] =====\n", stu->name);
            printf("%-10s %-10s %-10s\n", "科目", "原始分", "等级");
            
            int i = 0;
            for(i = 0; i < sys->subject_count; i++) {
                SubjectConfig *sub = &sys->subjects[i];
                SubjectGrade *grade = &stu->grades[i];
                
                printf("%-10s ", sub->name);
                
                if(grade->raw_score >= 0) {
                    printf("%-10.1f ", grade->raw_score);
                } else {
                    printf("%-10s ", "N/A");
                }
                
                if(grade->grade != 'N') {
                    printf("%-10c", grade->grade);
                } else {
                    printf("%-10s", "N/A");
                }
                printf("\n");
            }
            printf("总分: %.1f\n", stu->total);
        }
    }
}

// 显示科目设置
void display_subject_config(GradeSystem *sys) {
    printf("\n===== 科目设置 =====\n");
    int i = 0;
    for(i = 0; i < sys->subject_count; i++) {
        SubjectConfig *sub = &sys->subjects[i];
        
        printf("\n科目 %d: %s\n", i+1, sub->name);
        printf("评分类型: %s\n", sub->is_grade_type ? "等级制" : "原始分");
        printf("分数范围: %.1f - %.1f\n", sub->min_score, sub->max_score);
        
        if(sub->is_grade_type) {
            printf("等级分段:\n");
            int j = 0;
            for(j = 0; j < sub->grade_count; j++) {
                printf("  %c: %.1f - %.1f\n", 
                       sub->grade_ranges[j].grade,
                       sub->grade_ranges[j].min_score,
                       sub->grade_ranges[j].max_score);
            }
        }
    }
}

// 保存数据到文件
void save_data(GradeSystem *sys) {
    FILE *file = fopen("grade_system.dat", "wb");
    if(file == NULL) {
        printf("无法保存文件!\n");
        return;
    }
    
    fwrite(sys, sizeof(GradeSystem), 1, file);
    fclose(file);
    printf("数据保存成功!\n");
}

// 从文件加载数据
void load_data(GradeSystem *sys) {
    FILE *file = fopen("grade_system.dat", "rb");
    if(file == NULL) {
        printf("无法加载文件!\n");
        return;
    }
    
    fread(sys, sizeof(GradeSystem), 1, file);
    fclose(file);
    printf("数据加载成功!\n");
}
