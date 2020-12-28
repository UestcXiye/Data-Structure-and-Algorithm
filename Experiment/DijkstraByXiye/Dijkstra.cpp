#include<iostream>
#include<stack>
#include<fstream>

using namespace std;

typedef struct node
{
    int **edges;//邻接矩阵
    int n;//顶点数
    int e;//边数
}Graph;

//初始化图
Graph CreateGraph(int n,int e)
{
	Graph graph;
	graph.n=n;
	graph.e=e;
	graph.edges=(int **)malloc(sizeof(int *)*graph.n);

	for(int i=0;i<graph.n;i++)
	{
		graph.edges[i]=(int *)malloc(sizeof(int)*graph.n);
	}

	for(int i=0;i<graph.n;i++)
    {
		for(int j=0;j<graph.n;j++)
        {
			graph.edges[i][j]=0;
		}
	}

	return graph;
}

//初始化dist
int *CreateDist(int size)
{
	int *dist=new int[size];
	return dist;
}

//初始化path
int *CreatePath(int size)
{
	int *path=new int[size];
	return path;
}

//初始化visited
bool *CreateVisited(int size)
{
	bool *visited=(bool *)malloc(sizeof(bool)*size);
	return visited;
}

//释放邻接矩阵空间
void FreeGraph(Graph g)
{
	for(int i=0;i<g.n;i++)
	{
		free(g.edges[i]);
	}
	free(g.edges);
}

void DijkstraDot(Graph g,int *path,bool *visited,int vs)
{
	FILE *fp=fopen("dijkstra.gv","w+");
	fprintf(fp,"digraph Dijkstra {\nnode [shape=ellipse];\n");
	fprintf(fp,"v%d[shape=diamond,color=red,fontcolor=red];\n",vs);

	for(int i=0;i<g.n && i!=vs;i++)
	{
		fprintf(fp,"v%d;\n",i);
	}
		
	for(int i=0;i<g.n;i++)  
	{  
		for(int j=0;j<g.n;j++)  
 		{  
 			if(g.edges[i][j])
			{
				if(visited[i] && visited[j] && path[j]==i)
				{
					fprintf(fp,"v%d[fontcolor=red,color=red];\n",i);
					fprintf(fp,"v%d[fontcolor=red,color=red];\n",j);
					fprintf(fp,"v%d->v%d[style=bold,label=%d,fontcolor=red,color=red];\n",i,j,g.edges[i][j]);
				}
				else
				{
					fprintf(fp,"v%d->v%d[style=bold,label=%d];\n",i,j,g.edges[i][j]);	
				}
			}
  		}  
   	} 
 	fprintf(fp,"}\n");
 	fclose(fp);
}

//vs表示源顶点 
void DijkstraPath(Graph g,int *dist,int *path,int vs)
{
    bool *visited=CreateVisited(g.n);
	//初始化
    for(int i=0;i<g.n;i++)
    {
        if(g.edges[vs][i]>0 && i!=vs)
        {
            dist[i]=g.edges[vs][i];
			//path记录最短路径上从vs到i的前一个顶点
            path[i]=vs; 
        }
        else
        {
			//若i不与vs直接相邻，则权值置为无穷大
            dist[i]=INT_MAX;
            path[i]=-1;
        }
        visited[i]=false;
        path[vs]=vs;
        dist[vs]=0;
    }
    FILE *fp=fopen("dijkstra.gv","w+");
	fprintf(fp,"digraph Dijkstra {\nnode [shape=ellipse];\n");
	fprintf(fp,"v%d[shape=diamond,color=red,fontcolor=red];\n",vs);

	for(int i=0;i<g.n && i!=vs;i++)
	{
		fprintf(fp,"v%d; ",i);
	}

	for(int i=0;i<g.n;i++)  
  	{  
       	for(int j=0;j<g.n;j++)  
       	{  
       		if(g.edges[i][j])
			{
				fprintf(fp,"v%d->v%d[style=bold,label=%d];\n",i,j,g.edges[i][j]);
			}
  		}  
   	}
	fprintf(fp,"}\n");
	fclose(fp);
	system("sfdp.exe -Tpng dijkstra.gv -o DijkSetp01.png");
    visited[vs]=true;
	//循环扩展n-1次
    for(int i=1;i<g.n;i++) 
    {
        int min=INT_MAX;
        int u;
		//寻找未被扩展的权值最小的顶点
        for(int j=0;j<g.n;j++)
        {
            if(!visited[j] && dist[j]<min)
            {
                min=dist[j];
                u=j;        
            }
        } 
        visited[u]=true;
		//更新dist数组的值和路径的值
        for(int k=0;k<g.n;k++) 
        {
            if(!visited[k] && g.edges[u][k]>0 && min+g.edges[u][k]<dist[k])
            {
                dist[k]=min+g.edges[u][k];
                path[k]=u; 
            }
        }
		DijkstraDot(g,path,visited,vs);
	 	char orderstr[128];
		sprintf(orderstr,"sfdp.exe -Tpng dijkstra.gv -o DijkSetp%02d.png",i+1);
		system(orderstr);        
    } 
}

