#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
struct stu
{
	char ID[20];  //学号
	char name[20];  //姓名
	int Chinese; //语文成绩
	int Math;  //数学成绩
	int English;  //英语成绩
	int Computer;  //计算机成绩
	float all;  //总成绩
	float aver;  //平均成绩 
 } student[500];
 int number=0;
 
 void input()//输入学生信息 
 {
 	while(1)
 	{
 		printf("输入学生学号:");
 		scanf("%s",student[number].ID);
 		printf("输入学生姓名:");
 		scanf("%s",student[number].name);
 		printf("输入学生语文成绩:");
 		scanf("%d",&student[number].Chinese);
 		printf("输入学生数学成绩:");
 		scanf("%d",&student[number].Math);
 		printf("输入学生英语成绩:");
 		scanf("%d",&student[number].English );
 		printf("输入学生计算机成绩:");
 		scanf("%d",&student[number].Computer);
 		getchar();
		 student[number].all = student[number].Chinese + student[number].Computer + student[number].English + student[number].Math ;
		 student[number].aver = student[number].all/4;
		 number++;
		printf("成绩录入成功。\n");
		 printf("是否继续(y/n)\n");
		 if(getchar()=='n'){
		 	break;
		 } 
	 }
	 
 }
 
 int stu_id(char ID[])//由学号查找学生信息 
 {
 	int i;
 	for(i=0;i<number;i++)
 	{
 		if(strcmp(student[i].ID,ID)==0)
 		return i;
	 }
 	return -1;//错误数据 
 }
 
 int stu_name(char name[])//由姓名查找学生信息 
 {
 	int i;
 	for(i=0;i<number;i++)
 	{
 		if(strcmp(student[i].name ,name)==0)
 		return i;
	 }
 	return -1;//错误数据 
 }
 
 int modify()//修改学生数据
 {
 	while(1)
 	{
 		char ID[50];
 		int id;
 		printf("输入想要修改的学生数据");
 		scanf("%s",ID);
		getchar();
		id = stu_id(ID);
		{
        if (id == -1)
        {
            printf("未找到该学生！\n");
        }
        else
		{
		printf("--*输入新的数据*--");
		printf("输入学生学号:");
 		scanf("%s",student[number].ID);
 		printf("输入学生姓名:");
 		scanf("%s",student[number].name);
 		printf("输入学生语文成绩:");
 		scanf("%d",&student[number].Chinese);
 		printf("输入学生数学成绩:");
 		scanf("%d",&student[number].Math);
 		printf("输入学生英语成绩:");
 		scanf("%d",&student[number].English );
 		printf("输入学生计算机成绩:");
 		scanf("%d",&student[number].Computer);
 		getchar();
		 student[number].all = student[number].Chinese + student[number].Computer + student[number].English + student[number].Math ;
		 student[number].aver = student[number].all/4;
		printf("成绩录入成功。\n");
		 printf("是否继续(y/n)\n");
		 if(getchar()=='n')
		 	break; 
	    }
  } 
}
  
// int deleted()//删除学生数据 
//{
// 	while(1)
// 	{
// 		
//	 }
//  } 
//  
// int insert()//插入学生成绩 
//  {
// 	while(1)
// 	{
// 		
//	 }
//  } 
  
void output()//输出学生成绩 
{ 
    int i;
	printf("%10s%10s%10s%10s%10s  %10s%10s%10s\n","学号","姓名","语文","数学","英语","计算机","总成绩","平均成绩");
	printf("------------------------------------------------------------------------------------------------------------\n") ;
	for(i=0;i<number;i++)
		printf("%10s%10s%10d%10d%10d%10d   %10.2f%10.2f\n",
				student[i].ID,student[i].name ,
				student[i].Chinese ,
				student[i].Math,
				student[i].English,
				student[i].Computer,
				student[i].all,student[i].aver);
}

//int query()//查询学生成绩 
// {
// 	while(1)
// 	{
// 		
//	 }
//  } 
//  
//int ordering()//学生总分查询 
// {
// 	while(1)
// 	{
// 		
//	 }
//  } 
//  
//int fail()//输出不及格学生 
// {
// 	while(1)
// 	{
// 		
//	 }
//  } 
//  
//int highest()//输出最高成绩 
// {
// 	while(1)
// 	{
// 		
//	 }
//  } 
//  
int exit_()//退出系统
{
 	printf("退出系统。\n");
    exit(0);
  } 
   
  
int main()//主界面 
{
	int i,j;
	while(1){
	const char *logo[] = {
    "     WW      WW   YY         YY",
    "     WW      WW    YY       YY",
    "     WW      WW     YY     YY",
    "     WW  WW  WW      YY   YY",
    "     WW  WW  WW       YY YY",
    "     WW WWWW WW        YYY",
    "     WWW    WWW         Y",
    "     WW      WW         Y",
    "     WW      WW         Y",
    "     WW      WW         Y"
}
    //名字logo 
    for (int j = 0; j < 10; j++) {
        printf("%s\n", logo[j]);
    }
		printf("------**学生成绩管理系统**------\n");
		printf("      1.输入学生数据\n"); 
		printf("      2.修改学生数据\n");
		printf("      3.删除学生数据\n");
		printf("      4.插入学生数据\n");
		printf("      5.输出学生数据\n");
		printf("      6.查询学生数据\n");;
		printf("      7.学生总分查询\n");
		printf("      8.输出各科不及格的学生\n");;
		printf("      9.输出各科最高分\n");
		printf("      0.退出管理系统\n");
		printf("请选择(0~9)  ");
		scanf("%d",&i); 
	
	switch(i){
		case 1:input();break;
		case 2:modify();break;
		case 3:deleted();break;
		case 4:insert();break;
		case 5:output();break;
		case 6:query();break;
		case 7:ordering();break;
		case 8:fail();break;
		case 9:highest();break;
		case 0:exit_();break;
	    }
}
	return 0;
}
