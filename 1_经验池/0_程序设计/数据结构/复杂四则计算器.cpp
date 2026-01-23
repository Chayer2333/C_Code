#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MAXSIZE 100  // 栈的最大容量

typedef enum {	// 数据类型枚举
    OPERATOR,   // 运算符
    OPERAND     // 操作数
} DataType;

typedef union {	// 栈元素联合体
    char op;    // 运算符
    double num; // 操作数
} Element;

typedef struct {	// 顺序栈结构
    Element data[MAXSIZE];
    DataType type;  // 栈的数据类型
    int top;        // 栈顶指针
} SqStack;

// 全局变量
char expression[MAXSIZE*2];   // 存储表达式
int  pos = 0;                 // 当前解析位置

// 函数声明
void Menu();				  // 控制面板

void InitStack(SqStack *&s);
void DestroyStack(SqStack *&s);
bool StackEmpty(SqStack *s);
bool StackFull(SqStack *s);
bool Push(SqStack *&s, Element e);
bool Pop(SqStack *&s, Element &e);
bool GetTop(SqStack *s, Element &e);

double EvaluateExpression(char startChar, char endChar);
int Precede(char op1, char op2);
double Operate(double a, char theta, double b);
double Number(int *index);
bool ValidateChar(int pos);

void Pause();
void clearInputBuffer();

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    while(1){
    	
        Menu();

        printf("请输入计算表达式（以#结束）: ");
        if (fgets(expression, sizeof(expression), stdin)==NULL) {
            printf("输入错误！\n");
            Pause();
            continue;
        }
        
        // 移除换行符
        expression[strcspn(expression, "\n")]='\0';
        
        // 检查是否以#结束
        int len=strlen(expression);
        if (len>0 && expression[len-1]!='#') {
            printf("\n错误表达式必须以'#'结束！\n");
			Pause();
            continue;
        }
        
        if (strcmp(expression, "exit#")==0 || strcmp(expression, "quit#")==0) {
            printf("程序退出。\n");
            break;
        }
        
        // 表达式验证
        bool valid = true;
        for (int i=0; i<strlen(expression); i++) {
            if (!ValidateChar(i)) {
                valid=false;
                break;
            }
        }
        
        if (!valid) {
            printf("表达式有误，请重新输入。\n\n");
            Pause();
            continue;
        }
        
        // 重置解析位置
        pos = 0;
        
        // 计算表达式
        double result=EvaluateExpression('\0', '#'); 
        printf("\n计算结果: %.10g\n", result);
        
        Pause();
	}
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Menu()
{
	system("cls");
	printf("============= 简单表达式求值程序 =============\n");
    printf("===   ===    === === 说明 === ===    ===   ===\n");
    printf("0. 输入以下字符串退出：    quit# 或 exit#     \n"); 
    printf("1. 输入表达式以            '#'结束            \n");
    printf("2. 支持实数运算            如：3.2              \n");
    printf("3. 支持四则运算            (+ - * /)和括号    \n");
    printf("4. 支持一元负号            如：-5, -(3+2)     \n");
    printf("==============================================\n");
    printf("示例：50.3*8+25/8*(-5+69*8.6)+8*(-6*5.6/7)# \n");
    printf("==============================================\n\n");
};
 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化栈
void InitStack(SqStack *&s) {
    s=(SqStack *)malloc(sizeof(SqStack));
    if (s==NULL) {
        printf("内存分配失败！\n"); Pause();
        exit(1);
    }
    s->top=-1;
}

// 销毁栈
void DestroyStack(SqStack *&s) {
    if (s!=NULL) {
        free(s);
        s=NULL;
    }
}

// 判断栈是否为空
bool StackEmpty(SqStack *s) {
    return s->top==-1;
}

// 判断栈是否已满
bool StackFull(SqStack *s) {
    return s->top==MAXSIZE-1;
}

// 入栈操作
bool Push(SqStack *&s, Element e) {
    if (StackFull(s)) {
        printf("栈已满，无法入栈！\n"); Pause();
        return false;
    }
    s->top++;
    s->data[s->top] = e;
    return true;
}

