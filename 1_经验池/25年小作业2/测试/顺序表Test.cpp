#include <stdio.h>
#include <cstdlib> 		// 包含system(),rand(),srand()函数的头文件
#include <ctime>    	// 用于设置随机种子
#include <stdlib.h> 	// 需要包含malloc的头文件
#include <iostream>  	// c++库.是IO的库
#include <stdbool.h> 	// bool

#define MaxSize 50		// 顺序表最大容限 

using namespace std;   	// 调用标准(std)命名空间

typedef int ElemType;

typedef struct
{
	ElemType data[MaxSize];
	int length;
} SqList;

void Menu();										// 控制面板

void InitList(SqList *&L);							// 创建空表
void DestroyList(SqList *&L);						// 销毁表

void Search_sys(SqList *L);							// 查找系统
bool ListEmpty(SqList *&L);							// 判断是否为空
int ListLength(SqList *L);							// 返回表长度
bool GetElem(SqList *L, int i, ElemType &e);		// 按序查找
int LocateElem(SqList *L, int Bp, ElemType e);		// 按值查找

void CreateList(SqList *&L, ElemType a[], int n);	// 输入表
void DispList(SqList *L);							// 输出表

bool ListInsert(SqList *&L, int i, ElemType e);		// 插入元素
bool ListDelete(SqList *&L, int i, ElemType &e);	// 删除数据

void Sort(SqList *&L, int m);						// 排序表
void ListUnion(SqList *&L1, SqList *&L2);			// 合并有序表 

int input(char c);									// sys选择 
void clearInputBuffer();							// 清除缓冲区

int main()
{

	int choice=0;
	char c='N';
	SqList *L;			// 表 1 
	InitList(L);
	
	SqList *L1;			// 表 2 
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
				char c = 'N';
				int n=0,i;
				
				cout<<"\n请输入表 1 的长度:";
				if(scanf("%d",&n)!=1)
				{
					printf("\n输入字符非法!");
					clearInputBuffer();
					break;
				}
				clearInputBuffer();
				
				n<0?n=0:n;							// 限制长度 
				n>MaxSize?n=MaxSize:n=n;
				
				ElemType *a = new ElemType[n]; 		// 动态分配数组
				
				for(i=0;i<n;i++)
					a[i]=rand();	//生成试验数据 
					
				CreateList(L,a,n);
				
				cout<<"\n---- 顺序表 1 已建立! ----";
				delete[] a; // 释放数组
				break;	
			}
			
			case 2: {			// ** 查找系统 **
				char c='N';
    			Search_sys(L);
    			//e=LocateElem(L, e);
				//printf("\n---- 查找到的序号%s,为：%d ----",e?"非空":"空",e);
				break;	
			}
				
			case 4: {			// ** 按位插入 ** 
				char c = 'N';
				int i,j;
				ElemType e;
				
				if(ListEmpty(L)==false)
				{
					// 显示所有元素与其序号的对应关系
			    	cout<<"\n当前表中的元素及其序号对映：\n";
			    	cout<<"______________________________\n";
			    	for(j=1; j<=ListLength(L); j++)
			        	if(GetElem(L, j, e))
			           		cout<<"序号 "<<j<<": \t\t"<<e<<endl;
			        cout<<"______________________________\n";
				} else {
					printf("\n表为空,注意只能在首位插入！！！\n");
				}
				
				printf("\n请输入插入点 (1-%d) :",L->length+1);
				cin>>(i);
				cout<<"\n请输入元素:";
				cin>>(e);
				clearInputBuffer();
				printf("\n---- 插入操作%s ----\n",ListInsert(L,i,e)?"成功！":"失败");
				printf("\n此时顺序表长度为 %d / %d ",ListLength(L),MaxSize);
				break;	
			}
				
			case 5: {			// ** 按位删除 ** 
				char c = 'N';
				int i,j;
				bool success=0;
				ElemType e;
				
				if(ListEmpty(L)==true)
				{
					printf("\n当前表为空,删除操作已退出!");
					break; 
			}
				
				// 显示所有元素与其序号的对应关系
			    cout<<"\n当前表中的元素及其序号对映：\n";
			    cout<<"______________________________\n";
			    for(j=1; j<=ListLength(L); j++)
			        if(GetElem(L, j, e))
			            cout<<"序号 "<<j<<": \t\t"<<e<<endl;
			    cout<<"______________________________\n";
				
				cout<<"\n请输入删除点:";
				cin>>(i);
				
				cout<<"\n要删除的元素为:";
				printf("%d\n",GetElem(L,i,e)?e:0);
				
				cout<<"\n是否确认删除？( Y or N ):";
				cin>>(c);
				clearInputBuffer();
				
				if(c=='Y' || c=='y')
				{
					success=ListDelete(L,i,e);
					printf("\n---- 删除操作%s ----\n",success?"成功！":"失败!!!");
					if(success)
						printf("\n顺序表长度为 %d/%d \n",ListLength(L),MaxSize);
				} else {
					cout<<"\n---- 删除操作已取消! ----"; 
				}
				break;	
			}
			
			case 7: {
				char c = 'N';
				int n=0,i;
				
				cout<<"\n请输入表 2 的长度:";
				cin>>(n);
				clearInputBuffer();
				n>MaxSize?n=MaxSize:n=n;			// 限制长度 
				
				ElemType *a = new ElemType[n]; 		// 动态分配数组
				// ElemType a[n];
				
				if(L1==NULL)
				{
					cout<<"\n---- 表 2 不存在,程序已退出! ----";
					delete[] a; 	// 释放数组
					break;
				}
				
				for(i=0;i<n;i++)
					a[i]=rand();	//生成试验数据 
					
				CreateList(L1,a,n);
				
				cout<<"\n---- 顺序表 2 已建立! ----";
				delete[] a; // 释放数组 
				break;
			}
			
			case 8: {
				char c = 'N';
				int overflow=0;		// 判断是否溢出 
				if(ListEmpty(L1)!=0 || ListEmpty(L1))
				{
					cout<<"\n---- 表 2 为空,程序已退出! ----";
					break;
				}
				
				if(ListEmpty(L) || L->length==MaxSize)
				{
        			cout<<"\n---- 表 1 为空或已满! ----";
        			break;
   				 }
				
				overflow=L->length+L1->length;
				
				Sort(L,L->length);
				Sort(L1,L1->length);
				
				cout<<"\n\n------- 两表已排序! ------";
				cout<<"\n表 1 排序如下:\n\n";
				DispList(L);
				cout<<"\n表 2 排序如下:\n\n";
				DispList(L1);
				
				ListUnion(L,L1);	// 调用合并函数 
				
				cout<<"\n\n------- 两表已合并! ------";
				cout<<"\n表 1 结果如下:\n\n";
				DispList(L);
				printf("\n顺序表 1 长度为 %d/%d \n", ListLength(L), MaxSize);
				printf("\n---- 运算%s ----", overflow>50?"溢出":"未溢出");
				
				InitList(L1);		// 重建表 2 以便继续运行程序 
			
				break;
			}
			
			default: {
				char c = 'N';
				cout<<"\n---- 输入错误! ----\n";

				break;
			}
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
	cout<<"******整型顺序表操作******\n";
	cout<<"--------------------------\n";
	cout<<"      1  建立实验表1      \n";
	cout<<"      2   查询系统        \n";
	cout<<"      3   修改系统        \n";
	cout<<"--------------------------\n";
	cout<<"      7  建立实验表2      \n";
	cout<<"      8  有序表的并       \n";
	cout<<"--------------------------\n";
	cout<<"      0   退出程序        \n";
	cout<<"--------------------------\n";
	cout<<"**************************\n";
	cout<<"请选择：";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 创建空表 **

