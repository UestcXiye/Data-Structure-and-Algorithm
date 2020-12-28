#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define MAXSIZE 100

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

void List_build(ListPtr L)
{
    int n;
    cout<<"Input the length:";
    cin>>n;
    L->length=n;
    cout<<"Input the elem:";
    for(int i=0;i<n;i++) cin>>L->elem[i];
}

void List_Traverse(ListPtr L)
{
    for(int i=0;i<L->length;i++) cout<<L->elem[i]<<" ";
    cout<<endl;
}

void Union(ListPtr a,ListPtr b,ListPtr c)
{
    int alen=a->length,blen=b->length;
    int k=alen;

    for(int i=0;i<alen;i++) c->elem[i]=a->elem[i];
    for(int i=0;i<blen;i++)
    {
        int j;
        for(j=0;j<alen;j++)
        {
            if(a->elem[j]==b->elem[i]) break;
        }
        if(j>=alen)
        {
            c->elem[k]=b->elem[i];
            k++;
        }
    }
    c->length=k;
}

int main()
{
    Sqlist A,B,C;
    List_Init(&A);
    List_Init(&B);
    List_Init(&C);
    List_build(&A);
    List_build(&B);

    Union(&A,&B,&C);

    cout<<"A:";
    List_Traverse(&A);
    cout<<"B:";
    List_Traverse(&B);
    cout<<"C=A¡ÈB:";
    List_Traverse(&C);
    
    system("pause");
    return 0;
}