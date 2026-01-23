#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MAXSIZE 100  // 栈的最大容量

// 栈元素联合体
typedef union {
    char op;    // 运算符
    double num; // 操作数
} Element;

// 顺序栈结构
typedef struct {
    Element data[MAXSIZE];
    int top;    // 栈顶指针
} SqStack;

// 全局变量
char expr[256];     // 存储表达式
int expr_pos = 0;   // 当前解析位置
int expr_len = 0;   // 表达式长度

// 函数声明
void InitStack(SqStack *s);
bool StackEmpty(SqStack *s);
bool StackFull(SqStack *s);
bool Push(SqStack *s, Element e);
bool Pop(SqStack *s, Element *e);
bool GetTop(SqStack *s, Element *e);

double EvaluateExpression();
double EvaluateSubExpression();
int GetPriority(char op, int is_in_stack);
double StringToNumber(int *pos);
double Calculate(double a, char op, double b);

// ======================== 栈的基本操作 ========================

// 初始化栈
void InitStack(SqStack *s) {
    s->top = -1;
}

// 判断栈是否为空
bool StackEmpty(SqStack *s) {
    return s->top == -1;
}

// 判断栈是否已满
bool StackFull(SqStack *s) {
    return s->top >= MAXSIZE - 1;
}

// 入栈操作
bool Push(SqStack *s, Element e) {
    if (StackFull(s)) {
        return false;
    }
    s->top++;
    s->data[s->top] = e;
    return true;
}

// 出栈操作
bool Pop(SqStack *s, Element *e) {
    if (StackEmpty(s)) {
        return false;
    }
    *e = s->data[s->top];
    s->top--;
    return true;
}

// 获取栈顶元素
bool GetTop(SqStack *s, Element *e) {
    if (StackEmpty(s)) {
        return false;
    }
    *e = s->data[s->top];
    return true;
}

// ======================== 辅助函数 ========================

// 获取运算符优先级
int GetPriority(char op, int is_in_stack) {
    // is_in_stack: 1表示栈内优先级，0表示栈外优先级
    
    switch (op) {
        case '+':
        case '-':
            return is_in_stack ? 2 : 1;
        case '*':
        case '/':
            return is_in_stack ? 4 : 3;
        case '(':
            return is_in_stack ? 0 : 6;  // 左括号在栈内优先级最低，栈外最高
        case ')':
            return 0;  // 右括号只在栈外出现
        case '#':
            return 0;
        default:
            return -1;  // 非法运算符
    }
}

// 字符串转数字
double StringToNumber(int *pos) {
    int start = *pos;
    int sign = 1;
    
    // 处理一元负号
    if (expr[start] == '-') {
        // 判断是否为一元负号
        if (start == 0 || 
            expr[start-1] == '(' || 
            expr[start-1] == '+' || 
            expr[start-1] == '-' || 
            expr[start-1] == '*' || 
            expr[start-1] == '/' ||
            expr[start-1] == '=') {
            sign = -1;
            start++;
        }
    }
    
    double integer_part = 0.0;
    double decimal_part = 0.0;
    double decimal_weight = 0.1;
    int in_decimal = 0;
    
    int i = start;
    while (i < expr_len) {
        char c = expr[i];
        
        if (c >= '0' && c <= '9') {
            if (!in_decimal) {
                integer_part = integer_part * 10 + (c - '0');
            } else {
                decimal_part = decimal_part + (c - '0') * decimal_weight;
                decimal_weight *= 0.1;
            }
            i++;
        } else if (c == '.' && !in_decimal) {
            in_decimal = 1;
            i++;
        } else {
            break;
        }
    }
    
    double result = (integer_part + decimal_part) * sign;
    *pos = i;
    return result;
}

// 执行计算
double Calculate(double a, char op, double b) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (fabs(b) < 1e-10) {
                printf("错误：除数为零！\n");
                exit(1);
            }
            return a / b;
        default:
            printf("错误：未知运算符 '%c'\n", op);
            exit(1);
    }
}