void InitList(SqList *&L)
{
	L=(SqList *)malloc(sizeof(SqList));
	L->length=0;
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 销毁表 **

void DestroyList(SqList *&L)
{
	free(L);
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 判断是否为空 **	ps:实际改为三值表示表满会更好 

bool ListEmpty(SqList *&L)
{
	return(L->length==0);
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 返回表长度 **

int ListLength(SqList *L)
{
	return(L->length);
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 输入表 **

void CreateList(SqList *&L, ElemType a[], int n)
{
	int i=0,k=0;
	while(i<n)
	{
		L->data[k]=a[i];
		k++;i++;
	}
	L->length=k;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 输出表 **

void DispList(SqList *L)
{
	printf("\n-------------------------------\n\n");
	for(int i=0;i<L->length;i++) {
		printf("%d\t",L->data[i]);
		if((i+1)%4==0)	printf("\n");
	}
	printf("\n-------------------------------\n");
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 查找系统 **

void Search_sys(SqList *L)
{
	int choice;
	char c='N'; 
    do {
    	choice=999; c='N';
		system("cls");
		cout<<"******整型顺序表操作******\n";
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
			case 0: return;
			
			case 1: {
				printf("\n---- 顺序表长度为%d ----",ListLength(L));
				break;
			}
			
			case 2: {
				DispList(L);
				break;
			}
			
            case 3: {
            	int i;
            	bool bl;
            	ElemType e;
            	printf("\n请输入要查找的序号：");
    			cin>>(i);
    			clearInputBuffer();
    			bl=GetElem(L, i, e);
				printf("\n----- %s该序号 -------\n",bl?"查到":"未查到");
				//bl?printf("值为:%d",e):0;
				if(bl)	printf("值为:%d",e);
				break;
			}
			
            case 4: {
            	int Bp=0,count=0;
            	ElemType e;
            	printf("\n请输入要查找的元素值：");
    			cin>>(e);
    			clearInputBuffer();
    			cout<<"\n\n--------------------------\n\n";
    			do {
    					Bp=LocateElem(L, Bp, e);
    					count++;
    					if(Bp!=0)	printf("第%d个匹配元素的位置：%d\n", count, Bp);
				} while(Bp);
    			if(count==1)	printf("未找到值为 %d 的元素位置!\n",e);
    			cout<<"\n--------------------------\n";
				break;
			}
			
            default: {
				cout<<"\n---- 输入错误! ----\n";
			}
        }
    //////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
    } while (choice!=0);
}

// ** 按序查找 **

bool GetElem(SqList *L, int i, ElemType &e)
{
	if(i<1 || i>L->length)
		return false;
	e=L->data[i-1];
	return true; 
} 

// ** 按值查找 **

int LocateElem(SqList *L, int Bp, ElemType e)
{				// Breakpoint 查询断点
	int i;
	for(i=Bp;i<L->length;i++)
		if(L->data[i]==e)
			return i+1;
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 修改系统 **

void upDate_sys(SqList *L)
{
	int choice;
	char c='N'; 
    do {
    	choice=999; c='N';
		system("cls");
		cout<<"******整型顺序表操作******\n";
		cout<<"--------------------------\n";
        cout<<"---------修改系统---------\n";
        cout<<"      1 定点插入元素      \n";
        cout<<"      2 定点修改元素      \n";
        cout<<"      3 查值修改元素      \n";
		cout<<"      4   删除元素        \n";
        cout<<"      0   退出程序        \n";
        cout<<"--------------------------\n";
		cout<<"**************************\n";
        printf("\n请选择 (0-4): ");
        cin>>(c);
        choice=input(c);
        clearInputBuffer();

        switch(choice) {
			case 0: return;
			
			case 1: {
				printf("\n---- 顺序表长度为%d ----",ListLength(L));
				break;
			}
			
			case 2: {
				DispList(L);
				break;
			}
			
            case 3: {
            	int i;
            	bool bl;
            	ElemType e;
            	printf("\n请输入要查找的序号：");
    			cin>>(i);
    			clearInputBuffer();
    			bl=GetElem(L, i, e);
				printf("\n----- %s该序号 -------\n",bl?"查到":"未查到");
				//bl?printf("值为:%d",e):0;
				if(bl)	printf("值为:%d",e);
				break;
			}
			
            case 4: {
            	int Bp=0,count=0;
            	ElemType e;
            	printf("\n请输入要查找的元素值：");
    			cin>>(e);
    			clearInputBuffer();
    			cout<<"\n\n--------------------------\n\n";
    			do {
    					Bp=LocateElem(L, Bp, e);
    					count++;
    					if(Bp!=0)	printf("第%d个匹配元素的位置：%d\n", count, Bp);
				} while(Bp);
    			if(count==1)	printf("未找到值为 %d 的元素位置!\n",e);
    			cout<<"\n--------------------------\n";
				break;
			}
			
            default: {
				cout<<"\n---- 输入错误! ----\n";
			}
        }
    //////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
    } while (choice!=0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 插入元素 **

bool ListInsert(SqList *&L, int i, ElemType e)
{
	int j;
	if(i<1 || i>L->length+1 || L->length==MaxSize)
		return false;
	i--;
	for(j=L->length;j>i;j--)
		L->data[j]=L->data[j-1];
	L->data[i]=e;
	L->length++;
	return true;
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 删除数据 **

bool ListDelete(SqList *&L, int i, ElemType &e)
{
	int j;
	if(i<1 || i>L->length)
		return false;
	i--;
	e=L->data[i];
	for(j=i;j<L->length-1;j++)
		L->data[j]=L->data[j+1];
	L->length--;
	return true;
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 线性表的排序 **

void Sort(SqList *&L, int m)
{
	int i,j;
	int ts;
	
	for(i=1;i<=m;i++)						// 冒泡排序 
		for(j=0;j<m-i;j++)
		    if(L->data[j]>L->data[j+1])
		    {	
				ts=L->data[j];
				L->data[j]=L->data[j+1];
				L->data[j+1]=ts;
			};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 有序表的并 **

void ListUnion(SqList *&L1, SqList *&L2)
{
	int i=0,j=0;
	while(i<L1->length && j<L2->length)
	{
		if(L1->data[i] < L2->data[j])
			i++;							// 若 L1 小，则跳过 
		else
		{
			ListInsert(L1,i+1,L2->data[j]);	// 反之，将 L2 插入 
			j++;
		}
	}
	if(i==L1->length)						// 当 L1 到表尾时 
		while(j<L2->length)					// 将 L2 接到 L1 后 
		{
			ListInsert(L1,i+1,L2->data[j]);
			i++;j++;
		}
	DestroyList(L2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** sys选择 **

int input(char c)
{
	if('0'<=c && '9'>=c) 
		return c-'0';
	else
		return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 清除缓冲区 **

void clearInputBuffer() {
    while(getchar()!='\n');
}

