#include <stdio.h>
#include <cstdlib> 		// 包含system(),rand(),srand()函数的头文件
#include <stdlib.h> 	// 需要包含malloc的头文件
#include <stdbool.h> 	// bool

#define MaxSize 100		// 顺序栈最大容限 

// 栈定义 

typedef enum {
	op,
	num,
} DataType;

typedef union {
	char op;
	double num;
} Element;

typedef struct {
    Element data[MaxSize/50];
    DataType type;
    int top;
} SqStack;

// 函数申明 

void InitStack(SqStack *&s);			// 初始化栈 
void DestroyStack(SqStack *&s);			// 销毁栈 
bool StackEmpty(SqStack *s);			// 判断栈空 
bool StackFull(SqStack *s);				// 判断栈满 
bool Push(SqStack *&s, Element data);	// 入栈 
bool Pop(SqStack *&s, Element &e);		// 出栈 
bool GetTop(SqStack *s, Element &e);	// 取栈顶





int main()
{
	SqStack OPTR; OPTR.type=op;
	SqStack OPND; OPND.type=num;
	char a[MaxSize];
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 栈算法 **

void InitStack(SqStack *&s) {
	s=(SqStack *)malloc(sizeof(SqStack));
	s->top=-1;
} // 初始化栈 

void DestroyStack(SqStack *&s) {
	free(s);
} // 销毁栈 

bool StackEmpty(SqStack *s) {
	return s->top==-1;
} // 栈空？ 

bool StackFull(SqStack *s) {
    return s->top==MaxSize-1;
} // 栈满？ 

bool Push(SqStack *&s, Element e) {
    if(StackFull(s)) return false;
    s->top++;
    s->data[s->top]=e;
    return true;
} // 入栈 

bool Pop(SqStack *&s, Element &e) {
    if(StackEmpty(s)) return false;
    e=s->data[s->top--];
    return true;
} // 出栈 

bool GetTop(SqStack *s, Element &e) {
	if(StackEmpty(s)) return false;
    e=s->data[s->top];
    return true;
} // 取栈顶 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 数字匹配函数 **

double Number(char *a, int Bp) {
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 算符优先级函数 **
char Precede(char op1, char op2) {
	
}

