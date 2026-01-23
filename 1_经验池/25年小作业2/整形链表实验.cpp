#include <stdio.h>
#include <cstdlib> 		// 包含system(),rand(),srand()函数的头文件
#include <ctime>    	// 用于设置随机种子
#include <stdlib.h> 	// 需要包含malloc的头文件
#include <iostream>  	// c++库.是IO的库
#include <stdbool.h> 	// bool

#define MaxSize 50		// 链表最大容限

using namespace std;   	// 调用标准(std)命名空间

typedef int ElemType;	// my 类型

typedef struct LNode 
{
	ElemType data;
	struct LNode *next;
} LinkNode;

void Menu();											// 控制面板

void InitList(LinkNode *&L);							// 创建空表
void DestroyList(LinkNode *&L);							// 销毁表

bool CreateList(LinkNode *&L, ElemType a[], int n);		// 输入表
void DispList_1(LinkNode *L);							// 输出表
void DispList_2(LinkNode *L);							// 输出表

void Search_sys(LinkNode *L);							// 查找系统
bool ListEmpty(LinkNode *&L);							// 判断是否为空
 int ListLength(LinkNode *L);							// 返回表长度
bool GetElem(LinkNode *L, int i, ElemType &e);			// 按序查找
int LocateElem(LinkNode *L, int Bp, ElemType e);		// 按值查找

void upDate_sys(LinkNode *&L);							// 修改系统
bool ListUpdate(LinkNode *&L, int i, ElemType e);		// 修改元素 
bool ListInsert(LinkNode *&L, int i, ElemType e);		// 插入元素
bool ListDelete(LinkNode *&L, int i, ElemType &e);		// 删除数据

void main2(LinkNode *&L1, LinkNode *&L2);				// 附加系统 
void ListReverse(LinkNode *&L);							// 逆置单链表 
void Sort(LinkNode *&L);								// 排序表
void ListUnion(LinkNode *&L1, LinkNode *&L2);			// 合并有序表 

 int input(char c);										// sys选择
bool Input(const char *s, int *n);						// 整型验证 
void clearInputBuffer();								// 清除缓冲区

