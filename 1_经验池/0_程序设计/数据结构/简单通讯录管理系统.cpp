#include <stdio.h>
#include <cstdlib>      // 包含system(),rand(),srand()函数的头文件
#include <ctime>        // 用于设置随机种子
#include <stdlib.h>     // 需要包含malloc的头文件
#include <iostream>     // c++库.是IO的库
#include <stdbool.h>    // bool
#include <string.h>     // 字符串操作
#include <ctype.h>      // 字符类型判断

using namespace std;    // 调用标准(std)命名空间

// 常量定义
#define NAME_LEN 20		// 姓名的最大长度
#define PLACE_LEN 30	// 籍贯的最大长度
#define PHONE_LEN 15	// 电话号码的最大长度
#define MAX_STUDENTS 100// 学生数据最大容量 
#define MIN_AGE 1		// 年龄最小值
#define MAX_AGE 120		// 年龄最大值
#define MIN_HEIGHT 50	// 身高最小值（厘米）
#define MAX_HEIGHT 250	// 身高最大值（厘米）


typedef struct
{	// 数据结构体设计
    long long id;                    	// 学号
    char name[NAME_LEN];        	// 姓名
    int age;                    	// 年龄
    char native_place[PLACE_LEN]; 	// 籍贯
    float height;              		// 身高
    char landline[PHONE_LEN];   	// 固定电话
} Student;


typedef struct LNode 
{	// 单链表节点定义
    Student data;
    struct LNode *next;
} LinkNode;


// 函数声明
void Menu();                                          // 主控制面板
void SearchMenu();                                    // 查询菜单

void InitList(LinkNode *&L);                          // 创建空表
void DestroyList(LinkNode *&L);                       // 销毁表

bool IsEmpty(LinkNode *&L);                           // 判断是否为空
int ListLength(LinkNode *L);                          // 返回表长度

void ShowTitle();                                     // 显示表头
void ShowData(Student stud);                          // 显示一条记录
void DispList(LinkNode *L);                           // 显示全部记录

void CreateList(LinkNode *&L);                        // 初始化输入记录
void InRecordData(Student &e);                        // 输入一条记录数据
bool ListInsert(LinkNode *&L);                        // 插入通讯录记录
bool ListDelete(LinkNode *&L);                        // 删除通讯录记录
bool Search(LinkNode *L);                             // 查询通讯录记录
bool Modify(LinkNode *&L);                            // 修改通讯录记录

void SaveToFile(LinkNode *L);                         // 保存到文件
void LoadFromFile(LinkNode *&L);                      // 从文件加载

bool ValidateID(long long id, LinkNode *L, LinkNode *exclude = NULL); // 验证学号唯一性
bool ValidateName(const char *name);                             // 验证姓名
bool ValidatePhone(const char *phone);                           // 验证电话号码
bool ValidateAge(int age);                                       // 验证年龄
bool ValidateHeight(float height);                               // 验证身高

int  input(char c);                                   // sys选择
bool Input(const char *s, int *n);                    // 整型验证
bool InputLong(const char *s, long long *n);               // 长整型验证
bool InputFloat(const char *s, float *n);             // 浮点型验证
void clearInputBuffer();                              // 清除缓冲区
void trimString(char *str);                           // 去除字符串首尾空格

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 主函数 **

