#include<iostream>
#include<stdio.h>
#include<string>
#include<queue>
#include<string.h>
using namespace std;

#define INFINITY 0X7fffffff
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAX_VERTEX_NUM 30

typedef char InfoType;
typedef int Status;
typedef int Boolean;
typedef string VertexType;
typedef enum {DG,DN,UDG,UDN} GraphKind;

Boolean visited[MAX_VERTEX_NUM];

typedef struct ArcCell///弧(邻接矩阵)
{
    int adj;
    InfoType *info;
} ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct graph
{
    string vexs[MAX_VERTEX_NUM];//结点名
    AdjMatrix arcs;             //邻接矩阵
    int vexnum,arcnum;          //结点数，弧数
    GraphKind kind;
}Graph;

Status (*VisitFunc)(Graph G,int v);

Status LocateVex(Graph G,string name)//获取结点标号
{
    for(int i=0; i<G.vexnum; i++)
        if(name==G.vexs[i]) return i;
    return -1;
}

Status CreateDG(Graph &G)//邻接矩阵(建立无权有向图)
{
    int IncInfo;
    printf("建立无权有向图，请依次输入总结点数、总边数、是否包含信息:\n");
    scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
    printf("请为从1至n个结点命名:\n");
    for(int i=0; i<G.vexnum; i++)
        cin>>G.vexs[i];
    for(int i=0; i<G.vexnum; i++)
        for(int j=0; j<G.vexnum; j++)
        {
            G.arcs[i][j].adj=INFINITY;
            G.arcs[i][j].info=NULL;
        }
    string v1,v2;
    printf("请输入%d组由左指向右的有向边:\n",G.arcnum);
    for(int k=0; k<G.arcnum; k++)
    {
        cin>>v1>>v2;
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        G.arcs[i][j].adj=TRUE;//无权
        if(IncInfo) scanf("%s",G.arcs[i][j].info);
    }
    return OK;
}

Status CreateDN(Graph &G)//邻接矩阵(建立带权有向网)
{
    int IncInfo;
    printf("建立带权有向网，请依次输入总结点数、总边数、是否包含信息:\n");
    scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
    printf("请为从1至n个结点命名:\n");
    for(int i=0; i<G.vexnum; i++)
        cin>>G.vexs[i];
    for(int i=0; i<G.vexnum; i++)
        for(int j=0; j<G.vexnum; j++)G.arcs[i][j].adj=INFINITY,G.arcs[i][j].info=NULL;
    string v1,v2;
    int w;
    printf("请输入%d组由左指向右的有向边与边权:\n",G.arcnum);
    for(int k=0; k<G.arcnum; k++)
    {
        cin>>v1>>v2>>w;
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        G.arcs[i][j].adj=w;//带权
        if(IncInfo) scanf("%s",G.arcs[i][j].info);
    }
    return OK;
}

Status CreateUDG(Graph &G)//邻接矩阵(建立无权无向图)
{
    int IncInfo;
    printf("建立无权无向图，请依次输入总结点数、总边数、是否包含信息:\n");
    scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
    printf("请为从1至n个结点命名:\n");
    for(int i=0; i<G.vexnum; i++)
        cin>>G.vexs[i];
    for(int i=0; i<G.vexnum; i++)
        for(int j=0; j<G.vexnum; j++)
            G.arcs[i][j].adj=INFINITY,G.arcs[i][j].info=NULL;
    string v1,v2;
    printf("请输入%d组相互依附的两结点:\n",G.arcnum);
    for(int k=0; k<G.arcnum; k++)
    {
        cin>>v1>>v2;
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        G.arcs[i][j].adj=TRUE;//无权
        if(IncInfo) scanf("%s",G.arcs[i][j].info);
        G.arcs[j][i]=G.arcs[i][j];//无向图,结构体赋值
    }
    return OK;
}

