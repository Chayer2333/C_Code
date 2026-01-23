#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

// 定义学生结构体
typedef struct {
    int id;
    char name[50];
    float math;
    float chinese;
    float english;
    float total;
    float average;
} Student;

// 全局变量，存储学生数组和学生数量
Student students[MAX_STUDENTS];
int studentCount = 0;

// 函数声明
void enterStudent();
void displayStudents();
void searchStudentById();
void sortStudentsByTotal();
void updateStudentScores();
void statistics();
void exitProgram();
void printMenu();
int compare(const void*, const void*);

// 比较函数，用于qsort
int compare(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return (studentB->total - studentA->total);
}

// 打印菜单
void printMenu() {
    printf("\n学生成绩管理系统\n");
    printf("1. 成绩录入\n");
    printf("2. 成绩显示\n");
    printf("3. 成绩查询\n");
    printf("4. 成绩排序\n");
    printf("5. 成绩修改\n");
    printf("6. 成绩统计\n");
    printf("7. 退出系统\n");
    printf("请选择(1-7): ");
}

// 录入学生信息
void enterStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("学生数量已达到上限。\n");
        return;
    }
    printf("输入学生学号: ");
    scanf("%d", &(students[studentCount].id));
    getchar(); // 清除缓冲区的换行符
    printf("输入学生姓名: ");
    scanf("%s", students[studentCount].name);
    printf("输入数学成绩: ");
    scanf("%f", &(students[studentCount].math));
    printf("输入语文成绩: ");
    scanf("%f", &(students[studentCount].chinese));
    printf("输入英语成绩: ");
    scanf("%f", &(students[studentCount].english));
    students[studentCount].total = students[studentCount].math + students[studentCount].chinese + students[studentCount].english;
    students[studentCount].average = students[studentCount].total / 3;
    studentCount++;
    printf("成绩录入成功。\n");
}

// 显示所有学生信息
void displayStudents() {
    if (studentCount == 0) {
        printf("没有学生信息。\n");
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        printf("学号: %d\n", students[i].id);
        printf("数学: %.2f\n", students[i].math);
        printf("语文: %.2f\n", students[i].chinese);
        printf("英语: %.2f\n", students[i].english);
        printf("总分: %.2f\n", students[i].total);
        printf("平均分: %.2f\n", students[i].average);
        printf("---------\n");
    }
}

// 按学号查询学生信息
void searchStudentById() {
    int id;
    printf("输入要查询的学生学号: ");
    scanf("%d", &id);
    int found = 0; // 标记是否找到学生
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("找到学生信息：\n");
            printf("学号: %d\n", students[i].id);
            printf("姓名: %s\n", students[i].name);
            printf("数学: %.2f\n", students[i].math);
            printf("语文: %.2f\n", students[i].chinese);
            printf("英语: %.2f\n", students[i].english);
            printf("总分: %.2f\n", students[i].total);
            printf("平均分: %.2f\n", students[i].average);
            break; // 找到学生后退出循环
        }
    }
    if (!found) {
        printf("未找到学号为 %d 的学生。\n", id);
    }
}

// 按总分对学生信息进行排序
void sortStudentsByTotal() {
    qsort(students, studentCount, sizeof(Student), compare);
    printf("学生成绩已按总分排序。\n");
    displayStudents();
}

// 修改学生成绩
void updateStudentScores() {
    int id;
    printf("输入要修改成绩的学生学号: ");
    scanf("%d", &id);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("输入新的数学成绩: ");
            scanf("%f", &(students[i].math));
            printf("输入新的语文成绩: ");
            scanf("%f", &(students[i].chinese));
            printf("输入新的英语成绩: ");
            scanf("%f", &(students[i].english));
            students[i].total = students[i].math + students[i].chinese + students[i].english;
            students[i].average = students[i].total / 3;
            printf("成绩修改成功。\n");
            return;
        }
    }
    printf("未找到学号为 %d 的学生。\n", id);
}

// 统计学生成绩
void statistics() {
    // 这里只展示统计每门课程平均成绩的代码，其他统计项类似
float courseAverage[3] = {0};
for (int i = 0; i < studentCount; i++) {
        courseAverage[0] += students[i].math;
        courseAverage[1] += students[i].chinese;
        courseAverage[2] += students[i].english;
    }
    for (int i = 0; i < 3; i++) {
        courseAverage[i] /= studentCount;
        printf("%s课程的平均成绩是: %.2f\n", i == 0 ? "数学" : (i == 1 ? "语文" : "英语"), courseAverage[i]);
    }
}

// 退出程序
void exitProgram() {
    printf("退出系统。\n");
    exit(0);
}

int main() {
    int choice;
    do {
        printMenu();
        scanf("%d", &choice);
        while (getchar() != '\n'); // 清除缓冲区的换行符
        switch (choice) {
            case 1: enterStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudentById(); break;
            case 4: sortStudentsByTotal(); break;
            case 5: updateStudentScores(); break;
            case 6: statistics(); break;
            case 7: exitProgram(); break;
            default: printf("无效的选项，请重新选择。\n");
        }
    } while (choice != 7);
    return 0;
}