// ======================== 表达式求值函数 ========================

// 求值子表达式（处理括号）
double EvaluateSubExpression() {
    SqStack op_stack;  // 运算符栈
    SqStack num_stack; // 操作数栈
    Element e1, e2, result;
    
    InitStack(&op_stack);
    InitStack(&num_stack);
    
    // 将结束符'#'压入运算符栈
    e1.op = '#';
    Push(&op_stack, e1);
    
    while (expr_pos < expr_len) {
        // 跳过空格
        while (expr_pos < expr_len && expr[expr_pos] == ' ') {
            expr_pos++;
        }
        
        if (expr_pos >= expr_len) break;
        
        char current = expr[expr_pos];
        
        // 处理数字
        if ((current >= '0' && current <= '9') || 
            (current == '-' && 
             (expr_pos == 0 || 
              expr[expr_pos-1] == '(' || 
              expr[expr_pos-1] == '+' || 
              expr[expr_pos-1] == '-' || 
              expr[expr_pos-1] == '*' || 
              expr[expr_pos-1] == '/'))) {
            
            double num = StringToNumber(&expr_pos);
            e1.num = num;
            Push(&num_stack, e1);
        }
        // 处理左括号
        else if (current == '(') {
            expr_pos++;  // 跳过左括号
            // 递归处理括号内的表达式
            double sub_result = EvaluateSubExpression();
            e1.num = sub_result;
            Push(&num_stack, e1);
        }
        // 处理右括号
        else if (current == ')') {
            expr_pos++;  // 跳过右括号
            break;  // 括号结束，返回
        }
        // 处理运算符
        else if (current == '+' || current == '-' || 
                 current == '*' || current == '/' || 
                 current == '#') {
            
            char top_op;
            if (GetTop(&op_stack, &e1)) {
                top_op = e1.op;
                
                // 比较优先级
                int top_priority = GetPriority(top_op, 1);
                int curr_priority = GetPriority(current, 0);
                
                while (top_priority >= curr_priority && top_op != '(' && top_op != '#') {
                    // 弹出运算符和两个操作数进行计算
                    Pop(&op_stack, &e1);
                    char op = e1.op;
                    
                    Pop(&num_stack, &e1);
                    double b = e1.num;
                    
                    Pop(&num_stack, &e1);
                    double a = e1.num;
                    
                    double calc_result = Calculate(a, op, b);
                    e1.num = calc_result;
                    Push(&num_stack, e1);
                    
                    if (!GetTop(&op_stack, &e1)) break;
                    top_op = e1.op;
                    top_priority = GetPriority(top_op, 1);
                }
                
                // 当前运算符入栈
                if (current != '#') {
                    e1.op = current;
                    Push(&op_stack, e1);
                }
            }
            
            if (current == '#') {
                expr_pos++;
                break;  // 结束符，返回
            } else {
                expr_pos++;
            }
        }
        // 非法字符
        else {
            printf("错误：非法字符 '%c'\n", current);
            exit(1);
        }
    }
    
    // 处理栈中剩余的运算符
    while (GetTop(&op_stack, &e1) && e1.op != '#' && e1.op != '(') {
        Pop(&op_stack, &e1);
        char op = e1.op;
        
        Pop(&num_stack, &e1);
        double b = e1.num;
        
        Pop(&num_stack, &e1);
        double a = e1.num;
        
        double calc_result = Calculate(a, op, b);
        e1.num = calc_result;
        Push(&num_stack, e1);
    }
    
    // 获取最终结果
    Pop(&num_stack, &result);
    return result.num;
}

// 主求值函数
double EvaluateExpression() {
    // 添加结束符#
    expr_len = strlen(expr);
    if (expr_len > 0 && expr[expr_len-1] != '#') {
        strcat(expr, "#");
        expr_len = strlen(expr);
    }
    
    expr_pos = 0;  // 重置解析位置
    
    return EvaluateSubExpression();
}

// ======================== 测试函数 ========================

