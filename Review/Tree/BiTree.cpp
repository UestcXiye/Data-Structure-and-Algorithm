#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

typedef char DataType;

#define MAXSIZE 100

typedef struct node
{
    DataType data;
    struct node *lchild;
    struct node *rchild;
}BiTreeNode,*BiTree;

//先序建立二叉树
void CreateBiTree(BiTree &root)
{
    char c;
    cin>>c;
    if(c=='#')
    {
        root=NULL;
    }
    else
    {
        root=(BiTree)malloc(sizeof(BiTreeNode));
        root->data=c;
        CreateBiTree(root->lchild);
        CreateBiTree(root->rchild);
    }
}

//递归实现先序遍历
void PreOrder(BiTree root)
{
    if(root!=NULL)
    {
        cout<<root->data<<" ";
        PreOrder(root->lchild);
        PreOrder(root->rchild);
    }
}

//递归实现中序遍历
void InOrder(BiTree root)
{
    if(root!=NULL)
    {
        InOrder(root->lchild);
        cout<<root->data<<" ";
        InOrder(root->rchild);
    }
}

//递归实现后序遍历
void PostOrder(BiTree root)
{
    if(root!=NULL)
    {
        PostOrder(root->lchild);
        PostOrder(root->rchild);
        cout<<root->data<<" ";
    }
}

//非递归实现先序遍历
void NonPreOrder(BiTree root)
{
    BiTree S[MAXSIZE];
    BiTree p;
    int top=-1;
    S[++top]=root;
    while(top!=-1)
    {
        p=S[top--];
        cout<<p->data<<" ";
        if(p->rchild!=NULL) S[++top]=p->rchild;
        if(p->lchild!=NULL) S[++top]=p->lchild;
    }
}

//非递归实现中序遍历
void NonInOrder(BiTree root)
{
    BiTree S[MAXSIZE];
    BiTree p=root;
    int top=-1;
    while(top!=-1 || p!=NULL)
    {
        while(p!=NULL)
        {
            S[++top]=p;
            p=p->lchild;
        }
        if(top!=-1)
        {
            p=S[top--];
            cout<<p->data<<" ";
            p=p->rchild;
        }
    }
}

//队列实现层次遍历
void LevelOrder(BiTree root)
{
    BiTree Queue[MAXSIZE];
    int front=-1;
    int rear=0;
    Queue[rear]=root;
    while(rear!=front)
    {
        cout<<Queue[++front]->data<<" ";
        if(Queue[front]->lchild) Queue[++rear]=Queue[front]->lchild;
        if(Queue[front]->rchild) Queue[++rear]=Queue[front]->rchild;
    }
}

//求二叉树的深度
int Depth(BiTree root)
{
    if(root==NULL) return 0;
    return max(Depth(root->lchild),Depth(root->rchild))+1;
}

int max(int a,int b)
{
    if(a>b) return a;
    else return b;
}

//求叶子结点的数量
int LeafCount(BiTree root)
{
    if(root==NULL) return 0;
    if(root->lchild==NULL && root->rchild==NULL) return 1;
    return LeafCount(root->lchild)+LeafCount(root->rchild);
}

//求度为1的结点的数量
int DegreeOneCount(BiTree root)
{
    if(root==NULL) return 0;
    if((root->lchild!=NULL && root->rchild==NULL) || (root->lchild==NULL && root->rchild!=NULL))
        return DegreeOneCount(root->lchild)+DegreeOneCount(root->rchild)+1;
    return DegreeOneCount(root->lchild)+DegreeOneCount(root->rchild);
}

//求度为2的结点的数量
int DegreeTwoCount(BiTree root)
{
    if(root==NULL) return 0;
    if(root->lchild!=NULL && root->rchild!=NULL)
        return DegreeTwoCount(root->lchild)+DegreeTwoCount(root->rchild)+1;
    return DegreeTwoCount(root->lchild)+DegreeTwoCount(root->rchild);
}

//测试序列：ABD##E##CF###
int main()
{
    BiTree root;
    CreateBiTree(root);

    cout<<"二叉树的深度: "<<Depth(root)<<endl;
    cout<<"二叉树的叶子结点数: "<<LeafCount(root)<<endl;
    cout<<"度为1的结点数: "<<DegreeOneCount(root)<<endl;
    cout<<"度为2的结点数: "<<DegreeTwoCount(root)<<endl;

    cout<<"递归先序遍历: ";
    PreOrder(root);
    cout<<endl;
    cout<<"非递归先序遍历: ";
    NonPreOrder(root);
    cout<<endl;

    cout<<"递归中序遍历: ";
    InOrder(root);
    cout<<endl;
    cout<<"非递归中序遍历: ";
    NonInOrder(root);
    cout<<endl;

    cout<<"递归后序遍历: ";
    PostOrder(root);
    cout<<endl;

    cout<<"层次遍历: ";
    LevelOrder(root);
    cout<<endl;

    system("pause");
    return 0;
}