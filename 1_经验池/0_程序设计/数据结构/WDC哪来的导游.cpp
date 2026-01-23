#include<iostream>
#include<cstring>
#include<fstream>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;

// 符常量的定义
#define INF 32767             // 定义无穷大 
#define MAX 10                // 最大顶点个数

// 以下定义图的邻接矩阵类型
typedef struct {
    char SpotId[2];                 // 景点编号
    char Name[20];                  // 景点名称
    char Introduction[256];         // 景点简介 
} VertexType;                       // 景点类型

typedef struct {
    int u;                          // 边的起始顶点 
    int v;                          // 边的终止顶点 
    int Weight;                     // 边的权重 
} EdgeType;                         // 边的类型

typedef struct {
    int VexNum, EdgeNum;            // 顶点数，边数
    VertexType Vexs[MAX];           // 存放顶点信息
    int Edges[MAX][MAX]; 	        // 邻接矩阵数组    
} MatrixGraph;                      // 完整的图邻接矩阵类型

// 以下定义邻接表类型
typedef struct ANode {
    int adjvex;                     // 该边的邻接点编号
    struct ANode *nextarc;          // 指向下一条边的指针
    int weight;                     // 该边的相关信息，如权值
} ArcNode;                          // 边节点类型

typedef struct Vnode {
    VertexType VexData;             // 顶点数据 
    int count;                      // 存放顶点入度(用于拓扑排序)
    ArcNode *firstarc;              // 指向第一条边
} VertexNode;                       // 邻接表头节点类型

typedef struct {
    VertexNode adjlist[MAX];  	    // 邻接表头节点数组
    int n, e;                       // 图中顶点数n和边数e
} AdjGraph;                         // 完整的图邻接表类型

// 函数声明
void Menu();
int LocateSpotPos(MatrixGraph g, char SpotName[]);
void ShowOne(MatrixGraph g, int i);

// 景点地图整体管理相关函数
void ManaMapData(MatrixGraph &g);
void InitSpotsData(MatrixGraph &g);
void SaveToMapFile(MatrixGraph g);
void LoadFromMapFile(MatrixGraph &g);

// 校园景点数据管理相关函数
void ManaVertexData(MatrixGraph &g);
void InMultSpotsData(MatrixGraph &g, int n);
void InOneSpotsData(MatrixGraph &g, int i);
void InDeleteSpotsData(MatrixGraph &g);
void InModifySpotsData(MatrixGraph &g);
void ShowAll(MatrixGraph g);

// 景点交通数据管理相关函数
void ManaRoadData(MatrixGraph &g);
void AddEdge(MatrixGraph &g);
void DeleteEdge(MatrixGraph &g);
void ModifyEdge(MatrixGraph &g);
void DispAllEdge(MatrixGraph g);

// 校园景点信息查询
void SearchSpotInfor(MatrixGraph g);

// 游览线路查询规划
void VisitPathPlan(MatrixGraph &g);
bool MatrixToAdjList(MatrixGraph g, AdjGraph *&G);
void DFS(AdjGraph *G, int v);
void BFS(AdjGraph *G, int v);
void DispAdj(AdjGraph *G);
void DestroyAdj(AdjGraph *&G);

// 景点最短路径查询
void ShortestPathQuery(MatrixGraph g);
void Dijkstra(MatrixGraph g, int v);
void Floyd(MatrixGraph g);
void Disppath(MatrixGraph g, int dist[], int path[], int S[], int v);
void Dispath(MatrixGraph g, int A[][MAX], int path[][MAX]);

// 管道系统最优布设
void PipelineSystemOptimal(MatrixGraph g);
void Prim(MatrixGraph g, int v);
void Kruskal(MatrixGraph g);
void BubbleSort(EdgeType R[], int n);

