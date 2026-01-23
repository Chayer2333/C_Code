#include <stdio.h>
#include <cstdlib>   // 包含system(),rand(),srand()函数的头文件
#include <ctime>     // 用于设置随机种子
#include <stdlib.h>  // 需要包含malloc的头文件
#include <iostream>  // c++库.是IO的库
#include <stdbool.h> // bool
#include <string.h>  // 包含strcpy函数

#define MaxSize 50

using namespace std; // 调用标准(std)命名空间



// 患者信息结构体
typedef struct
{
    char name[10]; // 病人姓名
    int num;       // 病历号
} ElemType;

// 顺序队列结构体
typedef struct
{
    ElemType data[MaxSize];
    int front, rear;
} SqQueue;



void Menu(); // 控制面板

void InitQueue(SqQueue *&Q);                           // 顺序队列初始化
bool EnQueue(SqQueue *&Q, ElemType e);                 // 顺序队列入队操作
bool DeQueue(SqQueue *&Q, ElemType &e);                // 顺序队列出队操作
bool QueueEmpty(SqQueue *Q);                           // 判断队列是否为空
bool QueueFull(SqQueue *Q);                            // 判断队列是否为满
void ShowQueue(SqQueue *Q);                            // 遍历队列

int input(char c);									   // sys选择
void clearInputBuffer(); 							   // 清除缓冲区



int main()
{
    int choice=0;
    SqQueue *Q; // 患者队列
    InitQueue(Q);
    
    srand(time(NULL));
    
    ElemType patient;
    int patientCount=0; // 患者计数，用于生成病历号

    do
    {
    	char c='N';
        choice=0;
        Menu();
        cin>>(c);
        choice=input(c);
        clearInputBuffer();
        
        switch(choice)
        {
        case 0: { // ** 退出指令 **
            cout<<"\n系统已退出。\n";
            break;
        }
        
        case 1: { // ** 候诊（入队） **
            char c='N';
            
            cout<<"\n请输入患者姓名: ";
            cin>>patient.name;
            clearInputBuffer();
            
            // 随机生成病历号
            patient.num=10000+(rand()%90000);
            patientCount++;
            
            if(EnQueue(Q, patient)) {
                cout<<"\n--- 患者 "<<patient.name<<" 已加入候诊队列，病历号: "<<patient.num<<" ---";
            } else {
                cout<<"\n--- 候诊队列已满，无法添加新患者! ---";
            }
            
            cout<<"\n\n按任意键继续....";
            c=getchar();
            break;
        }
        
        case 2: { // ** 就诊（出队） **
            char c='N';
            
            if (QueueEmpty(Q)) {
                cout<<"\n--- 候诊队列为空，没有患者等待就诊! ---";
            } else {
                if(DeQueue(Q, patient)) {
                    cout<<"\n--- 患者 "<<patient.name<<" (病历号: "<<patient.num<<") 开始就诊 ---";
                } else {
                    cout<<"\n--- 就诊操作失败! ---";
                }
            }
            
            cout<<"\n\n按任意键继续....";
            c=getchar();
            break;
        }
        
        case 3: { // ** 查看排队（遍历） **
            char c='N';
            
            if(QueueEmpty(Q)) {
                cout<<"\n--- 候诊队列为空 ---";
            } else {
                cout<<"\n--- 当前候诊队列 ---";
                ShowQueue(Q);
            }
            
            cout<<"\n\n按任意键继续....";
            c=getchar();
            break;
        }
        
        default: {
            char c='N';
            cout<<"\n--- 输入错误! ---\n";
            cout<<"\n\n按任意键继续....";
            c=getchar();
            break;
        }
        }
    } while (choice);
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 控制面板 **

void Menu()
{
    system("cls");
    cout<<"*******医院看病模拟系统*******\n";
    cout<<"------------------------------\n";
    cout<<"         1 候诊（入队)        \n";
    cout<<"         2 就诊（出队）       \n";
    cout<<"         3 查看排队（遍历）   \n";
    cout<<"         0 下班（退出程序）   \n";
    cout<<"------------------------------\n";
    cout<<"请选择：";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 顺序队列初始化 **

void InitQueue(SqQueue *&Q)
{
    Q=(SqQueue *)malloc(sizeof(SqQueue));
    Q->front=Q->rear=0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 顺序队列入队操作 **

bool EnQueue(SqQueue *&Q, ElemType e)
{
    if ((Q->rear+1)%MaxSize==Q->front) // 队满
        return false;
    
    Q->rear=(Q->rear+1)%MaxSize;
    strcpy(Q->data[Q->rear].name, e.name);
    Q->data[Q->rear].num=e.num;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 顺序队列出队操作 **

bool DeQueue(SqQueue *&Q, ElemType &e)
{
    if (Q->front==Q->rear) // 队空
        return false;
    
    Q->front=(Q->front+1)%MaxSize;
    strcpy(e.name, Q->data[Q->front].name);
    e.num=Q->data[Q->front].num;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 判断队列是否为空 **

bool QueueEmpty(SqQueue *Q)
{
    return (Q->front==Q->rear);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 判断队列是否为满 **

bool QueueFull(SqQueue *Q)
{
    return ((Q->rear+1)%MaxSize==Q->front);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 遍历队列 **

void ShowQueue(SqQueue *Q)
{
    int i;
    if(Q->front==Q->rear)
        return;
    
    i=(Q->front+1)%MaxSize;
    int count=1;
    
    while(i!=(Q->rear+1)%MaxSize)
    {
        cout<<"\n"<<count<<". 病历号："<<Q->data[i].num<<"\t姓名："<<Q->data[i].name;
        i=(i+1)%MaxSize;
        count++;
    }
    cout<<endl;
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
// ** 清除缓冲区 **

void clearInputBuffer()
{
    while(getchar()!='\n');
}
