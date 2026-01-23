#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 100  // 栈的最大容量

typedef enum {    // 数据类型枚举
    OPERATOR,     // 运算符
    OPERAND       // 操作数
} DataType;

// 栈元素结构体，包含类型信息和值
typedef struct {
    DataType type;
    union {
        char op;      // 运算符
        double num;   // 操作数
    } value;
} StackElement;

// 顺序栈结构
typedef struct {
    StackElement data[MAXSIZE];
    int top;        // 栈顶指针
} SqStack;

// 全局变量
char expression[MAXSIZE * 2];  // 存储表达式
int pos = 0;                   // 当前解析位置

// 函数声明
void InitStack(SqStack *&s);
void DestroyStack(SqStack *&s);
bool StackEmpty(SqStack *s);
bool StackFull(SqStack *s);
bool Push(SqStack *&s, StackElement e);
bool Pop(SqStack *&s, StackElement &e);
bool GetTop(SqStack *s, StackElement &e);

double EvaluateExpression();
int Precede(char op1, char op2);
double Operate(double a, char theta, double b);
double ReadNumber();
bool ValidateExpression();
void PreprocessExpression(char *expr);
void Menu();

// ======================== 主函数 ========================
int main() {
    Menu();
    
    while (1) {
        printf("请输入计算表达式（以#结束）或输入N退出: ");
        
        if (fgets(expression, sizeof(expression), stdin) == NULL) {
            printf("输入错误！\n");
            continue;
        }
        
        // 移除换行符
        expression[strcspn(expression, "\n")] = '\0';
        
        // 检查是否要退出
        if (strcmp(expression, "N") == 0 || strcmp(expression, "n") == 0) {
            printf("程序退出。\n");
            break;
        }
        
        // 检查是否以#结束
        int len = strlen(expression);
        if (len > 0 && expression[len-1] != '#') {
            printf("错误：表达式必须以'#'结束！\n\n");
            continue;
        }
        
        // 表达式验证
        if (!ValidateExpression()) {
            printf("表达式有误，请重新输入。\n\n");
            continue;
        }
        
        // 预处理表达式，处理一元负号
        PreprocessExpression(expression);
        
        // 重置解析位置
        pos = 0;
        
        // 计算表达式
        double result = EvaluateExpression();
        printf("计算结果: %.10g\n\n", result);
        
        printf("按任意键继续....");
        getchar(); // 等待按键
    }
    return 0;
}

// ======================== 控制面板 ========================
void Menu() {
    printf("============= 简单表达式求值程序 =============\n");
    printf("                  说明：                      \n");
    printf("0. 退出程序请输入：'N'                        \n");
    printf("1. 输入表达式以    '#'结束                    \n");
    printf("2. 支持实数运算                               \n");
    printf("3. 支持四则运算    (+ - * /)和括号            \n");
    printf("4. 支持一元负号    如：-5, -(3+2)             \n");
    printf("==============================================\n\n");
    printf("示例：50.3*8+25/8*(-5+69*8.6)+8*(-(6*5.6/7))# \n");
    printf("==============================================\n\n");
}