int main()
{

	int choice=0;
	char c='N';
	LinkNode *L;			// 表 1
	InitList(L);
	
	LinkNode *L1;			// 表 2
	InitList(L1);
	
	srand(time(NULL));	// 生成随机数种子 
	
	do
	{
		choice=0; c='N'; 
		Menu();
		cin>>(c);
        choice=input(c);
        clearInputBuffer();
		
		switch(choice)
		{
			case 0: {			// ** 退出指令 **
				DestroyList(L);
				DestroyList(L1);
				cout<<"\n表已销毁。\n";
                cout<<"\n系统已退出。\n";
                break;
			}
			
			case 1: {			// ** 建立实验表 1 **
				int n=0,i;
				bool isOK=0;
				DestroyList(L);						// 避免野节点 
				InitList(L);
				
				if(!Input("\n请输入表 1 的长度:",&n)) break;
				
				n<0?n=0:n;							// 限制长度 
				n>MaxSize?n=MaxSize:n=n;
				
				ElemType *a = new ElemType[n]; 		// 动态分配数组
				
				for(i=0;i<n;i++)
					a[i]=rand();	//生成试验数据 
				
				isOK=CreateList(L,a,n);
				
				printf("\n---- 顺序表 1 建立%s! ----",isOK?"成功":"失败"); 
				delete[] a; 	// 释放数组
				break;	
			}
			
			case 2: {			// ** 查找系统 **
    			Search_sys(L);
				break;	
			}
			
			case 3: {			// ** 修改系统 **
    			upDate_sys(L);
				break;
			}
			
			case 4: {			// ** 附加实验 ** 
				main2(L,L1);
				break;	
			}
			default: cout<<"\n---- 输入错误! ----\n";
		}
	//////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
	} while(choice);
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 控制面板 **

void Menu()
{
	system("cls");
	cout<<"*******整形链表操作*******\n";
	cout<<"--------------------------\n";
	cout<<"      1  建立实验表1      \n";
	cout<<"      2   查询系统        \n";
	cout<<"      3   修改系统        \n";
	cout<<"--------------------------\n";
	cout<<"      4   附加功能        \n";
	cout<<"--------------------------\n";
	cout<<"      0   退出程序        \n";
	cout<<"--------------------------\n";
	cout<<"**************************\n";
	cout<<"请选择：";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 创建空表 **

void InitList(LinkNode *&L)
{
	L=(LinkNode *)malloc(sizeof(LinkNode));
	L->data=0; L->next=NULL;
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 销毁表 **

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 判断是否为空 **	ps:实际改为三值表示表满会更好 

bool ListEmpty(LinkNode *&L)
{
	return(L->next==NULL);
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 返回表长度 **

int ListLength(LinkNode *L)
{
	int n=0;
	LinkNode *p=L;
	for(n=0;p->next!=NULL;n++)
		p=p->next;
	if(L->data!=n) return -1;	// -1表征节点丢失
	return n;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 输入表 **

bool CreateList(LinkNode *&L, ElemType a[], int n)
{	
	if(L->data!=0)	return false;
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
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 输出表 **

void DispList_1(LinkNode *L)
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

void DispList_2(LinkNode *L)
{	// 显示所有元素与其序号的对应关系
	LinkNode *p=L->next;
	cout<<"\n当前表中的元素及其序号对映：\n";
	cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
	for(int i=1; i<=L->data; i++, p=p->next)
		if(p!=NULL)
			cout<<"  序号 "<<i<<": \t\t"<<p->data<<endl;
	cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 查找系统 **

void Search_sys(LinkNode *L)
{
	int choice;
	char c='N'; 
    do {
    	choice=999; c='N';
		system("cls");
		cout<<"*******整形链表操作*******\n";
		cout<<"--------------------------\n";
        cout<<"---------查询系统---------\n";
        cout<<"      1  返回表长度       \n";
        cout<<"      2  遍历显示表       \n";
        cout<<"      3 按序查找元素      \n";
        cout<<"      4 按值查找元素      \n";
        cout<<"      0   退出程序        \n";
        cout<<"--------------------------\n";
		cout<<"**************************\n";
        printf("\n请选择 (0-4): ");
        cin>>(c);
        choice=input(c);
        clearInputBuffer();

        switch(choice) {
			case 0: return;	// 退出子程序
			
			case 1: {
				int n=ListLength(L);
				if(n==-1)
					printf("\n---- 顺序表节点丢失! ----");
				else
					printf("\n---- 顺序表长度为%d ----",n);
				break;
			}
			
			case 2: {
				DispList_1(L);
				break;
			}
			
            case 3: {
            	int i; bool bl;
            	ElemType e;

    			if(!Input("\n请输入要查找的序号:",&i)) break;
    			
    			bl=GetElem(L, i, e);
				printf("\n----- %s该序号 -------\n",bl?"查到":"未查到");
				//bl?printf("值为:%d",e):0;
				if(bl)	printf("值为:%d",e);
				break;
			}
			
            case 4: {
				int Bp=0,count=0;
            	ElemType e;
            	
            	if(!Input("\n请输入要查找的元素值:",&e)) break;
            	
    			cout<<"\n\n--------------------------\n\n";
    			do {
    					Bp=LocateElem(L,Bp,e);
    					count++;
    					if(Bp!=0) printf("第%d个匹配元素的位置：%d\n", count, Bp);
				} while (Bp);
    			if(count==1) printf("未找到值为 %d 的元素位置!\n",e);
    			cout<<"\n--------------------------\n";
				break;
			}
            default: cout<<"\n---- 输入错误! ----\n";
        }
   	//////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
    } while (choice!=0);
}

// ** 按序查找 **

bool GetElem(LinkNode *L, int i, ElemType &e)
{
	LinkNode *p=L;
	if(i<=0) return false;
	for(int j=0; j<i && p!=NULL; j++, p=p->next);
	if(p==NULL) return false;
	e=p->data;  return true;
} 

// ** 按值查找 **

int LocateElem(LinkNode *L, int Bp, ElemType e)
{					// Breakpoint 查询断点
	int i; LinkNode *p=L->next;
	for(i=Bp; i>0; i--)
		p=p->next;
	for(i=Bp; i<L->data; i++, p=p->next)
		if(p->data==e)
			return i+1;
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 修改系统 **

void upDate_sys(LinkNode *&L)
{
	int choice;
	char c='N';
    do {
    	choice=999; c='N';
		system("cls");
		cout<<"*******整形链表操作*******\n";
		cout<<"--------------------------\n";
        cout<<"---------修改系统---------\n";
        cout<<"      1 定点插入元素      \n";
        cout<<"      2 定点修改元素      \n";
        cout<<"      3 查值修改元素      \n";
		cout<<"      4 定点删除元素      \n";
		cout<<"      5 查值删除元素      \n";
        cout<<"      0   退出程序        \n";
        cout<<"--------------------------\n";
		cout<<"**************************\n";
        printf("\n请选择 (0-5): ");
        cin>>(c);
        choice=input(c);
        clearInputBuffer();
		
        switch(choice) {
			case 0: return;	// 退出子程序 
			
			case 1: {
				int i;
				ElemType e;
				
				if(ListEmpty(L)==false)
				{
					DispList_2(L);
				} else {
					printf("\n表为空,请注意只能在首位插入!!!\n");
				}
				
				printf("\n请输入插入点 (1-%d) :",L->data>=MaxSize?MaxSize:L->data+1);
				
				if(!Input(" ",&i)) break;
				
				if(!Input("\n请输入元素:",&e)) break;
				
				printf("\n---- 插入操作%s ----\n",ListInsert(L,i,e)?"成功！":"失败");
				printf("\n此时顺序表长度为 %d / %d ",ListLength(L),MaxSize);
				break;
			}
			
			case 2: {
				int i;
				ElemType e;
				
				if(ListEmpty(L)==false)
				{
					DispList_2(L);
				} else {
					printf("\n表为空,修改操作已退出!\n");
					break;
				}
				
				printf("\n请输入修改点 (1-%d) :",L->data);
				
				if(!Input("",&i)) break;
				
				if(!Input("\n请输入元素:",&e)) break;
				
				printf("\n---- 修改操作%s ----\n",ListUpdate(L,i,e)?"成功！":"失败");
				printf("\n此时顺序表长度为 %d / %d ",ListLength(L),MaxSize);
				break;
			}
			
            case 3: {
            	int Bp=0,count=0;
            	char c='N';
            	ElemType e,e1;
            	
            	if(!Input("\n请输入要查找的元素值:",&e)) break;
            	
    			cout<<"\n\n--------------------------\n\n";
    			while(1)
				{
    					c='N'; e1=e;
    					Bp=LocateElem(L,Bp,e);
						
    					if(Bp!=0) {
    						count++;
							printf("第%d个匹配元素的位置：%d\n", count, Bp);
						} else {
							cout<<"\n-------- 表已查完 --------\n";
							break;
						}
						
    					cout<<"\n是否修改该处的值? ( Y or N ):";
    					cin>>(c); clearInputBuffer();
    					
    					if(c=='y' || c=='Y')
    					{
    						if(!Input("\n请输入元素:",&e1)) break;
							printf("\n ---- 修改操作%s ----\n",ListUpdate(L,Bp,e1)?"成功！":"失败");
						}
						
						cout<<"\n是否继续查找该值? ( Y or N ):";
						cin>>(c); clearInputBuffer();
						
						if(c=='n' || c=='N') break;
						cout<<"\n--------------------------\n\n";
				}
    			if(count==0)
        			printf(" 未找到值为 %d 的元素位置!\n",e);
   				else
        			printf("\n   共找到 %d 个匹配元素.\n",count);
    			cout<<"\n--------------------------\n";
				break;
			}
			
            case 4: {
				int i; c='N';
				bool isOK=0;
				ElemType e;
				
				if(ListEmpty(L)==true)
				{
					printf("\n当前表为空,删除操作已退出!");
					break;
				}
				
				DispList_2(L);
				
				printf("\n请输入删除点: (1-%d) :",L->data);
				if(!Input(" ",&i)) break;
								
				cout<<"\n要删除的元素为:";
				printf("%d\n",GetElem(L,i,e)?e:0);
				
				cout<<"\n是否确认删除? ( Y or N ):";
				cin>>(c); clearInputBuffer();
				
				if(c=='Y' || c=='y')
				{
					isOK=ListDelete(L,i,e);
					printf("\n---- 删除操作%s ----\n",isOK?"成功！":"失败!!!");
					if(isOK) printf("\n顺序表长度为 %d/%d \n",ListLength(L),MaxSize);
					
				} else {
					cout<<"\n---- 删除操作已取消! ----"; 
				}
				break;
			}
			
			case 5: {
				int Bp=0,count=0;
            	char c='N';
            	bool isOK=0;
            	ElemType e,e1;
            	
            	if(!Input("\n请输入要查找的元素值:",&e)) break;
            	
    			cout<<"\n\n--------------------------\n\n";
    			while(1)
				{
    					c='N'; isOK=0;
    					Bp=LocateElem(L,Bp,e);
    					
    					if(Bp!=0) {
    						count++;
    						printf("第%d个匹配元素的位置：%d\n", count, Bp);
						} else {
							cout<<"\n-------- 表已查完 --------\n";
							break;
						}
						
    					cout<<"\n是否删除该处的值? ( Y or N ):";
    					cin>>(c); clearInputBuffer();
    					
    					if(c=='y' || c=='Y')
    					{
    						isOK=ListDelete(L,Bp,e);
							printf("\n ---- 删除操作%s ---- \n",isOK?"成功！":"失败!!!");
							if(isOK) printf("\n顺序表长度为 %d/%d \n",ListLength(L),MaxSize);
						}
						
						cout<<"\n是否继续查找该值? ( Y or N ):";
						cin>>(c); clearInputBuffer();
						
						if(c=='n' || c=='N') break;
						cout<<"\n--------------------------\n\n";
				}
    			if(count==0)
        			printf(" 未找到值为 %d 的元素位置!\n",e);
   				else
        			printf("\n   共找到 %d 个匹配元素.\n",count);
        		cout<<"\n--------------------------\n";
				break;
			}
            default: cout<<"\n---- 输入错误! ----\n";
        }
   	//////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
    } while (choice!=0);
}

// ** 修改元素 **

bool ListUpdate(LinkNode *&L, int i, ElemType e)
{
	LinkNode *p=L->next;
	if(i<1 || i>L->data || i>MaxSize)
		return false;
	while(--i>0)		// 移动到节点 i 
		p=p->next;
	p->data=e;
	return true;
}

// ** 插入元素 **

bool ListInsert(LinkNode *&L, int i, ElemType e)
{
	LinkNode *p=L, *s;
	if(i<1 || i>L->data+1 || L->data>=MaxSize)
		return false;
	while(--i>0 && p!=NULL)
		p=p->next;
	if(p==NULL && i!=L->data+1)	return false;
	s=(LinkNode *)malloc(sizeof(LinkNode));
	s->data=e;
	s->next=p->next;	// p->next连到 s 后 
	p->next=s;			// p->next置为 s 
	L->data++;
	return true;
} 

// ** 删除数据 **

bool ListDelete(LinkNode *&L, int i, ElemType &e)
{
	LinkNode *p=L, *q;
	if(i<1 || i>L->data)
		return false;
	while(--i>0 && p!=NULL)
		p=p->next;
	if(p==NULL || p->next==NULL)
		return false;
	q=p->next;
	e=q->data;
	p->next=q->next;
	free(q);
	L->data--;
	return true;
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 选做实验 **

void main2(LinkNode *&L1, LinkNode *&L2)
{
	int choice;
	char c='N';
    do {
    	choice=999; c='N';
		system("cls");
		cout<<"*******整形链表操作*******\n";
		cout<<"--------------------------\n";
        cout<<"----------附加实验--------\n";
        cout<<"      1  逆置单链表       \n";
		cout<<"      2  建立实验表2      \n";
		cout<<"      3  有序表的并       \n";
        cout<<"      0   退出程序        \n";
        cout<<"--------------------------\n";
		cout<<"**************************\n";
        printf("\n请选择 (0-3): ");
        cin>>(c);
        choice=input(c);
        clearInputBuffer();

        switch(choice) {
        	case 0: return;	// 退出子程序
			
			case 1: {
				if(!ListLength(L1))
				{
					cout<<"\n   --- 表为空! ---";
					break;
				}
				cout<<"\n逆置前结果:";
				DispList_1(L1);
				ListReverse(L1);
				cout<<"\n逆置后结果:";
				DispList_1(L1);
				break;
			} 
			
			case 2: {
				int n=0,i;
				bool isOK=0;
				DestroyList(L2);					// 避免野节点 
				InitList(L2);
				
				if(!Input("\n请输入表 2 的长度:",&n)) break;
				
				n<0?n=0:n;							// 限制长度 
				n>MaxSize?n=MaxSize:n=n;
				
				ElemType *a = new ElemType[n]; 		// 动态分配数组
				
				for(i=0;i<n;i++)
					a[i]=rand();	//生成试验数据 
				
				isOK=CreateList(L2,a,n);
				
				printf("\n---- 顺序表 2 建立%s! ----",isOK?"成功":"失败"); 
				delete[] a; 	// 释放数组
				break;
			}
			
			case 3: {
				int overflow=0;		// 判断是否溢出 
				if(ListEmpty(L2)!=0)
				{
					cout<<"\n---- 表 2 为空,程序已退出! ----";
					break;
				}
				
				if(ListEmpty(L1) || L1->data>=MaxSize)
				{
        			cout<<"\n ---- 表 1 为空或已满! ----";
        			break;
   				 }
				
				overflow=L1->data+L2->data;
				
				Sort(L1);
				Sort(L2);
				
				cout<<"\n\n  ------- 两表已排序! ------\n";
				cout<<"\n表 1 排序如下:\n";
				DispList_1(L1);
				cout<<"\n表 2 排序如下:\n";
				DispList_1(L2);
				
				ListUnion(L1,L2);	// 调用合并函数 
				
				cout<<"\n\n  ------- 两表已合并! ------\n";
				cout<<"\n表 1 结果如下:\n";
				DispList_1(L1);
				printf("\n顺序表 1 长度为 %d/%d \n", ListLength(L1), MaxSize);
				printf("\n  -------- 运算%s --------", overflow>MaxSize?"溢出":"未溢出");
				
				InitList(L2);		// 重建表 2 以便继续运行程序	
				break;
			}
			default: cout<<"\n    ---- 输入错误! ----\n";
		}
	//////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
	} while (choice!=0);
}

// ** 逆置单链表 **

void ListReverse(LinkNode *&L)
{	// 原地置换法 
	LinkNode *p=L->next, *q=p->next;
	while(p->next!=NULL)
	{
		p->next=q->next;	// 链接 q 后的节点	(不丢节点) 
		q->next=L->next;	// 链接 p 前的节点	(不丢节点)
		L->next=q;			// 将 q 插入表头	(逆置)
		q=p->next;			// 将 q 移至 p 后	(移动)
	}
}
/*
void InvertLinkedList(LinkNode &L)
{	// 头插法 
	LinkNode *p, *q=L->next;
	L->next=NULL;
	while(q)
	{
		p=q;
		q=q->next;
		p->next=L->next;
		L->next=p;
	}
}
*/
// ** 单链表的排序 **

void Sort(LinkNode *&L)
{
    if(L==NULL || L->next==NULL) return;
    
    LinkNode *p, *q, *end = NULL;  // end记录已排序部分的边界
    ElemType ts;
    
    for(p=L->next; p->next!=NULL; p=p->next, end=q)
        for(q=L->next; q->next!=end; q=q->next)
            if(q->data > q->next->data)		// 冒泡 
			{
                ts = q->data;
                q->data = q->next->data;
                q->next->data = ts;
            }
}

// ** 单链表的并 **

void ListUnion(LinkNode *&L1, LinkNode *&L2)
{
	if(L1==NULL || L2==NULL) return;
	LinkNode *p1=L1->next;
	LinkNode *p2=L2->next;
	LinkNode *p=L1;
	while(p1!=NULL && p2!=NULL)
	{
		if(p1->data < p2->data)
			{p->next=p1; p=p1; p1=p1->next;}
		else
			{p->next=p2; p=p2; p2=p2->next;}
	}
	if(p1)	p->next=p1;
	else	p->next=p2;
	L1->data+=L2->data;	// 记录长度 
	L2->next=NULL;		// 释放 L2 
	DestroyList(L2);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 清除缓冲区 **

void clearInputBuffer() {
    while(getchar()!='\n');
}