void TestExpression(char *test_expr, double expected) {
    strcpy(expr, test_expr);
    double result = EvaluateExpression();
    printf("表达式: %s\n", test_expr);
    printf("计算结果: %.10g\n", result);
    printf("期望结果: %.10g\n", expected);
    printf("结果: %s\n\n", fabs(result - expected) < 1e-5 ? "正确" : "错误");
}

// ======================== 主函数 ========================

int main() {
    printf("========== 简单表达式求值程序 ==========\n");
    printf("说明：\n");
    printf("1. 输入表达式以'#'结束\n");
    printf("2. 支持实数运算（包括小数）\n");
    printf("3. 支持四则运算(+ - * /)和括号\n");
    printf("4. 支持一元负号（如：-5, -(3+2)）\n");
    printf("5. 示例：50.3*8+25/8*(-5+69*8.6)+8*(-(6*5.6/7))#\n");
    printf("========================================\n\n");
    
    // 测试表达式
    printf("=== 测试表达式 ===\n");
    
    // 简单测试
    TestExpression("1+2*3#", 7.0);
    TestExpression("(1+2)*3#", 9.0);
    TestExpression("10/2-3#", 2.0);
    TestExpression("-5+3#", -2.0);
    TestExpression("2.5*4#", 10.0);
    TestExpression("-(3+2)*4#", -20.0);
    
    // 复杂表达式测试
    strcpy(expr, "50.3*8+25/8*(-5+69*8.6)+8*(-(6*5.6/7))#");
    double result = EvaluateExpression();
    printf("表达式: 50.3*8+25/8*(-5+69*8.6)+8*(-(6*5.6/7))#\n");
    printf("计算结果: %.10g\n", result);
    printf("期望结果: 2202.75\n");
    printf("结果: %s\n\n", fabs(result - 2202.75) < 1e-2 ? "正确" : "错误");
    
    // 分步计算验证
    printf("=== 分步计算验证 ===\n");
    
    // 计算各部分
    double part1 = 50.3 * 8;  // 402.4
    double part2 = 69 * 8.6;  // 593.4
    double part3 = -5 + part2;  // 588.4
    double part4 = 25.0 / 8.0;  // 3.125
    double part5 = part4 * part3;  // 3.125 * 588.4 = 1838.75
    double part6 = 6 * 5.6 / 7;  // 33.6 / 7 = 4.8
    double part7 = -part6;  // -4.8
    double part8 = 8 * part7;  // -38.4
    
    double total = part1 + part5 + part8;  // 402.4 + 1838.75 - 38.4 = 2202.75
    
    printf("part1 (50.3*8) = %.2f\n", part1);
    printf("part2 (69*8.6) = %.2f\n", part2);
    printf("part3 (-5+69*8.6) = %.2f\n", part3);
    printf("part4 (25/8) = %.3f\n", part4);
    printf("part5 (25/8*(-5+69*8.6)) = %.2f\n", part5);
    printf("part6 (6*5.6/7) = %.2f\n", part6);
    printf("part7 (-(6*5.6/7)) = %.2f\n", part7);
    printf("part8 (8*(-(6*5.6/7))) = %.2f\n", part8);
    printf("总计 = %.2f\n\n", total);
    
    // 交互式输入
    printf("=== 交互式计算 ===\n");
    while (1) {
        printf("请输入表达式（以#结束，输入exit#退出）: ");
        
        if (fgets(expr, sizeof(expr), stdin) == NULL) {
            break;
        }
        
        // 移除换行符
        expr[strcspn(expr, "\n")] = '\0';
        
        if (strcmp(expr, "exit#") == 0 || strcmp(expr, "quit#") == 0) {
            printf("程序退出。\n");
            break;
        }
        
        // 确保以#结束
        expr_len = strlen(expr);
        if (expr_len > 0 && expr[expr_len-1] != '#') {
            strcat(expr, "#");
        }
        
        expr_pos = 0;
        double result = EvaluateExpression();
        printf("结果: %.10g\n\n", result);
    }
    
    return 0;
}
