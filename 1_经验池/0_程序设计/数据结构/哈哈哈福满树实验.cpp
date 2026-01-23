#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <iostream>

using namespace std;

#define MAX_LEAF 256
#define MAX_NODE (2*MAX_LEAF-1)

typedef struct HTNode
{
    char data;        // 字符
    int weight;       // 权重
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode; // 存储哈夫曼编码

void InitHuffmanTree(HuffmanTree *HT, int n);                         // 初始化哈夫曼树
void DestroyHuffmanTree(HuffmanTree *HT);                             // 销毁哈夫曼树
void Select(HuffmanTree HT, int n, int *s1, int *s2);                 // 选择两个最小权重的结点
void CreateHuffmanTree(HuffmanTree *HT, char *chars, int *w, int n);  // 构建哈夫曼树
void InitHuffmanCode(HuffmanCode *HC, int n);                         // 初始化哈夫曼编码表
void DestroyHuffmanCode(HuffmanCode *HC, int n);                      // 销毁哈夫曼编码表
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n);       // 生成哈夫曼编码
void DisplayHuffmanCode(HuffmanTree HT, HuffmanCode HC, int n);       // 显示哈夫曼编码
void FreeHuffmanTree(HuffmanTree *HT, HuffmanCode *HC, int n);        // 释放所有内存

void CreateCustomData(char **custom_chars, int **custom_weights, int n); // 创建自定义数据
void DestroyCustomData(char **custom_chars, int **custom_weights);       // 销毁自定义数据

int input(char c);													  // sys选择
bool Input(const char *s, int *n);                                    // 整型输入验证
bool InputFloat(const char *s, float *f);                             // 浮点数输入验证
void clearInputBuffer();                                              // 清除缓冲区
void Menu();                                                          // 控制面板


