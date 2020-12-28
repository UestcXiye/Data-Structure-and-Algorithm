#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

#define MaxSize 100

typedef int DataType;

typedef struct node
{
	DataType data;
	int bf;
	int flag;
	struct node *lchild,*rchild;
}AVLNode,*AVLTree;

//初始化一个平衡二叉树结点
AVLTree InitNode(DataType data)
{
	AVLTree Node=(AVLTree)malloc(sizeof(AVLNode));
	Node->data=data;
	Node->lchild=NULL;
	Node->rchild=NULL;
	Node->bf=0;
	Node->flag=0;
}

//在平衡二叉树中插入值为data的元素，使之成为一棵新的平衡二叉排序树
void InsertAVL(AVLTree *root,DataType data)
{
	AVLNode *s;
	AVLNode *a,*fa,*p,*fp,*b,*c;
	s=InitNode(data);
	if(*root==NULL) *root=s;
	else 
	{ 
		//首先查找S的插入位置fp，同时记录距S的插入位置最近且平衡因子不等于0（等于-1或1）的结点A，A为可能的失衡结点
		a=*root; 
		fa=NULL;
		p=*root; 
		fp=NULL;
		while(p!=NULL)
		{ 
			if(p->bf!=0) 
			{
				a=p;
				fa=fp;
			}
			fp=p;
			if (data<p->data) p=p->lchild;
			else if(data>p->data) p=p->rchild;
			else
			{
				free(s);
				return;			
			}
		}
		//插入S
		if(data<fp->data) fp->lchild=s;
		else fp->rchild=s;
		//确定结点B，并修改A的平衡因子
		if (data<a->data)
		{
			b=a->lchild;
			a->bf=a->bf+1;
		}
		else
		{
			b=a->rchild;
			a->bf=a->bf-1;
		}
		//修改B到S路径上各结点的平衡因子（原值均为0）
		p=b;
		while(p!=s)
			if(data<p->data)
			{
				p->bf=1;
				p=p->lchild;
			}
			else
			{
				p->bf=-1;
				p=p->rchild;
			}
		//判断失衡类型并做相应处理
		if(a->bf==2 && b->bf==1)       /* LL型 */
		{
			b=a->lchild;
			a->lchild=b->rchild;
			b->rchild=a;
			a->bf=0;
			b->bf=0;
			if(fa==NULL) *root=b;
			else 
			{
				if(a==fa->lchild) fa->lchild=b;
				else fa->rchild=b;
			}
		}
		else if(a->bf==2 && b->bf==-1)       /* LR型 */
		{
			b=a->lchild;
			c=b->rchild;
			b->rchild=c->lchild;
			a->lchild=c->rchild;
			c->lchild=b;
			c->rchild=a;
			if(s->data<c->data)
			{ 
				a->bf=-1;
				b->bf=0;
				c->bf=0;
			}
			else if(s->data>c->data)
			{
				a->bf=0;
				b->bf=1;
				c->bf=0;
			}
			else
			{ 
				a->bf=0;
				b->bf=0;
			}
			if(fa==NULL) *root=c;
			else if(a==fa->lchild) fa->lchild=c;
			else fa->rchild=c;
			}
		else if(a->bf==-2 && b->bf==1)       /* RL型 */
		{
			b=a->rchild;
			c=b->lchild;
			b->lchild=c->rchild;
			a->rchild=c->lchild;
			c->lchild=a;
			c->rchild=b;
			if(s->data<c->data) 
			{ 
				a->bf=0;
				b->bf=-1;
				c->bf=0;
			}
			else if(s->data>c->data)
			{
				a->bf=1;
				b->bf=0;
				c->bf=0;
			}
			else 
			{ 
				a->bf=0;
				b->bf=0;
			}
			if (fa==NULL) *root=c;
			else if(a==fa->lchild) fa->lchild=c;
			else fa->rchild=c;
		}
		else if(a->bf==-2 && b->bf==-1)       /* RR型 */
		{
			b=a->rchild;
			a->rchild=b->lchild;
			b->lchild=a;
			a->bf=0;
			b->bf=0;
			if(fa==NULL) *root=b;
			else if(a==fa->lchild) fa->lchild=b;
			else fa->rchild=b;
		}
	}
}

