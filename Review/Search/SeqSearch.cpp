#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef int DataType;

#define MAXSIZE 100

typedef struct seq
{
    DataType key;
}Seq;

int SeqSearch(Seq array[],int n,DataType key)
{
    int i=n;
    array[0].key=key;
    while(array[i].key!=key) i--;
    return i;
}

int main()
{
    int n;
    int key;
    Seq q[MAXSIZE];
    cout<<"请输入数组长度：";
    cin>>n;
    cout<<"请输入数据：";
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        q[i].key=x;
    }
    cout<<"请输入要查找的值：";
    cin>>key;
    if(SeqSearch(q,n,key)) cout<<"查命中，"<<key<<"的下标为："<<SeqSearch(q,n,key)<<endl;
    else cout<<"查不命中"<<endl;
    
    system("pause");
    return 0;
}