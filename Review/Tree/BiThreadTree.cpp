#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

typedef char DataType;

typedef enum PointerTag
{
    Link,
    Thread
};

typedef struct node
{
    DataType data;
    struct node *lchild;
    struct node *rchild;
    PointerTag LTag;
    PointerTag RTag;
}BiThrNode, *BiThrTree;

//先序建立线索二叉树
void CreateBiThrTree(BiThrTree *root)
{
    char c;
    cin >> c;
    if (c == '#') *root=NULL;
    else
    {
        (*root) = (BiThrTree)malloc(sizeof(BiThrNode));
        (*root)->data = c;
        (*root)->LTag = Link;
        (*root)->RTag = Link;
        CreateBiThrTree(&(*root)->lchild);
        CreateBiThrTree(&(*root)->rchild);
    }
}

//二叉树的中序线索化
void InThreading(BiThrTree root, BiThrTree *pre)
{
    if (root == NULL) return;     

    InThreading(root->lchild, pre);

    if (root->lchild == NULL)
    {
        root->LTag = Thread;
        root->lchild = *pre;
    }

    if ((*pre)->rchild == NULL)
    {
        (*pre)->RTag = Thread;
        (*pre)->rchild = root;
    }

    *pre = root;
    InThreading(root->rchild, pre);
}

//增加头结点的中序线索化
void InOrderThreading(BiThrTree *root, BiThrTree T)
{
    *root = (BiThrTree)malloc(sizeof(BiThrNode));
    (*root)->LTag = Link;
    (*root)->RTag = Thread;
    (*root)->rchild = (*root);
    if (T == NULL)
    {
        (*root)->lchild = (*root);
    }
    BiThrTree pre;

    pre = (*root);
    (*root)->lchild = T;

    InThreading(T, &pre);
    pre->rchild = *root;
    pre->RTag = Thread;
    (*root)->rchild = pre;
}

//非递归遍历线索二叉树
void InOrderTraverse(BiThrTree T)
{
    BiThrNode *p = T->lchild;
    while (p != T)
    {
        while (p->LTag == Link)
            p = p->lchild;
        cout << p->data << " ";
        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            cout << p->data << " ";
        }
        p = p->rchild;
    }
    cout << endl;
}

//测试序列：ABD##E##CF###
int main()
{
    BiThrTree root, T;
    CreateBiThrTree(&root);
    InOrderThreading(&T, root);
    cout << "中序遍历二叉树的结果为：";
    InOrderTraverse(T);

    system("pause");
    return 0;
}