//在平衡二叉树root中删去关键字为value的结点
AVLTree DeleteAVL(AVLTree root,DataType value)
{
	AVLNode *p,*f,*s,*q;
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
    //若找不到，返回原来的平衡二叉树
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

//从文件输入元素的值，创建相应的平衡二叉树
void CreateAVL(AVLTree *root,const char *filename)
{ 
	FILE *fp;
	DataType keynumber;
	*root=NULL;
	fp=fopen(filename,"r+");
	while(EOF!=fscanf(fp,"%d",&keynumber)) InsertAVL(root,keynumber);
}

//先序遍历二叉树, root为指向二叉树根结点的指针
void PreOrderCleanFlag(AVLTree root) 
{
	if(root!=NULL)
	{
		//printf("%d(%d)\t",root->data,root->bf);
		root->flag=0;
		PreOrderCleanFlag(root->lchild);
		PreOrderCleanFlag(root->rchild);
	}
}

//中序遍历二叉树, root为指向二叉树根结点的指针
void InOrder(AVLTree root) 
{
	if(root!=NULL)
	{
		InOrder(root->lchild);
        printf("%d ",root->data);
		InOrder(root->rchild);
	}
}

//后序遍历二叉树, root为指向二叉树根结点的指针
void PostOrder(AVLTree root) 
{
	if(root!=NULL)
	{
		PostOrder(root->lchild);
		PostOrder(root->rchild);
        printf("%d ",root->data);
	}
}

//层序遍历, root为指向二叉树根结点的指针
void LevelOrder(AVLTree root)
{
	//定义一个队列 
    AVLTree Queue[MaxSize];
    
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

//删除平衡二叉树, root为指向二叉树根结点的指针
void DestroyAVL(AVLTree root)
{
	if(root!=NULL)
	{
		PreOrderCleanFlag(root->lchild);
		PreOrderCleanFlag(root->rchild);
		free(root);
	}
}

//在根指针root所指平衡二叉树root上，查找关键字等于data的结点，若查找成功，返回指向该元素结点指针，否则返回空指针
AVLTree SearchAVL(AVLTree root,DataType data)
{ 
	AVLTree q;
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

//在根指针root所指平衡二叉树中交换左右子树 
void Exchange(AVLTree root)
{
    if(root==NULL) return;
    if(root->lchild==NULL && root->rchild==NULL) return;
    AVLTree temp=root->lchild;
    root->lchild=root->rchild;
    root->rchild=temp;
    Exchange(root->lchild);
    Exchange(root->rchild);
}

//在根指针root所指平衡二叉树中求树的深度 
int Depth(AVLTree root)
{
    if(root==NULL) return 0;
    return 1+max(Depth(root->lchild),Depth(root->rchild));
}

int max(int a,int b)
{
    if (a>b) return a;
    return b;
}

//在根指针root所指平衡二叉树中计算总结点个数 
int CountBiNode(AVLTree root)
{
    if(root==NULL) return 0;
    int left=CountBiNode(root->lchild);
    int right=CountBiNode(root->rchild);
    return left+right+1;
}

//根指针root所指平衡二叉树中计算叶子结点个数 
int CountLeaf(AVLTree root)
{
    if(root==NULL) return 0;
    if(root->rchild==NULL && root->lchild==NULL) return 1;
    return (CountLeaf(root->lchild)+CountLeaf(root->rchild));
}

void DotOrderList(AVLTree root,FILE *fp)
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

void DotOrderLink(AVLTree root,FILE *fp) 
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

void MakeDot(AVLTree root,char *tital=NULL)
{
	FILE *fp=fopen("avltree.gv","w+");
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
	AVLTree root;
	CreateAVL(&root,"./data.txt");
	MakeDot(root);
	PreOrderCleanFlag(root);
	system("dot.exe -Tpng avltree.gv -o avltree.png");
	
	printf("该平衡二叉树的深度为： %d\n该平衡二叉树的总结点数为： %d\n该平衡二叉树的叶子结点数为： %d\n中序遍历的结果为：\n",Depth(root),CountBiNode(root),CountLeaf(root));
	InOrder(root);
	
	SearchAVL(root,709);
	MakeDot(root);
	system("dot.exe -Tpng avltree.gv -o avltree_search(709).png");
	
	PreOrderCleanFlag(root);
	SearchAVL(root,98); 
	MakeDot(root);
	system("dot.exe -Tpng avltree.gv -o avltree_search(98).png");

	PreOrderCleanFlag(root);
	DeleteAVL(root,340);
	MakeDot(root);
	system("dot.exe -Tpng avltree.gv -o avltree_delete(340).png");
	
	DestroyAVL(root);
	return 0;
}
