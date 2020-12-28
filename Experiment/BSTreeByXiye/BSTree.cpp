#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
using namespace std;

#define MaxSize 100

typedef int DataType;

//二叉排序树结构定义
typedef struct node
{
	DataType data;
	struct node *lchild,*rchild;
	int flag;
}BSTNode,*BSTree;

//初始化一个二叉排序树结点
BSTree InitNode(DataType data)
{
	BSTree Node=(BSTree)malloc(sizeof(BSTNode));
	Node->data=data;
	Node->lchild=NULL;
	Node->rchild=NULL;
	Node->flag=0;
	return Node;
}

//若在二叉排序树中不存在关键字等于data的元素，插入该元素
void InsertBST(BSTree *root, DataType data)
{
	if(*root==NULL)
	{
		*root=InitNode(data);
	}
	else 
	{
		if(data<(*root)->data) InsertBST(&((*root)->lchild),data);
		else 
		{
			if(data>(*root)->data) InsertBST(&((*root)->rchild),data);
		}
	}
}

//从文件输入元素的值，创建相应的二叉排序树
void CreateBST(BSTree *root,const char *filename)
{ 
	FILE *fp;
	DataType keynumber;
	*root=NULL;
	fp=fopen(filename,"r+");
	if(fp==NULL) exit(0x01);
	while(EOF!=fscanf(fp,"%d",&keynumber)) InsertBST(root,keynumber);
}

//先序遍历二叉树, root为指向二叉树根结点的指针
void PreOrderCleanFlag(BSTree root) 
{
	if(root!=NULL)
	{
		root->flag=0;
		PreOrderCleanFlag(root->lchild);
		PreOrderCleanFlag(root->rchild);
	}
}

//中序遍历二叉树, root为指向二叉树根结点的指针
void InOrder(BSTree root) 
{
	if(root!=NULL)
	{
		InOrder(root->lchild);
        printf("%d ",root->data);
		InOrder(root->rchild);
	}
}

//后序遍历二叉树, root为指向二叉树根结点的指针
void PostOrder(BSTree root) 
{
	if(root!=NULL)
	{
		PostOrder(root->lchild);
		PostOrder(root->rchild);
        printf("%d ",root->data);
	}
}

//层序遍历, root为指向二叉树根结点的指针
void LevelOrder(BSTree root)
{
	//定义一个队列 
    BSTree Queue[MaxSize];
    
    int front=-1,rear=0;
    // 若二叉树为空，遍历结束 
    if(root==NULL) return;
    //根结点进入队列 
    Queue[rear]=root;
    //若队列不为空，遍历，否则，遍历结束 
    while(rear!=front)
	{
		//出队，打印出队结点的值 
        front++;
        printf("%d ",Queue[front]->data);
        //若有左孩子，左孩子进入队列 
        if(Queue[front]->lchild!=NULL)
		{
            rear++;
            Queue[rear]=Queue[front]->lchild;
        }
        //若有右孩子，右孩子进入队列 
        if(Queue[front]->rchild!=NULL)
		{
            rear++;
            Queue[rear]=Queue[front]->rchild;
        }
    }
}

//删除排序二叉树, root为指向二叉树根结点的指针
void DestroyBST(BSTree root)
{
	if(root!=NULL)
	{
		PreOrderCleanFlag(root->lchild);
		PreOrderCleanFlag(root->rchild);
		free(root);
	}
}

//在根指针root所指二叉排序树root上，查找关键字等于data的结点，若查找成功，返回指向该元素结点指针，否则返回空指针
BSTree SearchBST(BSTree root,DataType data)
{ 
	BSTree q;
	q=root;
	while(q)
	{
		q->flag=1;
		if(q->data==data)
		{
			q->flag=2;
			return q;		
		}
		if(q->data>data) q=q->lchild;
		else q=q->rchild;
	}
	return NULL;
}

//在二叉排序树root中删去关键字为value的结点
BSTree DeleteBST(BSTree root,DataType value)
{
	BSTNode *p,*f,*s,*q;
	p=root; 
	f=NULL;
    //查找关键字为value的待删结点p
	while(p)
	{
        //找到则跳出循环,f指向p结点的双亲结点
		if(p->data==value) break;
		f=p;
		if(p->data>value) p=p->lchild;
		else p=p->rchild;
	}
    //若找不到，返回原来的二叉排序树
	if(p==NULL)  return root;
    //若p无左子树
	if(p->lchild==NULL)
	{ 
		if(f==NULL) root=p->rchild;
		else 
        {
			if(f->lchild==p) f->lchild=p->rchild;
			else f->rchild=p->rchild;
            //释放被删除的结点p
			free(p);
        }
	}
    //若p有左子树
	else
	{ 
		q=p; 
		s=p->lchild;
		while(s->rchild)
		{
			q=s; 
			s=s->rchild;
		}
		if(q==p) 
			q->lchild=s->lchild;
		else 
			q->rchild=s->lchild;
		p->data=s->data;
		free(s);
	}
	return root;
}