int main()
{
    HuffmanTree HT=NULL;
    HuffmanCode HC=NULL;
    int n=8; // 默认字符数量
    char c='N';
    int choice=0;
    
    // 默认字符集和权重
    char chars[]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int weights[]={5, 29, 7, 8, 14, 23, 3, 11};
    
    // 用于自定义输入的变量
    char *custom_chars=NULL;
    int *custom_weights=NULL;
    
    do
    {
        choice=0;
        c='N';
        Menu();
        cin>>c;
        choice=input(c);
        clearInputBuffer();
        
        switch(choice)
        {
            case 0: // *** 退出指令 ***
            {
                if (HT!=NULL)
                    FreeHuffmanTree(&HT, &HC, n);
                
                // 释放自定义输入分配的内存
                DestroyCustomData(&custom_chars, &custom_weights);
                
                cout<<"\n系统已退出。\n";
                break;
            }
            
            case 1: // *** 创建哈夫曼树 (默认数据) ***
            {
                if(HT!=NULL)
                    FreeHuffmanTree(&HT, &HC, n);
                
                n=8;
                CreateHuffmanTree(&HT, chars, weights, n);
                cout<<"\n--- 哈夫曼树创建完成! ---\n";
                break;
            }
            
            case 2: // *** 生成并显示哈夫曼编码 ***
            {
                if(HT==NULL)
                {
                    cout<<"\n--- 请先创建哈夫曼树! ---\n";
                    break;
                }
                
                if(HC==NULL)
                    CreateHuffmanCode(HT, &HC, n);
                
                DisplayHuffmanCode(HT, HC, n);
                break;
            }
            
            case 3: // *** 自定义输入 ***
            {
                // 释放之前的哈夫曼树
                if (HT!=NULL)
                    FreeHuffmanTree(&HT, &HC, n);
                
                // 释放之前的自定义数据
                DestroyCustomData(&custom_chars, &custom_weights);
                
                cout<<"\n********** 自定义输入哈夫曼编码 **********\n";
                cout<<"----------------------------------------\n";
                
                cout<<"请输入字符数量 (1-"<<MAX_LEAF<<"): ";
                if(!Input("", &n))
                {
                    cout<<"\n--- 输入无效! ---\n";
                    break;
                }
                
                if(n<1 || n>MAX_LEAF)
                {
                    cout<<"\n--- 字符数量必须在1-"<<MAX_LEAF<<"之间! ---\n";
                    break;
                }
                
                // 分配内存
                CreateCustomData(&custom_chars, &custom_weights, n);
                
                cout<<"\n请输入每个字符及其权重 (频率):\n";
                cout<<"注意: 权重可以输入整数或小数 (如: 0.05)\n";
                cout<<"----------------------------------------\n";
                
                float total_weight=0.0;
                for(int i=0; i<n; i++)
                {
                    cout<<"\n第 "<<i+1<<" 个字符:\n";
                    
                    char ch;
                    cout<<"  字符 (单字符，如: a, b, 1, #): ";
                    cin>>ch;
                    clearInputBuffer();
                    custom_chars[i] = ch;
                    
                    float weight_float;
                    cout<<"  权重 (频率，如: 0.05 或 5): ";
                    if(!InputFloat("", &weight_float))
                    {
                        cout<<"\n--- 权重输入无效! ---\n";
                        DestroyCustomData(&custom_chars, &custom_weights);
                        break;
                    }
                    
                    if (weight_float <= 0)
                    {
                        cout<<"\n--- 权重必须大于0! ---\n";
                        DestroyCustomData(&custom_chars, &custom_weights);
                        break;
                    }
                    
                    // 将权重转换为整数
                    custom_weights[i]=(int)(weight_float*100+0.5);
                    total_weight+=weight_float;
                    
                    cout<<"  已记录: 字符 '"<<ch<<"', 权重 "<<weight_float 
                        <<" (转换为整数: "<<custom_weights[i]<<")\n";
                }
                
                // 检查所有权重和是否为1
                if (total_weight<0.99 || total_weight>1.01)	// 近似 
                {
                    cout<<"\n----------------------------------------\n";
                    cout<<"警告: 所有权重之和为 "<<total_weight 
                        <<"，建议总和为1.0 (当前偏差: "<<(total_weight-1.0)<<")\n";
                    cout<<"是否继续? (Y/N): ";
                    
                    char confirm;
                    cin>>confirm;
                    clearInputBuffer();
                    
                    if (confirm!='Y' && confirm!='y')
                    {
                        cout<<"\n--- 已取消操作! ---\n";
                        DestroyCustomData(&custom_chars, &custom_weights);
                        break;
                    }
                }
                
                cout<<"\n----------------------------------------\n";
                cout<<"输入数据汇总:\n";
                cout<<"字符数量: "<<n<<"\n";
                cout<<"字符和权重:\n";
                for (int i=0; i<n; i++)
                    printf("  %c: %.2f (整数权重: %d)\n", 
                           custom_chars[i], 
                           custom_weights[i] / 100.0, 
                           custom_weights[i]);
                printf("  权重总和: %.4f\n", total_weight);
                cout<<"----------------------------------------\n";
                
                cout<<"\n正在创建哈夫曼树...\n";
                CreateHuffmanTree(&HT, custom_chars, custom_weights, n);
                cout<<"--- 哈夫曼树创建完成! ---\n";
                
                CreateHuffmanCode(HT, &HC, n);
                DisplayHuffmanCode(HT, HC, n);
                
                break;
            }
            
            default:
                cout<<"\n--- 输入错误! ---\n";
        }
        
        if(choice!=0)
        {
            cout<<"\n\n按任意键继续...";
            c=getchar();
        }
        
    } while(choice!=0);
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Menu()
{
    system("cls");
    cout<< "********** 哈夫曼编码系统 **********\n";
    cout<<"-------------------------------------\n";
    cout<<"      1 创建哈夫曼树 (使用默认数据)  \n";
    cout<<"      2      显示哈夫曼编码          \n";
    cout<<"      3        自定义输入            \n";
    cout<<"-------------------------------------\n";
    cout<<"      0         退出程序             \n";
    cout<<"-------------------------------------\n";
    cout<<"*************************************\n";
    cout<<"请选择: ";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 初始化哈夫曼树 ***
void InitHuffmanTree(HuffmanTree *HT, int n)
{
    if(*HT!=NULL)
        DestroyHuffmanTree(HT);
    
    int m=2*n-1;
    *HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
    
    if(*HT==NULL) {
        printf("内存分配失败!\n");
        exit(1);
    }
    
    for(int i=1; i<=m; i++)
    {
        (*HT)[i].data='\0';
        (*HT)[i].weight=0;
        (*HT)[i].parent=(*HT)[i].lchild=(*HT)[i].rchild=0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 销毁哈夫曼树 ***
void DestroyHuffmanTree(HuffmanTree *HT)
{
    if(*HT!=NULL)
    {
        free(*HT);
        *HT=NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 初始化哈夫曼编码表 ***
void InitHuffmanCode(HuffmanCode *HC, int n)
{
    if(*HC!=NULL) {
        DestroyHuffmanCode(HC, n);
    }
    
    *HC=(HuffmanCode)malloc((n+1)*sizeof(char*)); // 分配编码表数组
    if(*HC==NULL) {
        printf("内存分配失败!\n");
        exit(1);
    }
    
    for(int i=1; i<=n; i++)
    {
        (*HC)[i]=NULL; // 初始化为空
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 销毁哈夫曼编码表 ***
void DestroyHuffmanCode(HuffmanCode *HC, int n)
{
    if(*HC!=NULL)
    {
        for(int i=1; i<=n; i++)
        {
            if((*HC)[i]!=NULL) {
                free((*HC)[i]);
                (*HC)[i]=NULL;
            }
        }
        free(*HC);
        *HC=NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 创建自定义数据数组 ***
void CreateCustomData(char **custom_chars, int **custom_weights, int n)
{
    if(*custom_chars!=NULL) {
        free(*custom_chars);
    }
    if(*custom_weights!=NULL) {
        free(*custom_weights);
    }
    
    *custom_chars=(char*)malloc(n*sizeof(char));
    *custom_weights=(int*)malloc(n*sizeof(int));
    
    if(*custom_chars==NULL || *custom_weights==NULL) {
        printf("内存分配失败!\n");
        exit(1);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 销毁自定义数据数组 ***
void DestroyCustomData(char **custom_chars, int **custom_weights)
{
    if(*custom_chars!=NULL)
    {
        free(*custom_chars);
        *custom_chars=NULL;
    }
    
    if(*custom_weights!=NULL)
    {
        free(*custom_weights);
        *custom_weights=NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 选择两个最小权重的结点 ***
void Select(HuffmanTree HT, int n, int *s1, int *s2)
{
    int min1=INT_MAX, min2=INT_MAX;
    *s1=*s2=0;
    
    for(int i=1; i<=n; i++)
        if (HT[i].parent==0)
            if(HT[i].weight<min1)
            {
                min2=min1;
                *s2=*s1;
                min1=HT[i].weight;
                *s1=i;
            }
            else if(HT[i].weight<min2)
            {
                min2=HT[i].weight;
                *s2=i;
            }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 构建哈夫曼树 ***
void CreateHuffmanTree(HuffmanTree *HT, char *chars, int *w, int n)
{
    if(n<=1) return;
    
    int m=2*n-1;
    InitHuffmanTree(HT, n);
    
    // 初始化前n个结点为叶子结点
    for (int i=1; i<=n; i++)
    {
        (*HT)[i].data=chars[i-1]; // 使用传入的字符数组
        (*HT)[i].weight=w[i-1];
    }
    
    // 构建哈夫曼树
    for (int i=n+1; i<=m; i++)
    {
        int s1, s2;
        Select(*HT, i-1, &s1, &s2);
        
        (*HT)[s1].parent=(*HT)[s2].parent = i;
        (*HT)[i].lchild =s1;
        (*HT)[i].rchild =s2;
        (*HT)[i].weight =(*HT)[s1].weight+(*HT)[s2].weight;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 生成哈夫曼编码 ***
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n)
{
    // 先初始化编码表
    InitHuffmanCode(HC, n);
    
    // 临时编码缓冲区
    char *cd=(char*)malloc(n*sizeof(char));
    if(cd==NULL) {
        printf("内存分配失败!\n");
        exit(1);
    }
    cd[n-1]='\0';
    
    for(int i=1; i<=n; i++)
    {
        int start=n-1;
        int c=i, f=HT[i].parent;
        
        while (f!=0)
        {
            if(HT[f].lchild==c)
                cd[--start]='0';
            else
                cd[--start]='1';
                
            c=f;
            f=HT[c].parent;
        }
        
        // 分配编码字符串空间
        int code_len=n-start;
        (*HC)[i]=(char*)malloc((code_len+1)*sizeof(char));
        if((*HC)[i]==NULL) {
            printf("内存分配失败!\n");
            exit(1);
        }
        
        // 复制编码
        strcpy((*HC)[i], &cd[start]);
    }
    
    // 释放临时缓冲区
    free(cd);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 显示哈夫曼编码 ***
void DisplayHuffmanCode(HuffmanTree HT, HuffmanCode HC, int n)
{
    cout<<"\n------------------------------------\n";
    cout<<"字符   权重     哈夫曼编码\n";
    cout<<"------------------------------------\n";
    
    for (int i=1; i<=n; i++)
        printf("%c      %2d       %s\n", HT[i].data, HT[i].weight, HC[i]);
    
    cout << "------------------------------------\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 释放所有内存 ***
void FreeHuffmanTree(HuffmanTree *HT, HuffmanCode *HC, int n)
{
    DestroyHuffmanCode(HC, n);
    DestroyHuffmanTree(HT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** sys选择验证 ***
int input(char c)
{
	if('0'<=c && '3'>=c) 
		return c-'0';
	else 
		return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 整型输入验证 ***
bool Input(const char *s, int *n)
{
    if (s) printf("%s", s);
    
    if(scanf("%d", n)!=1)
    {
        printf("\n输入字符非法!");
        clearInputBuffer();
        return 0;
    }
    
    clearInputBuffer();
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 浮点数输入验证 ***
bool InputFloat(const char *s, float *f)
{
    if(s) printf("%s", s);
    
    if(scanf("%f", f)!=1)
    {
        printf("\n输入字符非法!");
        clearInputBuffer();
        return 0;
    }
    
    clearInputBuffer();
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** 清除缓冲区 ***
void clearInputBuffer()
{
    while (getchar() != '\n');
}