//打印源顶点vs到各结点的最短路径
void PrintPath(Graph g,int *dist,int *path,int vs)
{
	for(int i=0;i<g.n;i++)
	{
		if(vs!=i)
		{
			printf("v%d -> v%d, minDist: %d, path: v%d <- ",vs,i,dist[i],i);
			int temp=path[i];
			while(vs!=temp)
			{
				printf("v%d <- ",temp);
				temp=path[temp];
		    }
		    printf("v%d",vs);
			printf("\n");
		}
	}
}

//打印邻接矩阵
void PrintGraph(Graph g)
{
	for(int i=0;i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
		{
			printf("%2d ",g.edges[i][j]);
		}
		printf("\n");
	}
}

int main(int argc,char *argv[])
{
    if(argc<3) return 0x01;

	Graph g=CreateGraph(atoi(argv[1]),atoi(argv[2]));
	int *dist=CreateDist(g.n);
    int *path=CreatePath(g.n);
	int maxsinglearch,edgeCounter;
	
	if(g.e>=g.n)
	{
		maxsinglearch=g.n;
		for(int i=0;i<g.n;i++)
		{
			g.edges[i][(i+1)%g.n]=g.n/2+rand()%maxsinglearch;
		}
		edgeCounter=g.n;		
	}
	else edgeCounter=0;
	
	maxsinglearch=g.n;
   	while(edgeCounter<g.e)
   	{
   		rand();
	   	int s=rand()%g.n;
	   	int t=rand()%g.n;
	   	
		//随机生成没有双向弧的有向图
	   	if( s!=t && !g.edges[s][t] && (g.e>3*g.n || !g.edges[t][s]))  
	   	{
	   		g.edges[s][t]=rand()%maxsinglearch;
	   		edgeCounter++;
	   	}
 	}

	printf("随机生成的邻接矩阵：\n");
	PrintGraph(g);
	printf("\n");

	int vs=0;
	
    FILE *fp=fopen("DijkInitGraph.gv","w+");
	fprintf(fp,"digraph DijkInitGraph {\nnode [shape=ellipse];\n");
	fprintf(fp,"v%d[shape=diamond];\n",vs);

	for(int i=0;i<g.n && i!=vs;i++)
	{
		fprintf(fp,"v%d; ",i);
	}

 	for(int i=0;i<g.n;i++)
    {
		for(int j=0;j<g.n;j++)  
        {
			if(g.edges[i][j])
			{
				fprintf(fp,"v%d->v%d[style=bold,label=%d];\n",i,j,g.edges[i][j]);
			}
		}
	}

 	fprintf(fp,"}\n");
 	fclose(fp);
 	system("sfdp.exe -Tpng DijkInitGraph.gv -o DijkInitGraph.png");

    //0表示输入从0号节点开始 
    DijkstraPath(g,dist,path,vs);

    //打印源顶点vs到各结点的最短路径
	printf("源顶点v0到各结点的最短路径为： \n");
	PrintPath(g,dist,path,vs);
	printf("\n");

	//释放结点
	FreeGraph(g);
		
    return 0;
}
