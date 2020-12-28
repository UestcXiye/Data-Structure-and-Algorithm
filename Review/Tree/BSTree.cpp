#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

typedef int DataType;

typedef struct node
{
    DataType data;
    struct node *lchild;
    struct node *rchild;
} BSTNode, *BSTree;

//在排序二叉树查找key值
BSTree SearchBST(BSTree root, DataType key)
{
    if (root == NULL)
        return NULL;
    if (key > root->data)
        return SearchBST(root->rchild, key);
    else if (key < root->data)
        return SearchBST(root->lchild, key);
    else
        return root;
}

//向排序二叉树插值
void InsertBST(BSTree *root, DataType data)
{
    BSTree p = (BSTree)malloc(sizeof(BSTNode));
    if (!p)
        return;
    p->data = data;
    p->lchild = p->rchild = NULL;
    if (*root == NULL)
    {
        *root = p;
        return;
    }
    if (SearchBST(*root, data) != NULL)
        return;
    BSTree tnode = NULL, q = *root;
    while (q)
    {
        tnode = q;
        q = (data < q->data) ? q->lchild : q->rchild;
    }
    if (data < tnode->data)
        tnode->lchild = p;
    else
        tnode->rchild = p;
}

//创建一个排序二叉树，实际上就是不断插入的过程
void CreateBST(BSTree *T, int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        InsertBST(T, array[i]);
    }
}

//删除排序二叉树上值为key的结点
void DeleteBST(BSTree *root, DataType key)
{
    BSTree p = *root, parent = NULL, s = NULL;

    if (!p)
        return;

    if (p->data == key)
    {
        if (!p->rchild && !p->lchild)
            *root = NULL;

        else if (!p->rchild && p->lchild)
            *root = p->lchild;

        else if (!p->lchild && p->rchild)
            *root = p->rchild;

        else
        {
            s = p->rchild;
            if (!s->lchild)
                s->lchild = p->lchild;
            else
            {
                while (s->lchild)
                {
                    parent = s;
                    s = s->lchild;
                }
                parent->lchild = s->rchild;
                s->lchild = p->lchild;
                s->rchild = p->rchild;
            }
            *root = s;
        }
        free(p);
    }
    else if (key > p->data)
        DeleteBST(&(p->rchild), key);
    else if (key < p->data)
        DeleteBST(&(p->lchild), key);
}

void PreOrder(BSTree T)
{
    if (T)
    {
        cout << T->data << " ";
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BSTree root)
{
    if (root != NULL)
    {
        InOrder(root->lchild);
        cout << root->data << " ";
        InOrder(root->rchild);
    }
}

void PostOrder(BSTree root)
{
    if (root)
    {
        PostOrder(root->lchild);
        PostOrder(root->rchild);
        cout << root->data << " ";
    }
}

int main()
{
    int arr[] = {27, 12, 19, 10, 15, 30, 25, 8, 41, 33, 16, 22};

    BSTree root = NULL;

    CreateBST(&root, arr, 12);
    cout << "创建排序二叉树:";
    for (int i = 0; i < 12; i++)
        cout << arr[i] << " ";
    cout << endl
         << endl;
    cout << "先序遍历: ";
    PreOrder(root);
    cout << endl;
    cout << "中序遍历: ";
    InOrder(root);
    cout << endl;
    cout << "后序遍历: ";
    PostOrder(root);
    cout << endl
         << endl;

    BSTree result = SearchBST(root, 12);
    cout << "查值: 12" << endl
         << endl;
    cout << "查找结果：" << endl
         << "指针：" << result << endl
         << "指针的值：" << result->data << endl;

    InsertBST(&root, 9);
    cout << endl;
    cout << "插入: 9" << endl
         << endl;
    cout << "先序遍历:";
    PreOrder(root);
    cout << endl;
    cout << "中序遍历: ";
    InOrder(root);
    cout << endl;
    cout << "后序遍历: ";
    PostOrder(root);
    cout << endl;

    DeleteBST(&root, 12);
    cout << endl;
    cout << "删除: 12" << endl
         << endl;
    cout << "先序遍历:";
    PreOrder(root);
    cout << endl;
    cout << "中序遍历: ";
    InOrder(root);
    cout << endl;
    cout << "后序遍历: ";
    PostOrder(root);
    cout << endl;

    system("pause");
    return 0;
}