// 出栈操作
bool Pop(SqStack *&s, Element &e) {
    if (StackEmpty(s)) {
        return false;
    }
    e=s->data[s->top];
    s->top--;
    return true;
}

// 获取栈顶元素
bool GetTop(SqStack *s, Element &e) {
    if (StackEmpty(s)) {
        return false;
    }
    e=s->data[s->top];
    return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 字符验证函数
bool ValidateChar(int pos) {
    if (pos<0 || pos>=strlen(expression)) return false;
    
    char current=expression[pos];
    char prev=pos>0?expression[pos-1]:'\0';
    char next=expression[pos+1];
    
    if (!(current=='+' || current=='-' || current=='*' || 
          current=='/' || current=='(' || current==')' || 
          current=='#' || current=='.' || 
          (current>='0' && current<='9'))) {
        printf("\n错误非法字符 '%c'\n", current);
        Pause();
        return false;
    }
    
    if (current=='/' && next=='0' && 
        (pos+2>=strlen(expression) || expression[pos+2]<'0' || expression[pos+2]>'9')) {
        printf("\n错误除零错误\n");
        Pause();
        return false;
    }
    
    if (current=='.') {
        if (pos==0 || !(prev>='0' && prev<='9')) {
            printf("\n错误小数点前必须为数字\n");
            Pause();
            return false;
        }
        if (next=='\0' || !(next>='0' && next<='9')) {
            printf("\n错误小数点后必须为数字\n");
            Pause();
            return false;
        }
    }
    
    // 检查连续的运算符
    if ((current=='+' || current=='-' || current=='*' || current=='/') &&
        (prev=='+' || prev=='-' || prev =='*' || prev=='/')) {
        // 允许一元负号的情况：如 "*-"、"+-"、"(-" 等
        if (!(prev=='*' && current=='-') &&
            !(prev=='/' && current=='-') &&
            !(prev=='+' && current=='-') &&
            !(prev=='-' && current=='-') &&
            !(prev=='(' && current=='-')) {
            printf("\n错误连续的运算符 '%c%c'\n", prev, current);
            Pause();
            return false;
        }
    }
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 数字转换函数
double Number(int *index) {
    int i = *index;
    int sign = 1;  // 符号，1为正数，-1为负数
    double integer_part=0.0;
    double fraction_part=0.0;
    double result=0.0;
    int fraction_digits=0;
    
    // 处理一元负号
    if (expression[i]=='-') {
        // 判断是否为一元负号
        if (i==0 || expression[i-1]=='(' || expression[i-1]=='+' || 
            expression[i-1]=='-' || expression[i-1]=='*' || 
            expression[i-1]=='/' || expression[i-1]=='#') {
            sign=-1;
            i++;
        }
    }
    
    // 处理整数部分
    while (expression[i]>='0' && expression[i]<='9') {
        integer_part=integer_part*10+(expression[i]-'0');
        i++;
    }
    
    // 处理小数部分
    if (expression[i]=='.') {
        i++;  // 跳过小数点
        while(expression[i]>='0' && expression[i]<='9') {
            fraction_part=fraction_part*10+(expression[i]-'0');
            fraction_digits++;
            i++;
        }
        if (fraction_digits>0) {
            fraction_part/=pow(10, fraction_digits);
        }
    }
    
    result=(integer_part+fraction_part)*sign;
    *index=i;  // 更新索引
    
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 算符优先函数
int Precede(char op1, char op2) {
    int f1=0;
    int f2=0;
    
    // 定义优先级函数f1（栈顶运算符）
    switch (op1) {
        case '+':f1=2; break;
        case '-':f1=2; break;
        case '*':f1=4; break;
        case '/':f1=4; break;
        case '(':f1=6; break;
        case '#':f1=0; break;
        default: f1=-1; break;
    }
    
    // 定义优先级函数f2（当前运算符）
    switch (op2) {
        case '+':f2=1; break;
        case '-':f2=1; break;
        case '*':f2=3; break;
        case '/':f2=3; break;
        case '(':f2=5; break;
        case ')':f2=0; break;
        case '#':f2=0; break;
        default: f2= -1; break;
    }
    
    // 返回优先级比较结果
    if(f1>f2) return 1;  // op1优先级高于op2
    if(f1<f2) return -1; // op1优先级低于op2
    return 0;            // op1优先级等于op2
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 运算函数
double Operate(double a, char theta, double b) {
    switch (theta) {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': 
            if (fabs(b)<1e-10) {
                printf("\n错误除数为零\n");
                Pause();
                exit(1);
            }
            return a/b;
        default:
            printf("\n错误未知的运算符 '%c'\n", theta);
            Pause();
            exit(1);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 求值函数
double EvaluateExpression(char startChar, char endChar) {
    SqStack *OPTR;  // 运算符栈
    SqStack *OPND;  // 操作数栈
    Element e1, e2, e;
    char theta;
    double a, b;
    
    InitStack(OPTR);
    InitStack(OPND);
    
    e.op='#';
    e1.op='#';
    Push(OPTR, e);
    
    if(startChar=='(') {
        pos++; // 跳过左括号
    }
    
    // 主循环
    while (true) {
        while(expression[pos]==' ') {
            pos++;
        }
        
        // 检查是否到达结束符
        if (expression[pos]==endChar) {
            if (endChar==')') {
                pos++; // 跳过右括号
            }
            break;
        }
        
        // 处理数字
        if ((expression[pos]>='0' && expression[pos]<='9') || 
            (expression[pos]=='-' && 
             (pos==0 || expression[pos-1]=='(' || expression[pos-1]=='+' || 
              expression[pos-1]=='-' || expression[pos-1]=='*' || 
              expression[pos-1]=='/' || expression[pos-1]=='#'))) {
            
            int currentPos=pos;
            double num=Number(&pos);
            e.num=num;
            e1.num=num;
            Push(OPND, e);
            
            // 验证数字字符
            for (int i=currentPos; i<pos; i++) {
                if (!ValidateChar(i)) {
                    DestroyStack(OPTR);
                    DestroyStack(OPND);
                    return 0.0;
                }
            }
        }
        // 归处理括号内的表达式
        else if(expression[pos]=='(') {
            double bracketResult=EvaluateExpression('(', ')');
            e.num=bracketResult;
            Push(OPND, e);
        }
		
        else if(expression[pos]=='+' || expression[pos]=='-' || 
                expression[pos]=='*' || expression[pos]=='/') {
            
            GetTop(OPTR, e1);
            char op1=e1.op;
            char op2=expression[pos];
            
            int relation=Precede(op1, op2);
            
            if (relation==-1) {
                e.op=op2;
                Push(OPTR, e);
                pos++;
            } 
            else if(relation==1) {
                Pop(OPTR, e);
                theta=e.op;
                
                Pop(OPND, e2);
                b=e2.num;
                
                Pop(OPND, e2);
                a=e2.num;
                
                double result=Operate(a, theta, b);
                e.num=result;
                Push(OPND, e);
            } 
            else {  // 优先级相等，为括号匹配或结束符
                Pop(OPTR, e);
                pos++;
            }
        }
        else {
            printf("\n错误未知的字符 '%c'\n", expression[pos]);
            Pause();
            DestroyStack(OPTR);
            DestroyStack(OPND);
            return 0.0;
        }
    }
    
    // 处理栈中剩余的运算符
    while (!StackEmpty(OPTR)) {
        GetTop(OPTR, e1);
        if(e1.op=='#') {
            Pop(OPTR, e);
            break;
        }
        
        Pop(OPTR, e);
        theta=e.op;
        
        Pop(OPND, e2);
        b=e2.num;
        
        Pop(OPND, e2);
        a=e2.num;
        
        double result=Operate(a, theta, b);
        e.num=result;
        Push(OPND, e);
    }
    
    // 获取最终结果
    Pop(OPND, e);
    double final_result=e.num;
    
    // 销毁栈
    DestroyStack(OPTR);
    DestroyStack(OPND);
    
    return final_result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Pause() {
	printf("\n按任意键继续....");
    char t=getchar();
	clearInputBuffer();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ** 清除缓冲区 **
void clearInputBuffer() {
    while(getchar()!='\n');
}
