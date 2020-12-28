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

//递归实现交换左右子树
void ReChange(BiTree root)
{
    if(root==NULL) return;
    else
    {
        BiTree temp=root->lchild;
        root->lchild=root->rchild;
        root->rchild=temp;
        ReChange(root->lchild);
        ReChange(root->rchild);
    }
}

//非递归实现交换左右子树
void Change(BiTree root)
{
    BiTree Queue[MAXSIZE];
    int front=-1;
    int rear=0;
    Queue[rear]=root;
    while(rear!=front)
    {
        BiTree p=Queue[++front];
        BiTree temp=p->lchild;
        p->lchild=p->rchild;
        p->rchild=temp;
        if(p->lchild) Queue[++rear]=p->lchild;
        if(p->rchild) Queue[++rear]=p->rchild;
    }
}

//测试序列：ABDG###E##CF#H###
int main()
{
    BiTree root;
    CreateBiTree(root);

    PreOrder(root);
    cout<<endl;

    ReChange(root);

    PreOrder(root);
    cout<<endl;

    Change(root);

    PreOrder(root);
    cout<<endl;

    system("pause");
    return 0;
}