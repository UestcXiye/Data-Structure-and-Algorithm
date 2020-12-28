#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef struct Sqlist
{
    int *elem;
    int length;
}Sqlist,*ListPtr;

void List_Init(ListPtr L)
{
    L->elem=(int*)malloc((MAXSIZE+1)*sizeof(int));
    if(L->elem) L->length=0;
}

void List_Destroy(ListPtr L)
{
    if(L->elem)
    {
        free(L->elem);
        L->elem=NULL;
    }
    L->length=0;
}

void List_Clear(ListPtr L)
{
    L->length=0;
}

bool List_Empty(ListPtr L)
{
    return L->length==0;
}

int List_Insert(ListPtr L,int pos,int elem)
{
    if(L->length>MAXSIZE) return ERROR;
    if(pos>=1 && pos<=1+L->length)
    {
        for(int i=L->length;i>=pos;i--) L->elem[i+1]=L->elem[i];
        L->elem[pos]=elem;
        L->length++;
        return OK;
    }
}

int List_Delete(ListPtr L,int pos)
{
    if(pos>=1 && pos<=L->length)
    {
        for(int i=pos;i<L->length;i++) L->elem[i]=L->elem[i+1];
        L->length--;
        return OK;
    }
    return ERROR;
}

int List_Locate(ListPtr L,int pos)
{
    if(1<=pos && pos<=L->length) return L->elem[pos];
    return -1;
}

int List_Search(ListPtr L,int value)
{
    int i=0;
    while(i<=L->length && L->elem[i]!=value) i++;
    if(i<=L->length) return i;
    return -1;
}

int List_Prior(ListPtr L,int pos)
{
    if(2<=pos && pos<=L->length) return L->elem[pos-1];
    return -1;
}

int List_Next(ListPtr L,int pos)
{
    if(1<=pos && pos<L->length) return L->elem[pos+1];
    return -1;
}

void List_Traverse(ListPtr L)
{
    for(int i=1;i<=L->length;i++) printf("%d ",L->elem[i]);
    printf("\n");
}

void List_Reverse(ListPtr L)
{
    for(int i=1;i<L->length/2;i++)
    {
        int temp=L->elem[i];
        L->elem[i]=L->elem[L->length-i+1];
        L->elem[L->length-i+1]=temp;
    }
}

int main()
{
    Sqlist L;
    List_Init(&L);
    List_Insert(&L,1,1);
    List_Insert(&L,2,2);
    List_Insert(&L,3,3);
    List_Traverse(&L);
    printf("%d\n",List_Search(&L,3));
    List_Destroy(&L);
    system("pause");
    return 0;
}