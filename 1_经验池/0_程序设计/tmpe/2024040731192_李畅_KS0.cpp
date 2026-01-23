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
#define NAME_LEN 20
#define PLACE_LEN 30
#define PHONE_LEN 15
#define MAX_STUDENTS 100

// 数据结构体设计
typedef struct
{
    long id;                    // 学号
    char name[NAME_LEN];        // 姓名
    int age;                    // 年龄
    char native_place[PLACE_LEN]; // 籍贯
    float height;               // 身高（自选信息）
    char landline[PHONE_LEN];   // 固定电话
} Student;

// 单链表节点定义
typedef struct LNode 
{
    Student data;               // 学生数据
    struct LNode *next;
} LinkNode;

// 函数声明
void Menu();                                           // 主控制面板
void SearchMenu();                                     // 查询菜单
void SaveMenu();                                       // 保存菜单

void InitList(LinkNode *&L);                          // 创建空表
void DestroyList(LinkNode *&L);                       // 销毁表

bool IsEmpty(LinkNode *&L);                           // 判断是否为空
int ListLength(LinkNode *L);                          // 返回表长度

void DisplayRecord(Student stud);                     // 显示一条记录
void DisplayAllRecords(LinkNode *L);                  // 显示所有记录

void AddRecord(LinkNode *&L);                         // 增加记录
void InsertRecord(LinkNode *&L);                      // 插入记录
void DeleteRecord(LinkNode *&L);                      // 删除记录
void QueryRecord(LinkNode *L);                        // 查询记录
void ModifyRecord(LinkNode *&L);                      // 修改记录

void SaveToFile(LinkNode *L);                         // 保存到文件
void LoadFromFile(LinkNode *&L);                      // 从文件加载

bool InputStudent(Student *stud, LinkNode *L, LinkNode *exclude = NULL);  // 输入学生信息
bool ValidateID(long id, LinkNode *L, LinkNode *exclude = NULL);          // 验证学号唯一性

int input(char c);                                    // sys选择
bool Input(const char *s, int *n);                    // 整型验证
bool InputLong(const char *s, long *n);               // 长整型验证
bool InputFloat(const char *s, float *n);             // 浮点型验证
void clearInputBuffer();                              // 清除缓冲区

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 主函数 **