int input(char c);
void clearInputBuffer();

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    MatrixGraph g;
    g.VexNum=0;
    g.EdgeNum=0;
    int choice=0;
	char c='N';
    
    // 初始化邻接矩阵
    for(int i=0; i<MAX; i++)
        for(int j=0; j<MAX; j++)
            if(i==j)
                g.Edges[i][j]=0;
            else
                g.Edges[i][j]=INF;
    
    do {
    	choice=0; c='N';
        Menu();
        cin>>(c);
        choice=input(c);
        clearInputBuffer();
        
        switch(choice) {
        	case 0:
                cout<<"感谢使用武汉东湖学院校园导游系统！"<<endl;
                break;
            case 1:  // 景点地图整体管理
                ManaMapData(g);
                break;
            case 2:  // 校园景点数据管理
                ManaVertexData(g);
                break;
            case 3:  // 景点交通数据管理
                ManaRoadData(g);
                break;
            case 4:  // 校园景点信息查询
                SearchSpotInfor(g);
                break;
            case 5:  // 游览线路查询规划
                VisitPathPlan(g);
                break;
            case 6:  // 景点最短路径查询
                ShortestPathQuery(g);
                break;
            case 7:  // 管道系统最优布设
                PipelineSystemOptimal(g);
                break;
            default:
                cout<<"\n输入错误，请重新输入"<<endl;
        }
    //////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
    } while(choice!=0);
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Menu() {
    system("cls");
    cout<<"***********************************************"<<endl;
    cout<<"       武汉东湖学院校园导游信息系统主菜单      "<<endl;
    cout<<"***********************************************"<<endl;
    cout<<"             1  景点地图整体管理               "<<endl; 
    cout<<"             2  校园景点数据管理               "<<endl; 
    cout<<"             3  景点交通数据管理               "<<endl; 
    cout<<"             4  校园景点信息查询               "<<endl; 
    cout<<"             5  游览线路查询规划               "<<endl; 
    cout<<"             6  景点最短路径查询               "<<endl; 
    cout<<"             7  管道系统最优布设               "<<endl; 
    cout<<"             0  退出校园导游系统               "<<endl; 
    cout<<"***********************************************"<<endl;
    cout<<"\n请选择(0~7): ";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LocateSpotPos(MatrixGraph g, char SpotName[]) {
    for(int i=0; i<g.VexNum; i++)
        if(strcmp(g.Vexs[i].Name, SpotName)==0)
            return i;
    return -1;
}

void ShowOne(MatrixGraph g, int i) {
    if(i<0 || i>=g.VexNum) {
        cout<<"景点索引错误！"<<endl;
        return;
    }
    cout<<"============================================"<<endl;
    cout<<"景点编号: "<<g.Vexs[i].SpotId<<endl;
    cout<<"景点名称: "<<g.Vexs[i].Name<<endl;
    cout<<"景点简介: "<<g.Vexs[i].Introduction<<endl;
    cout<<"============================================"<<endl;
}

void clearInputBuffer() {
    while(getchar()!='\n');
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int input(char c)
{	// sys选择验证
	if('0'<=c && '9'>=c) 
		return c-'0';
	else 
		return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManaMapData(MatrixGraph &g) {	// 景点地图整体管理
    int choice=0;
	char c='N';
    do {
    	choice=999; c='N';
        system("cls");
        cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
        cout<<"     校园景点地图整体数据管理     "<<endl;
        cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
        cout<<"      1 初始化景点地图数据        "<<endl;
        cout<<"      2  保存景点地图数据         "<<endl;
        cout<<"      3  读取景点地图数据         "<<endl;
        cout<<"      0     返回主菜单            "<<endl;
        cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
        cout<<"\n请选择(0~3): ";
        cin>>(c);
        choice=input(c);
        clearInputBuffer();
        
        switch(choice) {
        	case 0:
                return;
            case 1:
                InitSpotsData(g);
                break;
            case 2:
                SaveToMapFile(g);
                break;
            case 3:
                LoadFromMapFile(g);
                break;
            default:
                cout<<"输入错误，请重新输入！"<<endl;
        }
    //////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
    } while(choice!=0);
}

void InitSpotsData(MatrixGraph &g) {
    g.VexNum=8;
    g.EdgeNum=10;
    
    // 初始化8个景点
    strcpy(g.Vexs[0].SpotId, "01");
    strcpy(g.Vexs[0].Name, "图书馆");
    strcpy(g.Vexs[0].Introduction, "武汉东湖学院图书馆，藏书丰富，学习氛围浓厚。");
    
    strcpy(g.Vexs[1].SpotId, "02");
    strcpy(g.Vexs[1].Name, "教学楼");
    strcpy(g.Vexs[1].Introduction, "主要教学区域，包含多个教室和实验室。");
    
    strcpy(g.Vexs[2].SpotId, "03");
    strcpy(g.Vexs[2].Name, "食堂");
    strcpy(g.Vexs[2].Introduction, "学生食堂，提供各种美食。");
    
    strcpy(g.Vexs[3].SpotId, "04");
    strcpy(g.Vexs[3].Name, "体育馆");
    strcpy(g.Vexs[3].Introduction, "体育教学和比赛场所。");
    
    strcpy(g.Vexs[4].SpotId, "05");
    strcpy(g.Vexs[4].Name, "宿舍");
    strcpy(g.Vexs[4].Introduction, "学生宿舍区，生活设施齐全。");
    
    strcpy(g.Vexs[5].SpotId, "06");
    strcpy(g.Vexs[5].Name, "操场");
    strcpy(g.Vexs[5].Introduction, "标准运动场，适合跑步和锻炼。");
    
    strcpy(g.Vexs[6].SpotId, "07");
    strcpy(g.Vexs[6].Name, "校门");
    strcpy(g.Vexs[6].Introduction, "学校主入口，标志性建筑。");
    
    strcpy(g.Vexs[7].SpotId, "08");
    strcpy(g.Vexs[7].Name, "实验室");
    strcpy(g.Vexs[7].Introduction, "计算机和科学实验室。");
    
    // 初始化邻接矩阵
    for(int i=0; i<MAX; i++)
        for(int j=0; j<MAX; j++)
            if(i==j)
                g.Edges[i][j]=0;
            else
                g.Edges[i][j]=INF;
    
    // 设置10条边的权重
    g.Edges[0][1] = g.Edges[1][0] = 200;  // 图书馆-教学楼
    g.Edges[0][2] = g.Edges[2][0] = 150;  // 图书馆-食堂
    g.Edges[1][3] = g.Edges[3][1] = 300;  // 教学楼-体育馆
    g.Edges[1][5] = g.Edges[5][1] = 250;  // 教学楼-操场
    g.Edges[2][4] = g.Edges[4][2] = 100;  // 食堂-宿舍
    g.Edges[3][5] = g.Edges[5][3] = 150;  // 体育馆-操场
    g.Edges[4][6] = g.Edges[6][4] = 200;  // 宿舍-校门
    g.Edges[5][6] = g.Edges[6][5] = 180;  // 操场-校门
    g.Edges[6][7] = g.Edges[7][6] = 120;  // 校门-实验室
    g.Edges[7][0] = g.Edges[0][7] = 220;  // 实验室-图书馆
    
    cout<<"景点地图数据初始化完成！"<<endl;
    cout<<"顶点数: "<<g.VexNum<<"，边数: "<<g.EdgeNum<<endl;
}

void SaveToMapFile(MatrixGraph g) {
    ofstream outFile("CampusSpotsData.dat", ios::binary);
    if (!outFile) {
        cout<<"无法打开文件进行保存！"<<endl;
        return;
    }
    
    outFile.write((char*)&g, sizeof(g));
    outFile.close();
    cout<<"景点地图数据已保存到 CampusSpotsData.dat"<<endl;
}

void LoadFromMapFile(MatrixGraph &g) {
    ifstream inFile("CampusSpotsData.dat", ios::binary);
    if (!inFile) {
        cout<<"无法打开文件或文件不存在！"<<endl;
        return;
    }
    
    inFile.read((char*)&g, sizeof(g));
    inFile.close();
    cout<<"景点地图数据已从 CampusSpotsData.dat 读取"<<endl;
    cout<<"顶点数: "<<g.VexNum<<"，边数: "<<g.EdgeNum<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManaVertexData(MatrixGraph &g) {	// 校园景点数据管理
	int choice=0;
	char c='N';
    do {
    	choice=999; c='N';
        system("cls");
        cout<<"============================================"<<endl;
        cout<<"              校园景点数据管理              "<<endl;
        cout<<"============================================"<<endl;
        cout<<"              1  增加景点数据               "<<endl;
        cout<<"              2  删除景点数据               "<<endl;
        cout<<"              3  修改景点数据               "<<endl;
        cout<<"              4  显示景点数据               "<<endl;
        cout<<"              0   返回主菜单                "<<endl;
        cout<<"============================================"<<endl;
		cout<<"\n请选择(0~4): ";
		cin>>(c);
        choice=input(c);
        clearInputBuffer();
        
        switch(choice) {
        	case 0:
                return;
            case 1:
                InMultSpotsData(g, 1);
                break;
            case 2:
                InDeleteSpotsData(g);
                break;
            case 3:
                InModifySpotsData(g);
                break;
            case 4:
                ShowAll(g);
                break;
            default:
                cout<<"输入错误，请重新输入！"<<endl;
        }
    //////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
    } while(choice!=0);
}

void InMultSpotsData(MatrixGraph &g, int n) {
    if (g.VexNum+n>MAX) {
        cout<<"景点数量超过最大限制！"<<endl;
        return;
    }
    
    for (int i=0; i<n; i++) {
        cout<<"请输入第 "<<g.VexNum+1<<" 个景点信息："<<endl;
        InOneSpotsData(g, g.VexNum);
        g.VexNum++;
    }
    cout<<"景点添加完成！"<<endl;
}

void InOneSpotsData(MatrixGraph &g, int i) {
    cout<<"景点编号: ";
    cin.getline(g.Vexs[i].SpotId, 3);
    cout<<"景点名称: ";
    cin.getline(g.Vexs[i].Name, 20);
    cout<<"景点简介: ";
    cin.getline(g.Vexs[i].Introduction, 256);
}

void InDeleteSpotsData(MatrixGraph &g) {
    char name[20];
    cout<<"请输入要删除的景点名称: ";
    cin.getline(name, 20);
    
    int pos=LocateSpotPos(g, name);
    if(pos==-1) {
        cout<<"未找到该景点！"<<endl;
        return;
    }
    
    // 删除景点及相关边
    for (int i=pos; i<g.VexNum-1; i++) {
        g.Vexs[i]=g.Vexs[i+1];
        for (int j=0; j<g.VexNum; j++) {
            g.Edges[i][j]=g.Edges[i+1][j];
            g.Edges[j][i]=g.Edges[j][i+1];
        }
    }
    
    g.VexNum--;
    cout<<"景点删除成功！"<<endl;
}

void InModifySpotsData(MatrixGraph &g) {
    char name[20];
    cout<<"请输入要修改的景点名称: ";
    cin.getline(name, 20);
    
    int pos=LocateSpotPos(g, name);
    if(pos==-1) {
        cout<<"未找到该景点！"<<endl;
        return;
    }
    
    cout<<"请输入新的景点信息："<<endl;
    InOneSpotsData(g, pos);
    cout<<"景点修改成功！"<<endl;
}

void ShowAll(MatrixGraph g) {
    cout<<"============================================"<<endl;
    cout<<"            所有景点信息列表                "<<endl;
    cout<<"============================================"<<endl;
    for (int i=0; i< g.VexNum; i++) {
        cout<<i+1<<". "<<g.Vexs[i].Name<<" ("<<g.Vexs[i].SpotId<<")"<<endl;
        cout<<"   简介: "<<g.Vexs[i].Introduction<<endl;
        cout<<"--------------------------------------------"<<endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ManaRoadData(MatrixGraph &g) {	// 景点交通数据管理
    int choice=0;
	char c='N';
    do {
    	choice=999; c='N';
        system("cls");
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"            校园景点交通数据管理            "<<endl;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"             1 增加景点交通数据             "<<endl;
        cout<<"             2 删除景点交通数据             "<<endl;
        cout<<"             3 修改景点交通数据             "<<endl;
        cout<<"             4 显示景点交通数据             "<<endl;
        cout<<"             0    返回主菜单                "<<endl;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"\n请选择(0~4): ";
		cin>>(c);
        choice=input(c);
        clearInputBuffer();
        
        switch(choice) {
        	case 0:
                return;
            case 1:
                AddEdge(g);
                break;
            case 2:
                DeleteEdge(g);
                break;
            case 3:
                ModifyEdge(g);
                break;
            case 4:
                DispAllEdge(g);
                break;
            default:
                cout<<"输入错误，请重新输入！"<<endl;
        }
    //////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
    } while(choice != 0);
}

void AddEdge(MatrixGraph &g) {
    char name1[20], name2[20];
    int weight;
    
    cout<<"请输入第一个景点名称: ";
    cin.getline(name1, 20);
    int v1=LocateSpotPos(g, name1);
    
    cout<<"请输入第二个景点名称: ";
    cin.getline(name2, 20);
    int v2=LocateSpotPos(g, name2);
    
    if (v1==-1 || v2==-1) {
        cout<<"景点不存在！"<<endl;
        return;
    }
    
    cout<<"请输入路径长度: ";
    cin>>weight;
    clearInputBuffer();
    
    g.Edges[v1][v2]=g.Edges[v2][v1]=weight;
    g.EdgeNum++;
    cout<<"交通数据添加成功！"<<endl;
}

void DeleteEdge(MatrixGraph &g) {
    char name1[20], name2[20];
    
    cout<<"请输入第一个景点名称: ";
    cin.getline(name1, 20);
    int v1 = LocateSpotPos(g, name1);
    
    cout<<"请输入第二个景点名称: ";
    cin.getline(name2, 20);
    int v2=LocateSpotPos(g, name2);
    
    if(v1==-1 || v2==-1) {
        cout<<"景点不存在！"<<endl;
        return;
    }
    
    if (g.Edges[v1][v2]==INF) {
        cout<<"该路径不存在！"<<endl;
        return;
    }
    
    g.Edges[v1][v2]=g.Edges[v2][v1]=INF;
    g.EdgeNum--;
    cout<<"交通数据删除成功！"<<endl;
}

void ModifyEdge(MatrixGraph &g) {
    char name1[20], name2[20];
    int weight;
    
    cout<<"请输入第一个景点名称: ";
    cin.getline(name1, 20);
    int v1=LocateSpotPos(g, name1);
    
    cout<<"请输入第二个景点名称: ";
    cin.getline(name2, 20);
    int v2=LocateSpotPos(g, name2);
    
    if (v1==-1 || v2==-1) {
        cout<<"景点不存在！"<<endl;
        return;
    }
    
    if (g.Edges[v1][v2]==INF) {
        cout<<"该路径不存在！"<<endl;
        return;
    }
    
    cout<<"当前路径长度: "<<g.Edges[v1][v2]<<endl;
    cout<<"请输入新的路径长度: ";
    cin>>weight;
    clearInputBuffer();
    
    g.Edges[v1][v2]=g.Edges[v2][v1]=weight;
    cout<<"交通数据修改成功！"<<endl;
}

void DispAllEdge(MatrixGraph g) {
    cout<<"============================================"<<endl;
    cout<<"            所有交通路径信息                "<<endl;
    cout<<"============================================"<<endl;
    
    for(int i=0; i<g.VexNum; i++)
        for(int j=i+1; j<g.VexNum; j++)
            if(g.Edges[i][j]!=INF && g.Edges[i][j]!=0) {
                cout<<g.Vexs[i].Name<<" <---> "<<g.Vexs[j].Name;
                cout<<"  距离: "<<g.Edges[i][j]<<"米"<<endl;
            }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SearchSpotInfor(MatrixGraph g) {	// 校园景点信息查询
    char name[20];
    cout<<"请输入要查询的景点名称: ";
    cin.getline(name, 20);
    
    int pos=LocateSpotPos(g, name);
    if(pos==-1) {
        cout<<"未找到该景点！"<<endl;
    } else {
        ShowOne(g, pos);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VisitPathPlan(MatrixGraph &g) {	// 游览线路查询规划
    int choice=0;
	char c='N';
	// 创建邻接表
    AdjGraph *G;
    if (!MatrixToAdjList(g, G)) {
        cout<<"邻接表创建失败！"<<endl;
        return;
    }
    
    char name[20];
    cout<<"请输入游览线路起点景点名称: ";
    cin.getline(name, 20);
    int v=LocateSpotPos(g, name);
    
    if(v==-1) {
        cout<<"\n未找到该景点！"<<endl;
        DestroyAdj(G);
        return;
    }
    
    do {
    	choice=999; c='N';
        system("cls");
        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<"      校园景点游览线路查询规划      "<<endl;
        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<"     1 深度优先游览线路查询规划     "<<endl;
        cout<<"     2 广度优先游览线路查询规划     "<<endl;
        cout<<"     0        返回主菜单            "<<endl;
        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<"\n请选择(0~2): ";
		cin>>(c);
        choice=input(c);
        clearInputBuffer();
        
        switch(choice) {
        	case 0:
                return;
            case 1:
                cout<<"\n深度优先遍历路径: ";
                DFS(G, v);
                cout<<endl;
                break;
            case 2:
                cout<<"\n广度优先遍历路径: ";
                BFS(G, v);
                cout<<endl;
                break;
            default:
                cout<<"输入错误，请重新输入！"<<endl;
        }
    //////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
    } while(choice!=0);
    
    DestroyAdj(G);
}

bool MatrixToAdjList(MatrixGraph g, AdjGraph *&G) {
    G=new AdjGraph;
    G->n=g.VexNum;
    G->e=g.EdgeNum;
    
    for(int i=0; i<g.VexNum; i++) {
        G->adjlist[i].VexData=g.Vexs[i];
        G->adjlist[i].count=0;
        G->adjlist[i].firstarc=NULL;
        
        for (int j=g.VexNum-1; j>=0; j--)
            if (g.Edges[i][j]!=0 && g.Edges[i][j]!=INF) {
                ArcNode *p=new ArcNode;
                p->adjvex=j;
                p->weight=g.Edges[i][j];
                p->nextarc=G->adjlist[i].firstarc;
                G->adjlist[i].firstarc=p;
            }
    }
    return true;
}

void DFS(AdjGraph *G, int v) {
    // 静态变量保存状态
    static bool visited[MAX];
    static stack<int> s;	// C++标准栈 
    static bool firstCall=true;
    static bool disp=false;
    
    if(firstCall) {	// 第一次调用，初始化
        for(int i=0; i<MAX; i++)
			visited[i]=false;
        while(!s.empty())
			s.pop();
        firstCall=false;
        disp=false;
        
        s.push(v);
        
        while(!s.empty()) {
            int current=s.top();
            s.pop();
            
            if(!visited[current]) {
                visited[current]=true;
                
                if(disp)
                    cout<<" -> ";
                disp=true;
                
                cout<<G->adjlist[current].VexData.Name;
                
                ArcNode *p=G->adjlist[current].firstarc;
                vector<int> neighbors;
                while(p!=NULL) {
                    if(!visited[p->adjvex])
                        neighbors.push_back(p->adjvex);
                    p=p->nextarc;
                }
                
                for(int i=neighbors.size()-1; i>= 0; i--)
                    s.push(neighbors[i]);
            }
        }
        
        firstCall=true;
    }
}

void BFS(AdjGraph *G, int v) {
    // 静态变量保存状态
    static bool visited[MAX];
    static queue<int> q;	// C++标准队列 
    static bool firstCall=true;
    static bool disp=false;
    
    if (firstCall) {
        for(int i=0; i<MAX; i++)
			visited[i]=false;
        while(!q.empty())
			q.pop();
        firstCall=false;
        disp=false;
        
        q.push(v);
        visited[v]=true;
        
        while(!q.empty()) {
            int current=q.front();
            q.pop();
            
            if(disp)
                cout<<" -> ";
            disp=true;
            
            cout<<G->adjlist[current].VexData.Name;
            
            ArcNode *p=G->adjlist[current].firstarc;
            while (p!=NULL) {
                if(!visited[p->adjvex]) {
                    visited[p->adjvex]=true;
                    q.push(p->adjvex);
                }
                p=p->nextarc;
            }
        }
        firstCall = true;
    }
}

void DispAdj(AdjGraph *G) {
    cout<<"邻接表信息:"<<endl;
    for (int i=0; i<G->n; i++) {
        cout<<i<<"("<<G->adjlist[i].VexData.Name<<"): ";
        ArcNode *p=G->adjlist[i].firstarc;
        while(p!=NULL) {
            cout<<p->adjvex<<"("<<G->adjlist[p->adjvex].VexData.Name<<")"<<"["<<p->weight<<"] ";
            p=p->nextarc;
        }
        cout<<endl;
    }
}

void DestroyAdj(AdjGraph *&G) {
    for(int i=0; i<G->n; i++) {
        ArcNode *p=G->adjlist[i].firstarc;
        while(p!=NULL) {
            ArcNode *q=p;
            p=p->nextarc;
            delete q;
        }
	}
    delete G;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShortestPathQuery(MatrixGraph g) {	// 景点最短路径查询
    int choice=0;
	char c='N';
    do {
    	choice=999; c='N';
        system("cls");
        cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
        cout<<"           校园景点景点最短路径查询           "<<endl;
        cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
        cout<<"          1 迪杰斯特拉(Dijkstra)算法          "<<endl;
        cout<<"          2 弗 洛 伊 德 (Floyd) 算法          "<<endl;
        cout<<"          0      返回主菜单                   "<<endl;
        cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
        cout<<"\n请选择(0~4): ";
		cin>>(c);
        choice=input(c);
        clearInputBuffer();
        
        switch(choice) {
        	case 0:
                return;
            case 1: {  // 迪杰斯特拉(Dijkstra)算法
                char name[20];
                int v=-1;
                do {
                    cout<<"请输入游览线路起点景点名称：";
                    cin.getline(name, 20);
                    v=LocateSpotPos(g, name);
                    if(v!=-1)
                        break;
                    else
                        cout<<"在校园地图中未找到景点名称为 "<<name<<" 的景点！"<<endl; 
                } while(v==-1);
                cout<<"\n从 "<<name<<" 出发，迪杰斯特拉(Dijkstra)算法查询到的最短路径如下："<<endl;
                cout<<"----------------------------------------"<<endl;
                Dijkstra(g, v);    
                cout<<"结束！"<<endl; 
                break;
            }
            case 2:  // 弗洛伊德(Floyd)算法
                cout<<"弗洛伊德 (Floyd) 算法查询到的最短路径如下："<<endl;
                Floyd(g);
                cout<<"结束！"<<endl; 
                break;
            default:
                cout<<"输入错误，请重新输入"<<endl;
        }
    //////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
    } while(choice);
}

// 迪杰斯特拉算法
void Dijkstra(MatrixGraph g, int v) {    
    int dist[MAX];
    int path[MAX]; 
    int S[MAX];
    int mindist, i, j, u;
    
    for(i=0; i<g.VexNum; i++) {  // dist、S初始化
        dist[i]=g.Edges[v][i];
        S[i]=0;
        if(g.Edges[v][i]<INF)
            path[i]=v;
        else
            path[i]=-1;
    }
    
    S[v]=1;
    path[v]=v;
    
    for(i=0; i<g.VexNum-1; i++) {    
        mindist=INF;
        for(j=0; j<g.VexNum; j++)  // 求尚未考虑的、距离最小的顶点u
            if (S[j]==0 && dist[j]<mindist) {    
                u=j;
                mindist=dist[j];
            }
        
        S[u]=1;  // 将顶点u加入S集合
        
        for(j=0; j<g.VexNum; j++)  // 考虑顶点u,求s到每个顶点j的最短路径长度
            if(S[j]==0 && g.Edges[u][j]<INF && dist[u]+g.Edges[u][j]<dist[j]) {
                dist[j]=dist[u]+g.Edges[u][j];
                path[j]=u;
            }
    }
    Disppath(g, dist, path, S, v);
}

// 输出最短路径函数 
void Disppath(MatrixGraph g, int dist[], int path[], int S[], int v) {                    
    int i, j, k;
    int apath[MAX], d; 
    
    for(i=0; i<g.VexNum; i++)    
        if(S[i]==1 && i!=v) {
            cout<<"从顶点 "<<g.Vexs[v].Name<<" 到顶点 "<<g.Vexs[i].Name;
            cout<<" 的路径长度为："<<dist[i]<<endl;
            d=0;
            apath[d]=i;
            k=path[i];
            if(k==-1) {  // 无路径的情况 
                cout<<"无路径！"<<endl;
            } else {
                while(k!=v) {
                    d++;
                    apath[d]=k;
                    k=path[k];
                }
                d++;
                apath[d]=v;
                cout<<"路径：";
                cout<<g.Vexs[apath[d]].Name;  
                for(j=d-1; j>=0; j--)
                    cout<<" ---> "<<g.Vexs[apath[j]].Name;
                cout<<endl;
            }
            cout<<"----------------------------------------"<<endl;
        }
}

// Floyd算法
void Floyd(MatrixGraph g) {    
    int A[MAX][MAX], path[MAX][MAX];
    int i, j, k;
    
    for(i=0; i<g.VexNum; i++)
        for(j=0; j<g.VexNum; j++) {
            A[i][j]=g.Edges[i][j];
            if(i!=j && g.Edges[i][j]<INF)
                path[i][j]=i;      // 顶点i到j有边时
            else
                path[i][j]=-1;     // 顶点i到j没有边时
        }
    
    for(k=0; k<g.VexNum; k++)   // 依次考察所有顶点
        for(i=0; i<g.VexNum; i++) 
            for(j=0; j<g.VexNum; j++)
                if(A[i][j]>A[i][k]+A[k][j]) {    
                    A[i][j]=A[i][k]+A[k][j];  // 修改最短路径长度
                    path[i][j]=path[k][j];      // 修改最短路径
                }
    Dispath(g, A, path);
}

void Dispath(MatrixGraph g, int A[][MAX], int path[][MAX]) {    
    int i, j, k, s;
    int apath[MAX], d;  // 存放一条最短路径中间顶点(反向)及其顶点个数
    
    for(i=0; i<g.VexNum; i++)
        for(j=0; j<g.VexNum; j++)
            if(i!=j && A[i][j]<INF) {
                cout<<"从 "<<g.Vexs[i].Name<<" 到 "<<g.Vexs[j].Name;
                cout<<" 的最短路径为："<<endl;
                k=path[i][j];
                d=0;
                apath[d]=j;  // 路径上添加终点
                while(k!=i && k!=-1 && d<MAX-1) {  // 路径上添加中间点
                    d++;
                    apath[d]=k;
                    k=path[i][k];
                }
                if(k==-1) {
                    cout<<"无路径！"<<endl;
                } else {
                    d++; 
                    apath[d]=i;  // 路径上添加起点
                    cout<<g.Vexs[apath[d]].Name;
                    for(s=d-1; s>=0; s--)  // 输出路径上的中间顶点
                        cout<<" ---> "<<g.Vexs[apath[s]].Name; 
                    cout<<"\t路径长度为："<<A[i][j]<<endl;       
                }
                cout<<"----------------------------------------"<<endl;
            }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PipelineSystemOptimal(MatrixGraph g) {	// 管道系统最优布设
    int choice=0;
	char c='N';
    do {
    	choice=999; c='N';
        system("cls");
        cout<<"##############################################"<<endl;
        cout<<"             校园管道系统最优布设             "<<endl;
        cout<<"##############################################"<<endl;
        cout<<"           1  普 里 姆( Prim )算法           "<<endl;
        cout<<"           2 克鲁斯卡尔(Kruskal)算法         "<<endl;
        cout<<"           0      返回主菜单                 "<<endl;
        cout<<"##############################################"<<endl;
        cout<<"\n请选择(0~2): ";
		cin>>(c);
        choice=input(c);
        clearInputBuffer();
        
        switch(choice) {
        	case 0:
                return;
            case 1: {  // 普里姆(Prim)算法
                char name[20];
                int v=-1;
                cout<<"请输入管道系统最优布设起点景点名称：";
                cin.getline(name, 20);
                v=LocateSpotPos(g, name);
                if(v==-1) {
                    cout<<"未找到该景点！"<<endl;
                } else {
                    Prim(g, v);
                }
                break;
            }
            case 2:  // 克鲁斯卡尔(Kruskal)算法
                Kruskal(g);
                break;    
            default:
                cout<<"输入错误，请重新输入"<<endl;
        }
    //////////////////////////////////////
		cout<<"\n\n按任意键继续....";
		c=getchar();
    } while(choice);
}

void Prim(MatrixGraph g, int v) {
    int lowcost[MAX];      // 最小权值
    int closest[MAX];      // 顶点下标
    bool s[MAX]={false}; // 标记数组
    
    s[v]=true;  // 将v加入U集合
    
    // 初始化lowcost和closest
    for(int i=0; i<g.VexNum; i++)
        if(i!=v) {
            lowcost[i]=g.Edges[v][i];
            closest[i]=v;
        }
    
    cout<<"\n普里姆(Prim)算法最小生成树："<<endl;
    cout<<"==============================="<<endl;
    
    int totalWeight=0;
    for (int i=1; i<g.VexNum; i++) {
        int min=INF;
        int k=-1;
        
        // 在V-U中找出离U最近的顶点k
        for(int j=0; j<g.VexNum; j++)
            if(!s[j] && lowcost[j]<min) {
                min=lowcost[j];
                k=j;
            }
        
        if (k == -1) break;
        
        // 输出选择的边
        cout<<g.Vexs[closest[k]].Name<<" --- "<<g.Vexs[k].Name;
        cout<<"  权重: "<<min<<endl;
        totalWeight+=min;
        
        s[k]=true;  // 将k加入U集合
        
        // 调整lowcost和closest
        for(int j=0; j<g.VexNum; j++)
            if(!s[j] && g.Edges[k][j]<lowcost[j]) {
                lowcost[j]=g.Edges[k][j];
                closest[j]=k;
            }
    }
    cout<<"==============================="<<endl;
    cout<<"最小生成树总权重: "<<totalWeight<<endl;
}

void Kruskal(MatrixGraph g) {
    EdgeType edges[MAX * MAX];
    int k=0;
    
    // 提取所有边
    for(int i=0; i<g.VexNum; i++)
        for(int j=i+1; j<g.VexNum; j++)
            if(g.Edges[i][j]!=INF && g.Edges[i][j]!=0) {
                edges[k].u=i;
                edges[k].v=j;
                edges[k].Weight=g.Edges[i][j];
                k++;
            }
    
    // 对边按权重排序
    BubbleSort(edges, k);
    
    // Kruskal算法
    int vset[MAX];  // 并查集
    for(int i=0; i<g.VexNum; i++)
        vset[i]=i;
    
    cout<<"\n克鲁斯卡尔(Kruskal)算法最小生成树："<<endl;
    cout<<"==============================="<<endl;
    
    int totalWeight=0;
    int count=0;
    
    for(int i=0; i<k && count<g.VexNum-1; i++) {
        int u=edges[i].u;
        int v=edges[i].v;
        
        // 查找u和v的根
        int rootU=u;
        while(vset[rootU]!=rootU)
            rootU=vset[rootU];
        
        int rootV=v;
        while(vset[rootV]!=rootV)
            rootV=vset[rootV];
        
        // 如果u和v不在同一集合，则加入
        if (rootU!=rootV) {
            cout<<g.Vexs[u].Name<<" --- "<<g.Vexs[v].Name;
            cout<<"  权重: "<<edges[i].Weight<<endl;
            totalWeight+=edges[i].Weight;
            count++;
            
            // 合并集合
            vset[rootV]=rootU;
        }
    }
    cout<<"==============================="<<endl;
    cout<<"最小生成树总权重: "<<totalWeight<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BubbleSort(EdgeType R[], int n)
{
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++)
            if(R[j].Weight>R[j+1].Weight) {
                EdgeType temp=R[j];
                R[j]=R[j+1];
                R[j+1]=temp;
            }
}
