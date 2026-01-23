#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACK_SIZE 100

// 栈结构
typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} Stack;

// 初始化栈
void initStack(Stack *s) {
    s->top = -1;
}

// 判断栈是否为空
int isEmpty(Stack *s) {
    return s->top == -1;
}

// 判断栈是否已满
int isFull(Stack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

// 入栈
void push(Stack *s, char c) {
    if (isFull(s)) {
        printf("栈已满!\n");
        return;
    }
    s->data[++(s->top)] = c;
}

// 出栈
char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("栈为空!\n");
        return '\0';
    }
    return s->data[(s->top)--];
}

// 获取栈顶元素
char peek(Stack *s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->data[s->top];
}

// 运算符优先级比较
// 返回: 1 表示 op1 优先级高于 op2
//       0 表示 op1 优先级等于 op2
//       -1 表示 op1 优先级低于 op2
int precedence(char op1, char op2) {
    int p1, p2;
    
    // 定义优先级
    switch(op1) {
        case '+': case '-': p1 = 1; break;
        case '*': case '/': p1 = 2; break;
        case '(': p1 = 0; break;
        default: p1 = -1;
    }
    
    switch(op2) {
        case '+': case '-': p2 = 1; break;
        case '*': case '/': p2 = 2; break;
        case '(': p2 = 3; break;  // 左括号优先级最高
        default: p2 = -1;
    }
    
    if (p1 > p2) return 1;
    else if (p1 == p2) return 0;
    else return -1;
}

// 判断是否为运算符
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

// 执行运算
int applyOperator(char op, int a, int b) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("错误: 除零错误\n");
                exit(1);
            }
            return a / b;
        default: 
            printf("错误: 未知运算符 %c\n", op);
            return 0;
    }
}

// 将中缀表达式转换为后缀表达式
void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int i = 0, j = 0;
    char token, top;
    
    printf("转换过程:\n");
    
    while (infix[i] != '\0') {
        token = infix[i];
        
        if (isspace(token)) {
            i++;
            continue;
        }
        
        printf("当前字符: %c, 栈: ", token);
        for (int k = 0; k <= s.top; k++) {
            printf("%c ", s.data[k]);
        }
        printf("\n");
        
        if (isdigit(token)) {
            // 如果是数字，直接输出到后缀表达式
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';  // 用空格分隔数字
            continue;
        } else if (token == '(') {
            // 左括号直接入栈
            push(&s, token);
        } else if (token == ')') {
            // 右括号：弹出栈中元素直到遇到左括号
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            if (!isEmpty(&s) && peek(&s) == '(') {
                pop(&s);  // 弹出左括号
            }
        } else if (isOperator(token)) {
            // 运算符：弹出栈中优先级更高或相等的运算符
            while (!isEmpty(&s) && peek(&s) != '(' && 
                   precedence(peek(&s), token) >= 0) {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            push(&s, token);
        }
        i++;
    }
    
    // 弹出栈中所有剩余运算符
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
        postfix[j++] = ' ';
    }
    
    postfix[j] = '\0';
}

// 计算后缀表达式的值
int evaluatePostfix(char* postfix) {
    Stack s;
    initStack(&s);
    int i = 0;
    char token;
    int operand1, operand2, result;
    char numStr[20];
    int numIndex = 0;
    
    printf("\n计算过程:\n");
    
    while (postfix[i] != '\0') {
        token = postfix[i];
        
        if (isdigit(token)) {
            // 构建数字
            numStr[numIndex++] = token;
            numStr[numIndex] = '\0';
        } else if (token == ' ' && numIndex > 0) {
            // 数字结束，转换为整数并入栈
            push(&s, atoi(numStr));
            numIndex = 0;
            printf("压入操作数: %s\n", numStr);
        } else if (isOperator(token) && token != '(' && token != ')') {
            // 运算符：弹出两个操作数，计算后结果入栈
            operand2 = pop(&s);
            operand1 = pop(&s);
            result = applyOperator(token, operand1, operand2);
            push(&s, result);
            printf("计算: %d %c %d = %d\n", operand1, token, operand2, result);
        }
        i++;
    }
    
    return pop(&s);
}

int main() {
    char infix[100];
    char postfix[200];
    int result;
    
    printf("请输入算术表达式 (支持 +, -, *, /, 括号): ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = 0;  // 移除换行符
    
    printf("\n中缀表达式: %s\n", infix);
    
    // 转换为后缀表达式
    infixToPostfix(infix, postfix);
    printf("\n后缀表达式: %s\n", postfix);
    
    // 计算后缀表达式
    result = evaluatePostfix(postfix);
    printf("\n最终结果: %d\n", result);
    
    return 0;
}
