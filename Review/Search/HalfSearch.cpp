#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAXSIZE 100

typedef int DataType;

//非递归实现折半查找
int HalfSearch(DataType array[],DataType n,DataType key)
{
    int low=1;
    int high=n;
    while(low<=high)
    {
        int mid=(low+high)/2;
        if(key<array[mid]) high=mid-1;
        else if(key>array[mid]) low=mid+1;
        else return mid;
    }
    return 0;
}

//递归实现实现折半查找
int BinSearch(DataType array[],DataType low,DataType high,DataType key)
{
    if(low>high) return 0;
    int mid=(low+high)/2;
    if(key<array[mid]) return BinSearch(array,low,mid-1,key);
    else if(key>array[mid]) return BinSearch(array,mid+1,high,key);
    else return mid;
}

int main()
{
    int n;
    int key1,key2;
    cout<<"请输入数组长度：";
    cin>>n;
    int a[MAXSIZE];
    cout<<"自动建立数组：";
    for(int i=1;i<=n;i++)
    {
        a[i]=10*i;
        cout<<a[i]<<" ";
    }
    cout<<endl;

    cout<<"非递归实现："<<endl;
    cout<<"请输入要查找的值：";
    cin>>key1;
    if(HalfSearch(a,n,key1)) cout<<"查命中，"<<key1<<"的下标为："<<HalfSearch(a,n,key1)<<endl;
    else cout<<"查不命中"<<endl;

    cout<<"递归实现："<<endl;
    cout<<"请输入要查找的值：";
    cin>>key2;
    if(BinSearch(a,1,n,key2)) cout<<"查命中，"<<key2<<"的下标为："<<BinSearch(a,1,n,key2)<<endl;
    else cout<<"查不命中"<<endl;

    system("pause");
    return 0;
}