// ======================== 栈的基本操作 ========================
// 初始化栈
void InitStack(SqStack *&s) {
    s = (SqStack *)malloc(sizeof(SqStack));
    if (s == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    s->top = -1;
}

// 销毁栈
void DestroyStack(SqStack *&s) {
    if (s != NULL) {
        free(s);
        s = NULL;
    }
}

// 判断栈是否为空
bool StackEmpty(SqStack *s) {
    return s->top == -1;
}

// 判断栈是否已满
bool StackFull(SqStack *s) {
    return s->top == MAXSIZE - 1;
}

// 入栈操作
bool Push(SqStack *&s, StackElement e) {
    if (StackFull(s)) {
        printf("栈已满，无法入栈！\n");
        return false;
    }
    s->top++;
    s->data[s->top] = e;
    return true;
}

// 出栈操作
bool Pop(SqStack *&s, StackElement &e) {
    if (StackEmpty(s)) {
        return false;
    }
    e = s->data[s->top];
    s->top--;
    return true;
}

// 获取栈顶元素
bool GetTop(SqStack *s, StackElement &e) {
    if (StackEmpty(s)) {
        return false;
    }
    e = s->data[s->top];
    return true;
}

// ======================== 表达式处理函数 ========================
// 预处理表达式：将一元负号转换为(0-x)的形式
void PreprocessExpression(char *expr) {
    char temp[MAXSIZE * 2] = {0};
    int i = 0, j = 0;
    
    // 在表达式开头添加0，如果第一个字符是负号
    if (expr[0] == '-') {
        temp[j++] = '0';
    }
    
    for (i = 0; expr[i] != '\0' && expr[i] != '#'; i++) {
        // 检查是否为一元负号
        if (expr[i] == '-' && (i == 0 || expr[i-1] == '(' || 
                               expr[i-1] == '+' || expr[i-1] == '-' || 
                               expr[i-1] == '*' || expr[i-1] == '/')) {
            // 一元负号，转换为(0-
            temp[j++] = '(';
            temp[j++] = '0';
            temp[j++] = '-';
        } else {
            temp[j++] = expr[i];
        }
    }
    
    // 添加结尾的#符号
    temp[j++] = '#';
    temp[j] = '\0';
    
    // 复制回原表达式
    strcpy(expression, temp);
}

// 验证表达式
bool ValidateExpression() {
    int len = strlen(expression);
    int parenCount = 0;  // 括号计数器
    
    for (int i = 0; i < len; i++) {
        char c = expression[i];
        
        // 检查非法字符
        if (!(c == '+' || c == '-' || c == '*' || c == '/' ||
              c == '(' || c == ')' || c == '#' || c == '.' ||
              (c >= '0' && c <= '9') || c == ' ')) {
            printf("错误：非法字符 '%c'\n", c);
            return false;
        }
        
        // 检查括号匹配
        if (c == '(') {
            parenCount++;
        } else if (c == ')') {
            parenCount--;
            if (parenCount < 0) {
                printf("错误：括号不匹配\n");
                return false;
            }
        }
        
        // 检查小数点
        if (c == '.') {
            if (i == 0 || !isdigit(expression[i-1])) {
                printf("错误：小数点前必须为数字\n");
                return false;
            }
            if (i == len-1 || !isdigit(expression[i+1])) {
                printf("错误：小数点后必须为数字\n");
                return false;
            }
        }
        
        // 检查除零错误
        if (c == '/' && i+1 < len) {
            int j = i+1;
            // 跳过空格
            while (j < len && expression[j] == ' ') j++;
            
            if (expression[j] == '0') {
                // 检查是否是真正的零，而不是像0.5这样的数
                int k = j+1;
                while (k < len && expression[k] == ' ') k++;
                if (k >= len || expression[k] == '#' || expression[k] == '+' || 
                    expression[k] == '-' || expression[k] == '*' || 
                    expression[k] == '/' || expression[k] == ')') {
                    printf("错误：除零错误\n");
                    return false;
                }
            }
        }
    }
    
    // 检查括号是否匹配
    if (parenCount != 0) {
        printf("错误：括号不匹配\n");
        return false;
    }
    
    return true;
}

// 读取数字
double ReadNumber() {
    double result = 0.0;
    double fraction = 0.0;
    int decimalPlaces = 0;
    int sign = 1;
    
    // 处理符号
    if (expression[pos] == '-') {
        sign = -1;
        pos++;
    }
    
    // 读取整数部分
    while (expression[pos] >= '0' && expression[pos] <= '9') {
        result = result * 10 + (expression[pos] - '0');
        pos++;
    }
    
    // 读取小数部分
    if (expression[pos] == '.') {
        pos++;  // 跳过小数点
        while (expression[pos] >= '0' && expression[pos] <= '9') {
            fraction = fraction * 10 + (expression[pos] - '0');
            decimalPlaces++;
            pos++;
        }
        if (decimalPlaces > 0) {
            fraction /= pow(10, decimalPlaces);
        }
    }
    
    result += fraction;
    return result * sign;
}

// 算符优先函数
int Precede(char op1, char op2) {
    // 定义运算符优先级
    int priority[256] = {0};
    priority['+'] = 1;
    priority['-'] = 1;
    priority['*'] = 2;
    priority['/'] = 2;
    priority['('] = 0;  // 左括号在栈内时优先级最低
    priority[')'] = 0;
    priority['#'] = -1;
    
    // 获取优先级
    int p1 = priority[op1];
    int p2 = priority[op2];
    
    // 比较优先级
    if (p1 > p2) return 1;   // op1优先级高
    if (p1 < p2) return -1;  // op2优先级高
    return 0;                // 优先级相等
}

// 运算函数
double Operate(double a, char theta, double b) {
    switch (theta) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (fabs(b) < 1e-10) {
                printf("错误：除数为零\n");
                exit(1);
            }
            return a / b;
        default:
            printf("错误：未知的运算符 '%c'\n", theta);
            exit(1);
    }
}