Status CreateUDN(Graph &G)//邻接矩阵(建立带权无向网)
{
    int IncInfo;
    printf("建立带权无向网，请依次输入总结点数、总边数、是否包含信息:\n");
    scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
    printf("请为从1至n个结点命名:\n");
    for(int i=0; i<G.vexnum; i++)
        cin>>G.vexs[i];
    for(int i=0; i<G.vexnum; i++)
        for(int j=0; j<G.vexnum; j++)
            G.arcs[i][j].adj=INFINITY,G.arcs[i][j].info=NULL;
    string v1,v2;
    printf("请输入%d组相互依附的两结点与边权:\n",G.arcnum);
    int w;//边权
    for(int k=0; k<G.arcnum; k++)
    {
        cin>>v1>>v2>>w;
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        G.arcs[i][j].adj=w;//带权
        if(IncInfo) scanf("%s",G.arcs[i][j].info);
        G.arcs[j][i]=G.arcs[i][j];//无向图,结构体赋值
    }
    return OK;
}

void DFS(Graph G,int v)//邻接矩阵DFS
{
    visited[v]=TRUE;
    VisitFunc(G,v);
    for(int w=0; w<G.vexnum; w++)
        if(G.arcs[v][w].adj!=INFINITY&&!visited[w])
            DFS(G,w);
}

void DFSTraverse(Graph G,Status (*Visit)(Graph G,int v))
{
    VisitFunc=Visit;
    printf("请输入深度优先搜索起始结点:\n");
    for(int v=0; v<G.vexnum; v++)
        visited[v]=FALSE;
    string st;
    cin>>st;
    int tmp=LocateVex(G,st);
    printf("深度优先搜索遍历序列:\n");
    DFS(G,tmp);
    for(int v=0; v<G.vexnum; v++)
        if(!visited[v])
            DFS(G,v);
    printf("\n");
}

void BFSTraverse(Graph G,Status (*Visit)(Graph G,int v))//邻接矩阵BFS
{
    for(int v=0; v<G.vexnum; v++)visited[v]=FALSE;
    queue<int>Q;
    printf("请输入广度优先搜索起始结点:\n");
    string st;
    cin>>st;
    printf("广度优先搜索遍历序列:\n");
    int temp=LocateVex(G,st);
    Visit(G,temp);
    Q.push(temp);
    visited[temp]=TRUE;
    while(!Q.empty())
    {
        int tmp=Q.front();
        Q.pop();
        for(int w=0; w<G.vexnum; w++)
        {
            if(!visited[w]&&G.arcs[tmp][w].adj!=INFINITY)
            {
                visited[w]=TRUE;
                Visit(G,w);
                Q.push(w);
            }
        }
    }
    for(int v=0; v<G.vexnum; v++)//剩余连通分量
    {
        if(!visited[v])
        {
            visited[v]=TRUE;
            Visit(G,v);
            Q.push(v);
            while(!Q.empty())
            {
                int tmp=Q.front();
                Q.pop();
                for(int w=0; w<G.vexnum; w++)
                {
                    if(!visited[w]&&G.arcs[tmp][w].adj!=INFINITY)
                    {
                        visited[w]=TRUE;
                        Visit(G,w);
                        Q.push(w);
                    }
                }
            }
        }
    }
    printf("\n");
}

Status CreateGraph(Graph &G)///邻接矩阵
{
    printf("请输入建图类型(1:无权有向图、2:带权有向网、3:无权无向图、4:带权无向网):\n");
    scanf("%d",&G.kind);///输入图的种类
    switch(G.kind-1)
    {
        case DG:
            return CreateDG(G);
        case DN:
            return CreateDN(G);
        case UDG:
            return CreateUDG(G);
        case UDN:
            return CreateUDN(G);
        default:
            return ERROR;
    }
}

Status visit(Graph G,int v)///邻接矩阵遍历
{
    cout<<G.vexs[v]<<" ";
}

int main()
{
    while(true)
    {
        Graph g;
        CreateGraph(g);///邻接矩阵
        DFSTraverse(g,visit);///深搜邻接矩阵
        BFSTraverse(g,visit);///广搜邻接矩阵
    }
    system("pause");
    return 0;
}
/*
测试输入：
3
8 9 0
V1 V2 V3 V4 V5 V6 V7 V8

V1 V2
V2 V4
V4 V8
V8 V5
V2 V5
V1 V3
V3 V6
V3 V7
V6 V7

V1

V1
*/