int main()
{
    int choice=0;
    char c='N';
    LinkNode *L;            // 通讯录链表
    InitList(L);
    LoadFromFile(L);        // 启动时加载数据
    cout<<"\n确认退出系统吗？(Y/N): ";
    cin>>c;
    clearInputBuffer();
    if(c=='Y' || c=='y') {
    	cout<<"\n系统已退出。\n";
    	return 0;
	}
    
    do
    {
        choice=0; 
        c='N'; 
        Menu();
        cin>>c;
        choice=input(c);
        clearInputBuffer();
        
        switch(choice)
        {
            case 0: {       // ** 退出系统 **
            	c='N';
                cout<<"\n确认退出系统吗？(Y/N): ";
                c=getchar();
                clearInputBuffer();
                
                if(c=='Y' || c=='y')
                {
                    SaveToFile(L);
                    DestroyList(L);
                    cout<<"\n数据已保存。\n";
                    cout<<"\n系统已退出。\n";
                }
                break;
            }
            
            case 1: {       // ** 初始化输入记录 **
                CreateList(L);
                break;
            }
            
            case 2: {       // ** 插入通讯录记录 **
                ListInsert(L);
                break;
            }
            
            case 3: {       // ** 删除通讯录记录 **
                ListDelete(L);
                break;
            }
            
            case 4: {       // ** 查询通讯录记录 **
                Search(L);
                break;
            }
            
            case 5: {       // ** 修改通讯录记录 **
                Modify(L);
                break;
            }
            
            case 6: {       // ** 显示通讯录记录 **
                DispList(L);
                break;
            }
            
            default: 
                cout<<"\n---- 输入错误! 请输入0~6之间的数字 ----\n";
        }
        
        if(choice!=0) {
            cout<<"\n\n按任意键继续....";
            getchar();
        }
    } while(choice!=0);
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 控制面板 **

void Menu()
{
    system("cls");
    cout<<"************************************************************\n";
    cout<<"   * * * * * * * * * * 通讯录管理系统 * * * * * * * * * *\n";
    cout<<"************************************************************\n";
    cout<<"                    1、初始化输入记录                    \n";
    cout<<"                    2、插入通讯录记录                    \n";
    cout<<"                    3、删除通讯录记录                    \n";
    cout<<"                    4、查询通讯录记录                    \n";
    cout<<"                    5、修改通讯录记录                    \n";
    cout<<"                    6、显示通讯录记录                    \n";
    cout<<"                    0、退出通讯录系统                    \n";
    cout<<"************************************************************\n";
    cout<<"请输入你的菜单选择编号（0~6）：";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 显示表头 **

void ShowTitle()
{
    cout<<"\n====================================================================================================\n";
    cout<<"学号\t\t姓名\t\t年龄\t籍贯\t\t身高\t固定电话\n";
    cout<<"====================================================================================================\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 显示一条记录 **

void ShowData(Student stud)
{
    printf("%lld \t %-8s \t %d \t %-12s\t %.1f \t %s\n", 
           stud.id, stud.name, stud.age, stud.native_place, stud.height, stud.landline);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 显示全部记录 **

void DispList(LinkNode *L)
{
    if(IsEmpty(L))
    {
        cout<<"\n通讯录为空，没有记录可显示。\n";
        return;
    }
    
    cout<<"\n===== 通讯录所有记录 =====\n";
    cout<<"共有 "<<ListLength(L)<<" 条记录\n";
    
    ShowTitle();
    LinkNode *p=L->next;
    int count=1;
    
    while(p!=NULL)
    {
        ShowData(p->data);
        p=p->next;
        count++;
    }
    cout<<"\n====================================================================================================\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 创建空表 **

void InitList(LinkNode *&L)
{
    L = (LinkNode *)malloc(sizeof(LinkNode));
    if (L==NULL) {
        cout<<"内存分配失败！系统无法启动。\n";
    }
    L->next=NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 销毁表 **

void DestroyList(LinkNode *&L)
{
    if(L==NULL) return;
    
    LinkNode *p=L;
    LinkNode *q;
    
    while(p!=NULL)
    {
        q=p->next;
        free(p);
        p=q;
    }
    L=NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 判断是否为空 **

bool IsEmpty(LinkNode *&L)
{
    if (L==NULL) return true;
    return(L->next==NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 返回表长度 **

int ListLength(LinkNode *L)
{
    if (L==NULL) return 0;
    
    int n=0;
    LinkNode *p=L->next;
    
    while(p!=NULL)
    {
        n++;
        p=p->next;
    }
    
    return n;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 初始化输入记录（批量增加） **

void CreateList(LinkNode *&L)
{
    int n;
    char c;
    
    cout<<"\n===== 初始化输入记录 =====\n";
    
    // 检查是否已有记录
    if (!IsEmpty(L)) {
        cout<<"通讯录中已有记录，是否清空后重新输入？(Y/N): ";
        c=getchar();
        clearInputBuffer();
        
        if (c!='Y' && c!='y') {
            cout<<"操作已取消。\n";
            return;
        }
        
        // 清空现有记录
        DestroyList(L);
        InitList(L);
    }
    
    // 输入要创建的学生数量
    while (1) {
        if (!Input("请输入要创建的学生数量(1-100): ", &n)) {
            return;
        }
        
        if (n<1 || n>MAX_STUDENTS) {
            cout<<"数量必须在1到"<<MAX_STUDENTS<<"之间！\n";
            continue;
        }
        break;
    }
    
    // 批量输入学生信息
    for (int i=0; i<n; i++) {
        cout<<"\n--- 输入第 "<<i+1<<" 个学生信息 ---\n";
        LinkNode *newNode, *p;
        
        newNode=(LinkNode *)malloc(sizeof(LinkNode));
        if(newNode==NULL) {
            cout<<"内存分配失败！\n";
            return;
        }
        
        InRecordData(newNode->data);
        
        // 验证学号唯一性
        if (!ValidateID(newNode->data.id, L, NULL)) {
            cout<<"错误：学号 "<<newNode->data.id<<" 已存在！请重新输入。\n";
            free(newNode);
            i--; // 重新输入
            continue;
        }
        
        // 找到链表末尾
        p=L;
        while(p->next!=NULL) {
            p=p->next;
        }
        
        // 插入到末尾
        p->next=newNode;
        newNode->next=NULL;
    }
    
    cout<<"\n成功创建 "<<n<<" 条记录！\n";
    
    // 显示所有记录
    cout<<"\n创建后的通讯录记录：\n";
    DispList(L);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 输入一条记录数据 **

void InRecordData(Student &e)
{
    // 学号
    while(1) {
        if(!InputLong("学号(正整数): ", &e.id))
            continue;
        
        if(e.id<=0) {
            cout<<"学号必须为正整数！\n";
            continue;
        }
        break;
    }
    
    // 姓名
    while(1) {
        cout<<"姓名: ";
        fgets(e.name, NAME_LEN, stdin);
        e.name[strcspn(e.name, "\n")]='\0';
        trimString(e.name);
        
        if (strlen(e.name) == 0) {
            cout<<"姓名不能为空！\n";
            continue;
        }
        break;
    }
    
    // 年龄
    while(1) {
        if(!Input("年龄: ", &e.age))
            continue;
        
        if(e.age<MIN_AGE || e.age>MAX_AGE) {
            cout<<"年龄必须在"<<MIN_AGE<<"到"<<MAX_AGE<<"岁之间！\n";
            continue;
        }
        break;
    }
    
    // 籍贯
    cout<<"籍贯: ";
    fgets(e.native_place, PLACE_LEN, stdin);
    e.native_place[strcspn(e.native_place, "\n")]='\0';
    trimString(e.native_place);
    
    // 身高
    while(1) {
        if(!InputFloat("身高(cm): ", &e.height))
            continue;
        
        if(e.height<MIN_HEIGHT || e.height>MAX_HEIGHT) {
            cout<<"身高必须在"<<MIN_HEIGHT<<"到"<<MAX_HEIGHT<<"厘米之间！\n";
            continue;
        }
        break;
    }
    
    // 固定电话
    while(1) {
        cout<<"固定电话: ";
        fgets(e.landline, PHONE_LEN, stdin);
        e.landline[strcspn(e.landline, "\n")]='\0';
        trimString(e.landline);
        
        int len=strlen(e.landline);
        int digitCount=0;
        bool valid=true;
        
        for (int i=0; i<len; i++) {
            if (isdigit(e.landline[i])) {
                digitCount++;
            } else if (e.landline[i]!='-' && e.landline[i]!=' ' && 
                      e.landline[i]!='(' && e.landline[i]!=')') {
                valid=false;
                break;
            }
        }
        
        if (!valid) {
            cout<<"电话号码只能包含数字、空格、括号和横线！\n";
            continue;
        }
        
        if (digitCount<7) {
            cout<<"电话号码至少需要7位数字！\n";
            continue;
        }
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 插入通讯录记录 **

bool ListInsert(LinkNode *&L)
{
    int pos;
    char prompt[100];
    
    int listLen=ListLength(L);
    
    if (listLen==0) {
        cout<<"\n当前通讯录为空，将插入为第一条记录。\n";
        pos=1;
    } else {
        sprintf(prompt, "\n请输入插入位置(1-%d): ", listLen+1);
        if(!Input(prompt, &pos))
            return false;
        
        if(pos<1 || pos>listLen+1) {
            cout<<"插入位置无效！\n";
            return false;
        }
    }
    
    LinkNode *newNode, *p=L;
    
    newNode=(LinkNode *)malloc(sizeof(LinkNode));
    if(newNode==NULL) {
        cout<<"内存分配失败！\n";
        return false;
    }
    
    cout<<"\n请输入要插入的学生信息：\n";
    InRecordData(newNode->data);
    
    // 验证学号唯一性
    if (!ValidateID(newNode->data.id, L, NULL)) {
        cout<<"错误：学号 "<<newNode->data.id<<" 已存在！\n";
        free(newNode);
        return false;
    }
    
    // 找到插入位置的前一个节点
    for(int i=0; i<pos-1; i++) {
        p=p->next;
    }
    
    // 插入节点
    newNode->next=p->next;
    p->next=newNode;
    
    cout<<"\n记录插入成功！\n";
    
    // 显示插入后的所有记录
    cout<<"\n插入后的通讯录记录：\n";
    DispList(L);
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 删除通讯录记录 **

bool ListDelete(LinkNode *&L)
{
    long long id;
    char c;
    
    if(IsEmpty(L)) {
        cout<<"\n通讯录为空，没有记录可删除。\n";
        return false;
    }
    
    if(!InputLong("\n请输入要删除的学生学号: ", &id))
        return false;
    
    LinkNode *p=L, *q;
    
    // 查找要删除的节点
    while(p->next!=NULL && p->next->data.id!=id) {
        p=p->next;
    }
    
    if(p->next==NULL) {
        cout<<"\n未找到学号为 "<<555<<" 的学生。\n";
        return false;
    }
    
    // 显示要删除的记录
    cout<<"\n找到以下记录：\n";
    ShowTitle();
    ShowData(p->next->data);
    cout<<"\n====================================================================================================\n";
    
    cout<<"\n确认删除该记录？(Y/N): ";
    c=getchar();
    clearInputBuffer();
    
    if(c=='Y' || c=='y') {
        q=p->next;
        p->next=q->next;
        free(q);
        cout<<"\n记录删除成功！\n";
        
        // 显示删除后的所有记录
        cout<<"\n删除后的通讯录记录：\n";
        DispList(L);
        return true;
    } else {
        cout<<"\n删除操作已取消。\n";
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 查询通讯录记录 **

bool Search(LinkNode *L)
{
    long long id;
    
    if(IsEmpty(L)) {
        cout<<"\n通讯录为空，没有记录可查询。\n";
        return false;
    }
    
    if(!InputLong("\n请输入要查询的学生学号: ", &id))
        return false;
    
    LinkNode *p=L->next;
    bool found=false;
    
    while(p!=NULL) {
        if(p->data.id==id) {
            cout<<"\n查询结果：\n";
            ShowTitle();
            ShowData(p->data);
    cout<<"\n====================================================================================================\n";
            found=true;
            break;
        }
        p = p->next;
    }
    
    if(!found) {
        cout<<"\n没有查找到学号为 "<<id<<" 的记录！\n";
        return false;
    }
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 修改通讯录记录 **

bool Modify(LinkNode *&L)
{
    long long id;
    char c;
    
    if(IsEmpty(L)) {
        cout<<"\n通讯录为空，没有记录可修改。\n";
        return false;
    }
    
    if(!InputLong("\n请输入要修改的学生学号: ", &id))
        return false;
    
    // 查找要修改的节点
    LinkNode *p=L->next;
    while(p!=NULL && p->data.id!=id) {
        p=p->next;
    }
    
    if(p==NULL) {
        cout<<"\n没有查找到学号为 "<<id<<" 的记录！\n";
        return false;
    }
    
    // 显示原记录
    cout<<"\n原记录信息：\n";
    ShowTitle();
    ShowData(p->data);
    cout<<"\n====================================================================================================\n";
    
    cout<<"\n请输入新的信息：\n";
    
    // 动态分配缓冲区存储新输入的数据
    Student *temp=(Student *)malloc(sizeof(Student));
    if (temp==NULL) {
        cout<<"\n内存分配失败！\n";
        return false;
    }
    
    // 保存原学号
    long old_id=p->data.id;
    
    // 输入新信息到缓冲区
    while(1) {
        // 学号
        if(!InputLong("学号(正整数): ", &temp->id)) {
            free(temp);
            continue;
        }
        
        if(temp->id<=0) {
            cout<<"学号必须为正整数！\n";
            continue;
        }
        
        // 如果学号被修改，验证新学号的唯一性（排除当前节点）
        if (temp->id!=old_id && !ValidateID(temp->id, L, p)) {
            cout<<"错误：学号 "<<temp->id<<" 已存在！\n";
            continue;
        }
        break;
    }
    
    // 姓名
    while(1) {
        cout << "姓名: ";
        fgets(temp->name, NAME_LEN, stdin);
        temp->name[strcspn(temp->name, "\n")]='\0';
        trimString(temp->name);
        
        if (strlen(temp->name)==0) {
            cout<<"姓名不能为空！\n";
            continue;
        }
        break;
    }
    
    // 年龄
    while(1) {
        if(!Input("年龄: ", &temp->age)) {
            free(temp);
            continue;
        }
        
        if(temp->age<MIN_AGE || temp->age>MAX_AGE) {
            cout<<"年龄必须在"<<MIN_AGE<<"到"<<MAX_AGE<<"岁之间！\n";
            continue;
        }
        break;
    }
    
    // 籍贯
    cout << "籍贯: ";
    fgets(temp->native_place, PLACE_LEN, stdin);
    temp->native_place[strcspn(temp->native_place, "\n")] = '\0';
    trimString(temp->native_place);
    
    // 身高
    while(1) {
        if(!InputFloat("身高(cm): ", &temp->height)) {
            free(temp);
            continue;
        }
        
        if(temp->height<MIN_HEIGHT || temp->height>MAX_HEIGHT) {
            cout<<"身高必须在"<<MIN_HEIGHT<<"到"<<MAX_HEIGHT<<"厘米之间！\n";
            continue;
        }
        break;
    }
    
    // 固定电话
    while(1) {
        cout << "固定电话: ";
        fgets(temp->landline, PHONE_LEN, stdin);
        temp->landline[strcspn(temp->landline, "\n")]='\0';
        trimString(temp->landline);
        
        int len=strlen(temp->landline);
        int digitCount=0;
        bool valid=true;
        
        for (int i=0; i<len; i++) {
            if (isdigit(temp->landline[i])) {
                digitCount++;
            } else if (temp->landline[i]!='-' && temp->landline[i]!=' ' && 
                      temp->landline[i]!='(' && temp->landline[i]!=')') {
                valid=false;
                break;
            }
        }
        
        if (!valid) {
            cout<<"电话号码只能包含数字、空格、括号和横线！\n";
            continue;
        }
        
        if (digitCount<7) {
            cout<<"电话号码至少需要7位数字！\n";
            continue;
        }
        break;
    }
    
    // 显示原记录和新记录对比
    cout<<"\n====================================================================================================\n";
    cout<<"原记录信息：\n";
    ShowTitle();
    ShowData(p->data);
    cout<<"\n新记录信息：\n";
    ShowTitle();
    ShowData(*temp);
    cout<<"\n====================================================================================================\n";
    
    // 确认是否修改
    cout<<"\n确认修改吗？(Y/N): ";
    c=getchar();
    clearInputBuffer();
    
    if(c=='Y' || c=='y') {
        memcpy(&p->data, temp, sizeof(Student));
        free(temp);  // 释放临时缓冲区
        
        cout<<"\n记录修改成功！\n";
        
        cout<<"\n修改后的通讯录记录：\n";
        DispList(L);
        
        return true;
    } else {
        cout<<"\n修改操作已取消，原记录保持不变。\n";
        free(temp);  // 释放临时缓冲区
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 验证学号唯一性 **

bool ValidateID(long long id, LinkNode *L, LinkNode *exclude)
{
    LinkNode *p=L->next;
    
    while(p!=NULL) {
        // 跳过要排除的节点（用于修改操作）
        if(exclude!=NULL && p==exclude) {
            p=p->next;
            continue;
        }
        
        if(p->data.id==id) {
            return false; // 学号已存在
        }
        p=p->next;
    }
    
    return true; // 学号唯一
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 保存到文件 **

void SaveToFile(LinkNode *L)
{
    FILE *fp;
    LinkNode *p=L->next;
    
    fp=fopen("contacts.dat", "wb");
    if(fp==NULL) {
        cout<<"\n无法创建文件！\n";
        return;
    }
    
    // 先写入记录数量
    int count=ListLength(L);
    fwrite(&count, sizeof(int), 1, fp);
    
    // 写入每条记录
    while(p!=NULL) {
        fwrite(&p->data, sizeof(Student), 1, fp);
        p=p->next;
    }
    
    fclose(fp);
    cout<<"\n成功保存 "<<count<<" 条记录到文件。\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 从文件加载 **

void LoadFromFile(LinkNode *&L)
{
    FILE *fp;
    int count, i;
    
    fp=fopen("contacts.dat", "rb");
    if(fp==NULL) {
        cout<<"\n无法打开文件！文件可能不存在。\n";
        return;
    }
    
    // 读取记录数量
    fread(&count, sizeof(int), 1, fp);
    
    if(count<=0 || count>MAX_STUDENTS) {
        cout<<"\n文件损坏：无效的记录数量 "<<count<<"\n";
        fclose(fp);
        return;
    }
    
    // 读取每条记录并添加到链表
    for(i=0; i<count; i++) {
        LinkNode *newNode, *p;
        
        newNode=(LinkNode *)malloc(sizeof(LinkNode));
        if(newNode==NULL) {
            cout<<"内存分配失败！\n";
            fclose(fp);
            return;
        }
        
        fread(&newNode->data, sizeof(Student), 1, fp);
        newNode->next=NULL;
        
        // 验证读取的数据
        if (newNode->data.id<=0) {
            cout<<"文件损坏：检测到无效学号\n";
            free(newNode);
            continue;
        }
        
        p=L;
        while(p->next!=NULL) {
            p=p->next;
        }
        
        p->next=newNode;
    }
    
    fclose(fp);
    cout<<"\n成功加载 "<<count<<" 条记录。\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** sys选择验证 **

int input(char c)
{
    if('0'<=c && '9'>=c) 
        return c-'0';
    else 
        return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 整型输入验证 **

bool Input(const char *s, int *n)
{
    if(s) cout<<s;
    if(scanf("%d", n)!=1) {
        cout<<"\n输入错误！请输入整数。\n";
        clearInputBuffer();
        return false;
    }
    clearInputBuffer();
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 长整型输入验证 **

bool InputLong(const char *s, long long *n)
{
    if(s) cout<<s;
    if(scanf("%lld", n)!=1) {
        cout<<"\n输入错误！请输入整数。\n";
        clearInputBuffer();
        return false;
    }
    clearInputBuffer();
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 浮点型输入验证 **

bool InputFloat(const char *s, float *n)
{
    if(s) cout<<s;
    if(scanf("%f", n)!=1) {
        cout<<"\n输入错误！请输入数字。\n";
        clearInputBuffer();
        return false;
    }
    clearInputBuffer();
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 清除缓冲区 **

void clearInputBuffer()
{
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 去除字符串首尾空格 **

void trimString(char *str)
{
    if (str==NULL) return;
    
    int len=strlen(str);
    int start=0, end=len-1;
    
    // 找到第一个非空格字符
    while(start<len && isspace(str[start])) {
        start++;
    }
    
    // 找到最后一个非空格字符
    while(end>=0 && isspace(str[end])) {
        end--;
    }
    
    if(start>end) {
        str[0]='\0';
        return;
    }
    
    // 移动字符串
    int i;
    for(i=0; i<=end-start; i++) {
        str[i]=str[start+i];
    }
    str[i]='\0';
}