// ======================== 主表达式求值函数 ========================
double EvaluateExpression() {
    SqStack *OPTR;  // 运算符栈
    SqStack *OPND;  // 操作数栈
    StackElement e, e1, e2;
    char theta;
    double a, b;
    
    // 初始化栈
    InitStack(OPTR);
    InitStack(OPND);
    
    // 将结束符'#'压入运算符栈
    e.type = OPERATOR;
    e.value.op = '#';
    Push(OPTR, e);
    
    // 主循环
    while (true) {
        // 跳过空格
        while (expression[pos] == ' ') {
            pos++;
        }
        
        // 检查是否到达结束符
        if (expression[pos] == '#') {
            break;
        }
        
        // 如果是数字
        if ((expression[pos] >= '0' && expression[pos] <= '9') || 
            (expression[pos] == '-' && 
             (pos == 0 || expression[pos-1] == '(' || expression[pos-1] == '+' || 
              expression[pos-1] == '-' || expression[pos-1] == '*' || 
              expression[pos-1] == '/' || expression[pos-1] == '#'))) {
            
            double num = ReadNumber();
            e.type = OPERAND;
            e.value.num = num;
            Push(OPND, e);
        }
        // 如果是左括号
        else if (expression[pos] == '(') {
            e.type = OPERATOR;
            e.value.op = '(';
            Push(OPTR, e);
            pos++;
        }
        // 如果是右括号
        else if (expression[pos] == ')') {
            // 弹出运算符直到遇到左括号
            while (true) {
                GetTop(OPTR, e1);
                if (e1.type == OPERATOR && e1.value.op == '(') {
                    Pop(OPTR, e);  // 弹出左括号
                    break;
                }
                
                // 弹出运算符
                Pop(OPTR, e);
                theta = e.value.op;
                
                // 弹出两个操作数
                Pop(OPND, e2);
                b = e2.value.num;
                
                Pop(OPND, e2);
                a = e2.value.num;
                
                // 计算并压回结果
                double result = Operate(a, theta, b);
                e.type = OPERAND;
                e.value.num = result;
                Push(OPND, e);
            }
            pos++;
        }
        // 如果是运算符
        else if (expression[pos] == '+' || expression[pos] == '-' || 
                 expression[pos] == '*' || expression[pos] == '/') {
            
            // 获取栈顶运算符
            GetTop(OPTR, e1);
            char op1 = e1.value.op;
            char op2 = expression[pos];
            
            int relation = Precede(op1, op2);
            
            if (relation == -1) {  // 当前运算符优先级高
                e.type = OPERATOR;
                e.value.op = op2;
                Push(OPTR, e);
                pos++;
            } 
            else if (relation == 1) {  // 栈顶运算符优先级高，执行运算
                // 弹出运算符
                Pop(OPTR, e);
                theta = e.value.op;
                
                // 弹出两个操作数
                Pop(OPND, e2);
                b = e2.value.num;
                
                Pop(OPND, e2);
                a = e2.value.num;
                
                // 计算并压回结果
                double result = Operate(a, theta, b);
                e.type = OPERAND;
                e.value.num = result;
                Push(OPND, e);
                // 注意：这里不移动pos，需要继续比较当前运算符
            } 
            else {  // 优先级相等，弹出栈顶运算符
                Pop(OPTR, e);
                pos++;
            }
        }
        else {
            printf("错误：未预期的字符 '%c'\n", expression[pos]);
            DestroyStack(OPTR);
            DestroyStack(OPND);
            return 0.0;
        }
    }
    
    // 处理栈中剩余的运算符
    while (!StackEmpty(OPTR)) {
        GetTop(OPTR, e1);
        if (e1.type == OPERATOR && e1.value.op == '#') {
            Pop(OPTR, e);
            break;
        }
        
        // 弹出运算符
        Pop(OPTR, e);
        theta = e.value.op;
        
        // 弹出两个操作数
        Pop(OPND, e2);
        b = e2.value.num;
        
        Pop(OPND, e2);
        a = e2.value.num;
        
        // 计算并压回结果
        double result = Operate(a, theta, b);
        e.type = OPERAND;
        e.value.num = result;
        Push(OPND, e);
    }
    
    // 获取最终结果
    Pop(OPND, e);
    double final_result = e.value.num;
    
    // 销毁栈
    DestroyStack(OPTR);
    DestroyStack(OPND);
    
    return final_result;
}
