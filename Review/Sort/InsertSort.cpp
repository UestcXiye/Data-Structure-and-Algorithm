#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define ARRAY_LENGTH 12

void InsertSort(int a[],int n)
{
    for(int i=2;i<=n;i++)
    {
        int j;
        a[0]=a[i];
        for(j=i-1;a[0]<a[j];j--) a[j+1]=a[j];
        a[j+1]=a[0];
    }
}

int main()
{
    int array[ARRAY_LENGTH+1]={-1,8,14,12,19,15,23,20,46,25,74,86,35};

    cout<<"原序列：";
    for(int i=1;i<=ARRAY_LENGTH;i++) cout<<array[i]<<" ";
    cout<<endl;

    InsertSort(array,ARRAY_LENGTH);

    cout<<"直接插入排序：";
    for(int i=1;i<=ARRAY_LENGTH;i++) cout<<array[i]<<" ";
    cout<<endl;
    
    system("pause");
    return 0;
}