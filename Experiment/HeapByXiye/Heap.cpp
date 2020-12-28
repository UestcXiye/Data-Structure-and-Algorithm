#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<time.h>
using namespace std;

typedef int DataType;

#define TOTALNUM 200

char figlabel[TOTALNUM];
char orderstr[TOTALNUM];
int heap[TOTALNUM];
int nNum,HeapSize;

//交换函数
void swap(int *a,int *b)
{
    *a=*a+*b;
    *b=*a-*b;
    *a=*a-*b;
}

//堆遍历
void HeapTraverse(int a[],int size)
{
    for(int i=0;i<size;i++) printf("%d ",a[i]);
    printf("\n");
}

//带起始点的堆调整
void HeapShift(int a[],int size,int start)
{
    int dad=start,son=2*dad+1;

    while(son<=size)
    {
        // 找子结点的最大值
        if(son+1<=size && a[son]>a[son+1]) son++;

        if(a[dad]<a[son]) return;
        else
        {
            swap(&a[dad],&a[son]);
            dad=son;
            son=2*dad+1;
        }
    }
}

//堆排序
void HeapSort(int a[],int size)
{
    //构建初始堆
    for(int i=size/2-1;i>=0;i--)
    {
        HeapShift(a,size-1,i);
    }
    for(int j=size-1;j>0;j--)
    {
        // 堆顶元素和堆中的最后一个元素交换
        swap(&a[0],&a[j]);
        // 重新调整结构，使其继续满足堆定义
        HeapShift(a,j-1,0);
    }
}

//堆调整
void HeapAdjust(int a[],int i,int size)
{
    int child;
    int temp;
    for(;2*i+1<size;i=child)
    {
        child=2*i+1;
        if(child<size-1 && a[child+1]<a[child]) child++;
        if(a[i]>a[child])
        {
            temp=a[i];
            a[i]=a[child];
            a[child]=temp;
        }
        else break;
    }
}

void DotHeap(int heap[],int n,char *label,int input=-1,int drop=-1)
{
	FILE *fpTree=fopen("heapT.gv","w+");
	fprintf(fpTree,"digraph heapT {\n");
	fprintf(fpTree,"fontname = \"Microsoft YaHei\"; labelloc = t; labeljust = l; rankdir = TB;\n");
	fprintf(fpTree,"label = \"%s\";\n",label);
	fprintf(fpTree,"node [fontname = \"Microsoft YaHei\", color=darkgreen, shape=circle, height=.1];\n");
	fprintf(fpTree,"edge [fontname = \"Microsoft YaHei\", color=darkgreen, style=solid, arrowsize=0.7];\n");	
	
	if(input!=-1 && drop!=-1)
	{
		fprintf(fpTree,"in%d[label=\"%d\",shape=Mcircle,fontcolor=blue,color=blue];\n",input,input);
	}

	for(int i=0;i<n;i++)
	{
		fprintf(fpTree,"%d[label=\"%d\"];\n",heap[i],heap[i]);
	}
	
	if(input!=-1 && drop!=-1 && input!=drop)
	{
		fprintf(fpTree,"%d[label=\"%d\",shape=circle,fontcolor=blue,color=blue];\n",input,input);
	}
	
	if(input!=-1 && drop!=-1)
	{
		if(input==drop)
		{
			fprintf(fpTree,"%d[label=\"%d\",shape=doublecircle,fontcolor=darkgreen,color=darkgreen];\n",heap[0],heap[0]);
		}
	}
	
	if(input!=-1 && drop!=-1)
	{
		if(input!=drop)
		{
			fprintf(fpTree,"dp%d[label=\"%d\",shape=doublecircle,fontcolor=red,color=red];\n",drop,drop);
		}
		else
		{
			fprintf(fpTree,"dp%d[label=\"%d\",shape=Mcircle,fontcolor=red,color=red];\n",drop,drop);
		}
	}
	
	if(input!=-1 && drop!=-1)
	{
		fprintf(fpTree,"{rank = same; in%d; %d; dp%d;};\n",input,heap[0],drop);
		fprintf(fpTree,"in%d -> %d[color=blue];\n",input,heap[0]);
		fprintf(fpTree,"%d -> dp%d[color=red];\n",heap[0],drop);
	}

	for(int i=0;i<n;i++)
	{
		if(2*(i+1)-1<n) fprintf(fpTree,"%d:sw -> %d;\n",heap[i],heap[2*(i+1)-1]);
		if(2*(i+1)<n) fprintf(fpTree,"%d:se -> %d;\n",heap[i],heap[2*(i+1)]);
	}

	fprintf(fpTree,"node [fontname = \"Microsoft YaHei\", color=darkgreen, shape=record, height=.1];\n");
	fprintf(fpTree,"edge [fontname = \"Microsoft YaHei\", color=darkgreen, style=solid];\n");
	fprintf(fpTree,"struct [ label = \"{value|address} |");
	fprintf(fpTree,"{|%d} ",0);
	for(int i=0;i<n;i++)
	{
		fprintf(fpTree,"| {%d|%d} ",heap[i],i+1);
	}
	fprintf(fpTree,"\"]; \n");
	fprintf(fpTree,"%d -> struct[color=white]; \n",heap[n-1]);
	fprintf(fpTree,"}\n\n");
	fclose(fpTree);
}

int main()
{
	double start,finish;
	start=clock();
	
	nNum=0;
	HeapSize=10;
	memset(heap,'\0',sizeof(heap));

	FILE *fp;
	fp=fopen("./data.txt","r+");

	while(nNum<HeapSize && EOF!=fscanf(fp,"%d",&heap[nNum++]));
	
	sprintf(figlabel,"Initial Heap");
	DotHeap(heap,nNum,figlabel);
	sprintf(orderstr,"dot.exe -Tpng heapT.gv -o IniT.png");
	system(orderstr);
	
	for(int i=nNum/2;i>=0;i--)
	{
		HeapAdjust(heap,i,nNum);
	}
	sprintf(figlabel,"Adjust Heap");
	DotHeap(heap,nNum,figlabel);
	sprintf(orderstr,"dot.exe -Tpng heapT.gv -o AdjT.png");
	system(orderstr);
		
	int temp;
	int k=11;
	while(EOF!=fscanf(fp,"%d",&temp))
	{
		sprintf(figlabel,"Input %d Drop %d",temp);
		if(temp>heap[0])
		{
			int pretop=heap[0];
			heap[0]=temp;
			HeapAdjust(heap,0,nNum);
			sprintf(figlabel,"Time = %d",k);
			DotHeap(heap,nNum,figlabel,temp,pretop);			
		}
		else
		{
			sprintf(figlabel,"Time = %d",k);
			DotHeap(heap,nNum,figlabel,temp,temp);	
		}
		
		sprintf(orderstr,"dot.exe -Tpng heapT.gv -o Tree%02d.png",k++);
		system(orderstr);
	}
	sprintf(figlabel,"Current Heap Situation");
	DotHeap(heap,nNum,figlabel,temp);
	sprintf(orderstr,"dot.exe -Tpng heapT.gv -o FinaT.png");
	system(orderstr);

	finish=clock();
	printf("本次运行耗时： %f s\n",(finish-start)/CLOCKS_PER_SEC);

	return 0;
}
