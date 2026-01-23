#include <stdio.h>
#include <cstdlib> 		// 包含system(),rand(),srand()函数的头文件
#include <ctime>    	// 用于设置随机种子
#include <stdlib.h> 	// 需要包含malloc的头文件
#include <iostream>  	// c++库.是IO的库
#include <stdbool.h> 	// bool

#define MaxSize 50		// 链表最大容限 

using namespace std;   	// 调用标准(std)命名空间

typedef int ElemType;

typedef struct LNode 
{
	ElemType data;
	struct LNode *next;
} LinkNode;

//void Menu();										// 控制面板

void InitList(LinkNode *&L);						// 创建空表
void DestroyList(LinkNode *&L);						// 销毁表


void CreateList(LinkNode *&L, ElemType a[], int n);	// 输入表
void DispList(LinkNode *L);	                        // 输出表
                                                    // 输出表

//void Search_sys(LinkNode *L);						// 查找系统
bool ListEmpty(LinkNode *&L);						// 判断是否为空
int ListLength(LinkNode *L);						// 返回表长度
bool GetElem(LinkNode *L, int i, ElemType &e);		// 按序查找
                                                    // 按值查找

//void upDate_sys(LinkNode *&L);					// 修改系统
                                                    // 修改元素 
                                                    // 插入元素
                                                    // 删除数据

//void main2(LinkNode *&L1, LinkNode *&L2);			// 附加系统 
void ListReverse(LinkNode *&L);						// 逆置单链表 
void Sort(LinkNode *&L);							// 排序表
//void ListUnion(LinkNode *&L1, LinkNode *&L2);		// 合并有序表 

// int input(char c);								// sys选择
bool Input(const char *s, int *n);					// 整型验证 
void clearInputBuffer();							// 清除缓冲区

int main()
{
	LinkNode *L;
	InitList(L);
	L->data=2;
	printf("\n%d\n",L->data);
	printf("\n%d\n",ListLength(L));
	
	int n=0,i;
	ElemType e;
				
	if(!Input("\n请输入表 1 的长度:",&n))
				
	n<0?n=0:n;							// 限制长度 
	n>MaxSize?n=MaxSize:n=n;
				
	ElemType *a = new ElemType[n]; 		// 动态分配数组
	
	for(i=0;i<n;i++)
		a[i]=rand();	//生成试验数据
	
	CreateList(L,a,n);
				
	cout<<"\n---- 顺序表 1 已建立! ----";
	delete[] a; 	// 释放数组
	
	DispList(L);
	
	printf("\n%d\n",ListLength(L));
	
	bool isOK=GetElem(L,2,e);
	printf("\n%s数据:",isOK?"查到":"未查到");
	!isOK?printf("NULL\n"):printf("%d\n",e);
	
	ListReverse(L);
	
	DispList(L);
	
	Sort(L);
	
	DispList(L);
	
	DestroyList(L);
}

void InitList(LinkNode *&L)
{
	L=(LinkNode *)malloc(sizeof(LinkNode));
	L->next=NULL;
}

void DestroyList(LinkNode *&L)
{
	LinkNode *pre=L, *p=L->next;
	while(p!=NULL)
	{
		free(pre);
		pre=p; p=pre->next;
	}
	free(pre);
}

bool ListEmpty(LinkNode *&L)
{
	return(L->next==NULL);
}

int ListLength(LinkNode *L)
{
	int n=0;
	LinkNode *p=L;
	for(n=0;p->next!=NULL;n++)
		p=p->next;
	if(L->data!=n) return -1;	// -1表征节点丢失 
	return n;
} 

void CreateList(LinkNode *&L, ElemType a[], int n)
{
	LinkNode *s, *r=L;
	for(int i=0;i<n;i++)
	{
		s=(LinkNode *)malloc(sizeof(LinkNode));	// 申请节点 
		s->data=a[i];
		r->next=s;		// 尾节点 r 作为链接对象 
		r=s;			// 移动 r 
	}
	r->next=NULL;		// 处理尾节点 
	L->data=n;			// 将表长存入头节点 
}

void DispList(LinkNode *L)
{
	LinkNode *p=L->next;
	printf("\n- - - - - - - - - - - - - - - -\n\n");
	for(int i=0; i<L->data; i++, p=p->next) {
		printf("%6d",p->data);	printf("  -> ");
		if((i+1)%3==0)	printf("\n");
	}
	printf("  NULL");
	printf("\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
} 

bool GetElem(LinkNode *L, int i, ElemType &e)
{
	LinkNode *p=L;
	if(i<=0) return false;
	for(int j=0; j<i && p!=NULL; j++, p=p->next);
	if(p==NULL) return false;
	e=p->data;  return true;
}

void ListReverse(LinkNode *&L)
{
	LinkNode *p=L->next, *q=p->next;
	while(p->next!=NULL)
	{
		p->next=q->next;
		q->next=L->next;
		L->next=q;
		q=p->next;
	}
}

void Sort(LinkNode *&L)
{
	LinkNode *p, *q;
	ElemType ts;
	
	for(p=L->next;p!=NULL;p=p->next)						// 冒泡排序 
		for(q=L->next;q->next!=p;q=q->next)
		    if(q->data>q->next->data)
		    {	
				ts=q->data;
				q->data=q->next->data;
				q->next->data=ts;
			};
}

bool Input(const char *s, int *n)
{
	if(s) printf("%s",s);
    if(scanf("%d",n)!=1)
	{
        printf("\n输入字符非法!");
        clearInputBuffer();
        return 0;
    }
    clearInputBuffer();
    return 1;
}

void clearInputBuffer() {
    while(getchar()!='\n');
}