//在根指针root所指二叉排序树中交换左右子树 
void Exchange(BSTree root)
{
    if(root==NULL) return;
    if(root->lchild==NULL && root->rchild==NULL) return;
    BSTree temp=root->lchild;
    root->lchild=root->rchild;
    root->rchild=temp;
    Exchange(root->lchild);
    Exchange(root->rchild);
}

//在根指针root所指二叉排序树中求树的深度 
int Depth(BSTree root)
{
    if(root==NULL) return 0;
    return 1+max(Depth(root->lchild),Depth(root->rchild));
}

int max(int a,int b)
{
    if (a>b) return a;
    return b;
}

//在根指针root所指二叉排序树中计算总结点个数 
int CountBiNode(BSTree root)
{
    if(root==NULL) return 0;
    int left=CountBiNode(root->lchild);
    int right=CountBiNode(root->rchild);
    return left+right+1;
}

//根指针root所指二叉排序树中计算叶子结点个数 
int CountLeaf(BSTree root)
{
    if(root==NULL) return 0;
    if(root->rchild==NULL && root->lchild==NULL) return 1;
    return (CountLeaf(root->lchild)+CountLeaf(root->rchild));
}

void DotOrderList(BSTree root,FILE *fp)
{
	if(root==NULL)
		return;
	char lpoint=root->lchild ? ' ' : ' ';
	char rpoint=root->rchild ? ' ' : ' ';
	if(root->flag==1)
	{
		fprintf(fp,"%d[label = \"<l>%c|<d>%d|<r>%c\",color=green];\n",root->data,lpoint,root->data,rpoint);
	}
	else if(root->flag==2)
	{
		fprintf(fp,"%d[label = \"<l>%c|<d>%d|<r>%c\",color=red,fontcolor=red];\n",root->data,lpoint,root->data,rpoint);
	}
	else
		fprintf(fp,"%d[label = \"<l>%c|<d>%d|<r>%c\"];\n",root->data,lpoint,root->data,rpoint);
	DotOrderList(root->lchild,fp);
	DotOrderList(root->rchild,fp);
}

void DotOrderLink(BSTree root,FILE *fp) 
{
	if(root==NULL)
		return;
	
	if(root->lchild)
		fprintf(fp,"%d:l:sw -> %d:d;\n",root->data,root->lchild->data);
	
	if(root->rchild)
		fprintf(fp,"%d:r:se -> %d:d;\n",root->data,root->rchild->data);

	DotOrderLink(root->lchild,fp);
	DotOrderLink(root->rchild,fp);
}

void MakeDot(BSTree root,char *tital=NULL)
{
	FILE *fp=fopen("bstree.gv","w+");
	fprintf(fp,"digraph BSTree {\n");
	if(tital != NULL)
	{
		fprintf(fp,"labelloc = t; labeljust = l;\n");
		fprintf(fp,"label = \"%s\";\n",tital);		
	}
	fprintf(fp,"node [fontname = Verdana, color=navy, shape=record, height=.1];\n");
	fprintf(fp,"edge [fontname = Verdana, color=navy, style=solid];\n");
	DotOrderList(root,fp);
	DotOrderLink(root,fp);
	fprintf(fp,"}\n\n");
	fclose(fp);
}

int main()
{
	BSTree root;
	CreateBST(&root,"./data.txt");
	MakeDot(root);
	PreOrderCleanFlag(root);
	system("dot.exe -Tpng bstree.gv -o bstree.png");
	
	printf("该二叉排序树的深度为： %d\n该二叉排序树的总结点数为： %d\n该二叉排序树的叶子结点数为： %d\n中序遍历的结果为：\n",Depth(root),CountBiNode(root),CountLeaf(root));
	InOrder(root);
	
	SearchBST(root,62);
	MakeDot(root);
	system("dot.exe -Tpng bstree.gv -o bstree_search(62).png");
	
	PreOrderCleanFlag(root);
	SearchBST(root,98); 
	MakeDot(root);
	system("dot.exe -Tpng bstree.gv -o bstree_search(98).png");
	
	PreOrderCleanFlag(root);
	DeleteBST(root,822);
	MakeDot(root);
	system("dot.exe -Tpng bstree.gv -o bstree_delete(822).png");
	 
	DestroyBST(root);
	return 0;
}