int main()
{
    int choice = 0;
    char c = 'N';
    LinkNode *L;            // 通讯录链表
    InitList(L);
    
    LoadFromFile(L);        // 启动时加载数据
    
    do
    {
        choice = 0; 
        c = 'N'; 
        Menu();
        cin >> c;
        choice = input(c);
        clearInputBuffer();
        
        switch(choice)
        {
            case 0: {       // ** 退出系统 **
                char confirm;
                cout << "\n确认退出系统吗？(Y/N): ";
                confirm = getchar();
                clearInputBuffer();
                
                if(confirm == 'Y' || confirm == 'y')
                {
                    SaveToFile(L);
                    DestroyList(L);
                    cout << "\n数据已保存。\n";
                    cout << "\n系统已退出。\n";
                }
                else
                {
                    choice = 1; // 继续循环
                }
                break;
            }
            
            case 1: {       // ** 增加记录 **
                AddRecord(L);
                break;
            }
            
            case 2: {       // ** 插入记录 **
                InsertRecord(L);
                break;
            }
            
            case 3: {       // ** 删除记录 **
                DeleteRecord(L);
                break;
            }
            
            case 4: {       // ** 查询系统 **
                QueryRecord(L);
                break;
            }
            
            case 5: {       // ** 修改记录 **
                ModifyRecord(L);
                break;
            }
            
            case 6: {       // ** 显示所有记录 **
                DisplayAllRecords(L);
                break;
            }
            
            case 7: {       // ** 数据管理 **
                SaveToFile(L);
                break;
            }
            
            default: 
                cout << "\n---- 输入错误! ----\n";
        }
        
        if(choice != 0) {
            cout << "\n\n按任意键继续....";
            getchar();
        }
    } while(choice != 0);
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 控制面板 **

void Menu()
{
    system("cls");
    cout << "************************************************************\n";
    cout << "* * * * * * * * 通讯录管理系统(单链表) * * * * * * * *\n";
    cout << "************************************************************\n";
    cout << "      1  增加记录（末尾）        \n";
    cout << "      2  插入记录（指定位置）    \n";
    cout << "      3  删除记录                \n";
    cout << "      4  查询记录                \n";
    cout << "      5  修改记录                \n";
    cout << "      6  显示所有记录            \n";
    cout << "      7  保存数据                \n";
    cout << "      0  退出系统                \n";
    cout << "************************************************************\n";
    cout << "请选择：";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 查询菜单 **

void SearchMenu()
{
    cout << "\n===== 查询方式 =====\n";
    cout << "      1. 按学号查询     \n";
    cout << "      2. 按姓名查询     \n";
    cout << "      0. 返回主菜单     \n";
    cout << "====================\n";
    cout << "请选择: ";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 创建空表 **

void InitList(LinkNode *&L)
{
    L = (LinkNode *)malloc(sizeof(LinkNode));
    L->next = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 销毁表 **

void DestroyList(LinkNode *&L)
{
    LinkNode *p = L;
    LinkNode *q;
    
    while(p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    L = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 判断是否为空 **

bool IsEmpty(LinkNode *&L)
{
    return(L->next == NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 返回表长度 **

int ListLength(LinkNode *L)
{
    int n = 0;
    LinkNode *p = L->next;
    
    while(p != NULL)
    {
        n++;
        p = p->next;
    }
    
    return n;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 显示一条记录 **

void DisplayRecord(Student stud)
{
    cout << "\n================================\n";
    cout << "学号: " << stud.id << endl;
    cout << "姓名: " << stud.name << endl;
    cout << "年龄: " << stud.age << endl;
    cout << "籍贯: " << stud.native_place << endl;
    cout << "身高: " << stud.height << "cm" << endl;
    cout << "固定电话: " << stud.landline << endl;
    cout << "================================\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 显示所有记录 **

void DisplayAllRecords(LinkNode *L)
{
    if(IsEmpty(L))
    {
        cout << "\n通讯录为空，没有记录可显示。\n";
        return;
    }
    
    cout << "\n===== 通讯录所有记录 =====\n";
    cout << "共有 " << ListLength(L) << " 条记录\n";
    
    LinkNode *p = L->next;
    int count = 1;
    
    while(p != NULL)
    {
        cout << "\n--- 记录 " << count++ << " ---\n";
        DisplayRecord(p->data);
        p = p->next;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 增加记录（在末尾） **

void AddRecord(LinkNode *&L)
{
    LinkNode *newNode, *p;
    
    newNode = (LinkNode *)malloc(sizeof(LinkNode));
    if(newNode == NULL)
    {
        cout << "内存分配失败！\n";
        return;
    }
    
    if(!InputStudent(&newNode->data, L, NULL))
    {
        free(newNode);
        return;
    }
    
    // 找到链表末尾
    p = L;
    while(p->next != NULL)
    {
        p = p->next;
    }
    
    // 插入到末尾
    p->next = newNode;
    newNode->next = NULL;
    
    cout << "\n记录添加成功！\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 插入记录（指定位置） **

void InsertRecord(LinkNode *&L)
{
    int pos;
    char prompt[100];
    LinkNode *newNode, *p = L;
    
    sprintf(prompt, "\n请输入插入位置(1-%d): ", ListLength(L) + 1);
    if(!Input(prompt, &pos))
    	return;
    
    if(pos < 1 || pos > ListLength(L) + 1)
    {
        cout << "插入位置无效！\n";
        return;
    }
    
    newNode = (LinkNode *)malloc(sizeof(LinkNode));
    if(newNode == NULL)
    {
        cout << "内存分配失败！\n";
        return;
    }
    
    if(!InputStudent(&newNode->data, L, NULL))
    {
        free(newNode);
        return;
    }
    
    // 找到插入位置的前一个节点
    for(int i = 0; i < pos - 1; i++)
    {
        p = p->next;
    }
    
    // 插入节点
    newNode->next = p->next;
    p->next = newNode;
    
    cout << "\n记录插入成功！\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 删除记录 **

void DeleteRecord(LinkNode *&L)
{
    long id;
    char confirm;
    LinkNode *p = L, *q;
    
    if(IsEmpty(L))
    {
        cout << "\n通讯录为空，没有记录可删除。\n";
        return;
    }
    
    if(!InputLong("\n请输入要删除的学生学号: ", &id))
        return;
    
    // 查找要删除的节点
    while(p->next != NULL && p->next->data.id != id)
    {
        p = p->next;
    }
    
    if(p->next == NULL)
    {
        cout << "\n未找到学号为 " << id << " 的学生。\n";
        return;
    }
    
    // 显示要删除的记录
    cout << "\n找到以下记录：\n";
    DisplayRecord(p->next->data);
    
    cout << "\n确认删除该记录？(Y/N): ";
    confirm = getchar();
    clearInputBuffer();
    
    if(confirm == 'Y' || confirm == 'y')
    {
        q = p->next;
        p->next = q->next;
        free(q);
        cout << "\n记录删除成功！\n";
    }
    else
    {
        cout << "\n删除操作已取消。\n";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 查询记录 **

void QueryRecord(LinkNode *L)
{
    int choice;
    
    if(IsEmpty(L))
    {
        cout << "\n通讯录为空，没有记录可查询。\n";
        return;
    }
    
    do
    {
        SearchMenu();
        if(!Input("", &choice))
            continue;
        
        switch(choice)
        {
            case 0:
                return;
                
            case 1: {   // 按学号查询
                long id;
                bool found = false;
                
                if(!InputLong("\n请输入要查询的学生学号: ", &id))
                    break;
                
                LinkNode *p = L->next;
                
                while(p != NULL)
                {
                    if(p->data.id == id)
                    {
                        cout << "\n查询结果：\n";
                        DisplayRecord(p->data);
                        found = true;
                        break;
                    }
                    p = p->next;
                }
                
                if(!found)
                {
                    cout << "\n未找到学号为 " << id << " 的学生。\n";
                }
                break;
            }
                
            case 2: {   // 按姓名查询
                char name[NAME_LEN];
                bool found = false;
                int count = 0;
                
                cout << "\n请输入要查询的学生姓名: ";
                fgets(name, NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';
                
                LinkNode *p = L->next;
                
                while(p != NULL)
                {
                    if(strcmp(p->data.name, name) == 0)
                    {
                        count++;
                        cout << "\n查询结果 " << count << "：\n";
                        DisplayRecord(p->data);
                        found = true;
                    }
                    p = p->next;
                }
                
                if(!found)
                {
                    cout << "\n未找到姓名为 " << name << " 的学生。\n";
                }
                else
                {
                    cout << "\n共找到 " << count << " 条记录。\n";
                }
                break;
            }
                
            default: 
                cout << "\n无效的选项，请重新选择。\n";
        }
    } while(choice != 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 修改记录 **

void ModifyRecord(LinkNode *&L)
{
    long id;
    
    if(IsEmpty(L))
    {
        cout << "\n通讯录为空，没有记录可修改。\n";
        return;
    }
    
    if(!InputLong("\n请输入要修改的学生学号: ", &id))
        return;
    
    // 查找要修改的节点
    LinkNode *p = L->next;
    while(p != NULL && p->data.id != id)
    {
        p = p->next;
    }
    
    if(p == NULL)
    {
        cout << "\n未找到学号为 " << id << " 的学生。\n";
        return;
    }
    
    // 显示原记录
    cout << "\n原记录信息：\n";
    DisplayRecord(p->data);
    
    cout << "\n请输入新的信息：\n";
    
    // 保存原学号
    long old_id = p->data.id;
    
    // 输入新信息
    if(!InputStudent(&p->data, L, p))
        return;
    
    cout << "\n记录修改成功！\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 输入学生信息 **

bool InputStudent(Student *stud, LinkNode *L, LinkNode *exclude)
{
    cout << "\n===== 请输入学生信息 =====\n";
    
    // 学号
    while(1)
    {
        if(!InputLong("学号: ", &stud->id))
            return false;
        
        if(stud->id <= 0)
        {
            cout << "学号必须为正整数！\n";
            continue;
        }
        
        if(!ValidateID(stud->id, L, exclude))
        {
            cout << "错误：学号 " << stud->id << " 已存在！\n";
            return false;
        }
        break;
    }
    
    // 姓名
    cout << "姓名: ";
    fgets(stud->name, NAME_LEN, stdin);
    stud->name[strcspn(stud->name, "\n")] = '\0';
    
    // 年龄
    while(1)
    {
        if(!Input("年龄: ", &stud->age))
            return false;
        
        if(stud->age < 0 || stud->age > 150)
        {
            cout << "年龄无效！请输入0-150之间的整数。\n";
            continue;
        }
        break;
    }
    
    // 籍贯
    cout << "籍贯: ";
    fgets(stud->native_place, PLACE_LEN, stdin);
    stud->native_place[strcspn(stud->native_place, "\n")] = '\0';
    
    // 身高
    while(1)
    {
        if(!InputFloat("身高(cm): ", &stud->height))
            return false;
        
        if(stud->height < 0 || stud->height > 300)
        {
            cout << "身高无效！请输入0-300之间的数值。\n";
            continue;
        }
        break;
    }
    
    // 固定电话
    cout << "固定电话: ";
    fgets(stud->landline, PHONE_LEN, stdin);
    stud->landline[strcspn(stud->landline, "\n")] = '\0';
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 验证学号唯一性 **

bool ValidateID(long id, LinkNode *L, LinkNode *exclude)
{
    LinkNode *p = L->next;
    
    while(p != NULL)
    {
        // 跳过要排除的节点（用于修改操作）
        if(exclude != NULL && p == exclude)
        {
            p = p->next;
            continue;
        }
        
        if(p->data.id == id)
        {
            return false; // 学号已存在
        }
        p = p->next;
    }
    
    return true; // 学号唯一
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 保存到文件 **

void SaveToFile(LinkNode *L)
{
    FILE *fp;
    LinkNode *p = L->next;
    
    fp = fopen("contacts.dat", "wb");
    if(fp == NULL)
    {
        cout << "\n无法创建文件！\n";
        return;
    }
    
    // 先写入记录数量
    int count = ListLength(L);
    fwrite(&count, sizeof(int), 1, fp);
    
    // 写入每条记录
    while(p != NULL)
    {
        fwrite(&p->data, sizeof(Student), 1, fp);
        p = p->next;
    }
    
    fclose(fp);
    cout << "\n成功保存 " << count << " 条记录到文件。\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 从文件加载 **

void LoadFromFile(LinkNode *&L)
{
    FILE *fp;
    int count, i;
    
    fp = fopen("contacts.dat", "rb");
    if(fp == NULL)
    {
        cout << "\n无法打开文件！文件可能不存在。\n";
        return;
    }
    
    // 读取记录数量
    fread(&count, sizeof(int), 1, fp);
    
    if(count <= 0 || count > MAX_STUDENTS)
    {
        cout << "\n文件损坏：无效的记录数量 " << count << "\n";
        fclose(fp);
        return;
    }
    
    // 读取每条记录并添加到链表
    for(i = 0; i < count; i++)
    {
        LinkNode *newNode, *p;
        
        newNode = (LinkNode *)malloc(sizeof(LinkNode));
        if(newNode == NULL)
        {
            cout << "内存分配失败！\n";
            fclose(fp);
            return;
        }
        
        fread(&newNode->data, sizeof(Student), 1, fp);
        newNode->next = NULL;
        
        // 找到链表末尾
        p = L;
        while(p->next != NULL)
        {
            p = p->next;
        }
        
        // 插入到末尾
        p->next = newNode;
    }
    
    fclose(fp);
    cout << "\n成功加载 " << count << " 条记录。\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** sys选择验证 **

int input(char c)
{
    if('0' <= c && '9' >= c) 
        return c - '0';
    else 
        return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 整型输入验证 **

bool Input(const char *s, int *n)
{
    if(s) cout << s;
    if(scanf("%d", n) != 1)
    {
        cout << "\n输入字符非法!";
        clearInputBuffer();
        return false;
    }
    clearInputBuffer();
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 长整型输入验证 **

bool InputLong(const char *s, long *n)
{
    if(s) cout << s;
    if(scanf("%ld", n) != 1)
    {
        cout << "\n输入字符非法!";
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
    if(s) cout << s;
    if(scanf("%f", n) != 1)
    {
        cout << "\n输入字符非法!";
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
    while(getchar() != '\n');
}
