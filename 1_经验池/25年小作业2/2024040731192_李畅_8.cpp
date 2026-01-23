#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>

using namespace std;

typedef char ElemType;

typedef struct BTNode {
    ElemType data;
    struct BTNode *lchild, *rchild;
} BTNode;

void Menu(); 						// 控制面板
void CreateBiTree(BTNode *&b); 		// 建立二叉链表
void PreOrder(BTNode *b); 			// 先序遍历
void InOrder(BTNode *b); 			// 中序遍历
void PostOrder(BTNode *b); 			// 后序遍历
void CountNodes(BTNode *b, int &leaf, int &single, int &doubleNode); // 统计节点
int  Height(BTNode *b); 			// 计算高度
void SwapTree(BTNode *b); 			// 交换左右孩子
void DestroyBiTree(BTNode *&b); 	// 销毁二叉链表

int  input(char c); 				// sys选择
bool Input(const char *s, int *n); 	// 整型验证
void clearInputBuffer(); 			// 清除缓冲区

int main() {
    int choice=0;
    char c='N';
    BTNode *b=NULL; 				// 二叉树根节点
    
    srand(time(NULL)); 				// 生成随机数种子
    
    do {
        choice = 0;
        c='N';
        Menu();
        cin>>c;
        choice=input(c);
        clearInputBuffer();
        
        switch(choice) {
            case 0: { // 退出指令
                DestroyBiTree(b);
                cout<<"\n二叉链表已销毁。\n";
                cout<<"\n系统已退出。\n";
                break;
            }
            
            case 1: { // 建立二叉链表
                DestroyBiTree(b); // 先销毁之前的树
                cout<<"\n请输入带空指针标记的先序遍历序列(用#表示空节点):\n";
                cout<<"例如: ABD##E##CF###\n";
                CreateBiTree(b);
                cout<<"\n--- 二叉链表建立完成! ---\n";
                clearInputBuffer();
                break;
            }
            
            case 2: { // 先序遍历
                if(b==NULL) {
                    cout<<"\n--- 二叉树为空! ---\n";
                } else {
                    cout<<"\n先序遍历结果: ";
                    PreOrder(b);
                    cout<<endl;
                }
                break;
            }
            
            case 3: { // 中序遍历
                if(b==NULL) {
                    cout<<"\n--- 二叉树为空! ---\n";
                } else {
                    cout<<"\n中序遍历结果: ";
                    InOrder(b);
                    cout<<endl;
                }
                break;
            }
            
            case 4: { // 后序遍历
                if(b==NULL) {
                    cout<<"\n--- 二叉树为空! ---\n";
                } else {
                    cout<<"\n后序遍历结果: ";
                    PostOrder(b);
                    cout<<endl;
                }
                break;
            }
            
            case 5: { // 统计节点
                if(b==NULL) {
                    cout<<"\n--- 二叉树为空! ---\n";
                } else {
                    int leaf=0, single=0, doubleNode=0;
                    CountNodes(b, leaf, single, doubleNode);
                    cout<<"\n--- 节点统计结果 ---\n";
                    cout<<"   叶子节点数:   "<<leaf<<endl;
                    cout<<"   单分支节点数: "<<single<<endl;
                    cout<<"   双分支节点数: "<<doubleNode<<endl;
                    cout<<"   总节点数:     "<<(leaf+single+doubleNode)<<endl;
                }
                break;
            }
            
            case 6: { // 计算高度
                if(b==NULL) {
                    cout<<"\n--- 二叉树为空! ---\n";
                } else {
                    int h=Height(b);
                    cout<<"\n二叉树的高度为: "<<h<<endl;
                }
                break;
            }
            
            case 7: { // 交换左右孩子
                if(b==NULL) {
                    cout<<"\n--- 二叉树为空! ---\n";
                } else {
                    SwapTree(b);
                    cout<<"\n--- 所有节点的左右孩子已交换! ---\n";
                    cout<<"交换后的先序遍历: ";
                    PreOrder(b);
                    cout<<endl;
                }
                break;
            }
            
            default: 
                cout<<"\n--- 输入错误! ---\n";
        }
        
        //////////////////////////////////////
        cout<<"\n\n按任意键继续....";
        c=getchar();
    } while(choice);
    
    return 0;
}

