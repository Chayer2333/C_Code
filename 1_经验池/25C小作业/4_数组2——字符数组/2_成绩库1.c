#include <stdio.h>
#include <string.h>
#define N 10 

struct student 
{
    long int num;
    char name[20];
    char sex;       // 男：M 女：F 
    short int age;
    float Chinese;
    float Maths;
    float English;
    float sum; 
};

void print(struct student *stud);

int main() {
    struct student stnum[N];
    struct student *p=stnum;
	int i=0;
    printf("请按如下格式录入学生信息：学号,姓名,性别(M/F),年龄,大学语文,高等数学,英语\n");
    for (i=0;i<N;i++) 
	{
        printf("请输入第 %d 个学生的信息:\n",i+1);
        scanf("%ld,%19[^,],%c,%hd,%f,%f,%f",
              &(p[i].num),
                p[i].name,
              &(p[i].sex),
              &(p[i].age),
              &(p[i].Chinese),
              &(p[i].Maths),
              &(p[i].English));

        p[i].sum=p[i].Chinese+p[i].Maths+p[i].English;
    }

    for (p=stnum;p<stnum+N;p++)
    	print(p);

    return 0;
}

void print(struct student *stud) 
{
    printf("\nNO.%ld\n 姓名:%s\n 性别:%c\n 年龄:%d\n 语数英成绩:%5.1f,%5.1f,%5.1f\n 总成绩:%.1f\n\n",
           stud->num,
           stud->name,
           stud->sex,
           stud->age,
           stud->Chinese,
           stud->Maths,
           stud->English,
           stud->sum);
}