////////////////////////////////////////////////////////////////
// 控制面板
void Menu() {
    system("cls");
    cout << "**********二叉链表操作**********\n";
    cout << "--------------------------------\n";
    cout << "        1 建立二叉链表          \n";
    cout << "        2   先序遍历            \n";
    cout << "        3   中序遍历            \n";
    cout << "        4   后序遍历            \n";
    cout << "--------------------------------\n";
    cout << "        5   统计节点            \n";
    cout << "        6   计算高度            \n";
    cout << "        7 交换左右孩子          \n";
    cout << "--------------------------------\n";
    cout << "        0   退出程序            \n";
    cout << "--------------------------------\n";
    cout << "********************************\n";
    cout << "请选择：";
}

////////////////////////////////////////////////////////////////
// 建立二叉链表
void CreateBiTree(BTNode *&b) {
    char ch;
    cin>>ch;
    if(ch=='#') {
        b=NULL;
    } else {
        b=(BTNode *)malloc(sizeof(BTNode));
        b->data=ch;
        CreateBiTree(b->lchild);
        CreateBiTree(b->rchild);
    }
} 

////////////////////////////////////////////////////////////////
// 先序遍历
void PreOrder(BTNode *b) {
    if(b!=NULL) {
        cout<<b->data<<" ";
        PreOrder(b->lchild);
        PreOrder(b->rchild);
    }
}

////////////////////////////////////////////////////////////////
// 中序遍历
void InOrder(BTNode *b) {
    if(b!=NULL) {
        InOrder(b->lchild);
        cout<<b->data<<" ";
        InOrder(b->rchild);
    }
}

////////////////////////////////////////////////////////////////
// 后序遍历
void PostOrder(BTNode *b) {
    if(b!=NULL) {
        PostOrder(b->lchild);
        PostOrder(b->rchild);
        cout<< b->data<<" ";
    }
}

////////////////////////////////////////////////////////////////
// 统计节点
void CountNodes(BTNode *b, int &leaf, int &single, int &doubleNode) {
    if(b!=NULL) {
        // 判断节点类型
        if(b->lchild==NULL && b->rchild==NULL) {
            leaf++; 		// 叶子节点
        } else if((b->lchild==NULL && b->rchild!=NULL) || 
                  (b->lchild!=NULL && b->rchild==NULL)) {
            single++; 		// 单分支节点
        } else {
            doubleNode++; 	// 双分支节点
        }
        
        // 递归统计子树
        CountNodes(b->lchild, leaf, single, doubleNode);
        CountNodes(b->rchild, leaf, single, doubleNode);
    }
}

////////////////////////////////////////////////////////////////
// 计算高度
int Height(BTNode *b) {
    if(b==NULL) {
        return 0;
    } else {
        int leftHeight=Height(b->lchild);
        int rightHeight=Height(b->rchild);
        return (leftHeight> rightHeight? leftHeight: rightHeight)+1;
    }
}

////////////////////////////////////////////////////////////////
// 交换左右孩子
void SwapTree(BTNode *b) {
    if(b!=NULL) {
        // 交换左右子树
        BTNode *temp=b->lchild;
        b->lchild=b->rchild;
        b->rchild=temp;
        
        // 递归交换子树
        SwapTree(b->lchild);
        SwapTree(b->rchild);
    }
}

////////////////////////////////////////////////////////////////
// 销毁二叉链表
void DestroyBiTree(BTNode *&b) {
    if(b!=NULL) {
        DestroyBiTree(b->lchild);
        DestroyBiTree(b->rchild);
        free(b);
        b=NULL;
    }
}

////////////////////////////////////////////////////////////////
// sys选择验证
int input(char c) {
    if('0'<=c && '9'>=c)
        return c-'0';
    else
        return -1;
}

////////////////////////////////////////////////////////////////
// 整型输入验证
bool Input(const char *s, int *n) {
    if(s) printf("%s", s);
    if(scanf("%d", n)!=1) {
        printf("\n输入字符非法!");
        clearInputBuffer();
        return 0;
    }
    clearInputBuffer();
    return 1;
}

////////////////////////////////////////////////////////////////
// 清除缓冲区
void clearInputBuffer() {
    while(getchar()!='\n');
}
