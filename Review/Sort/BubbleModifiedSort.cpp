#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define ARRAY_LENGTH 12

void BubbleModifiedSort(int a[],int n)
{
    int i=n;
    int count=0;
    while(i>1)
    {
        int LastExchangeIndex=1;
        for(int j=1;j<i;j++)
        {
            if(a[j]>a[j+1])
            {
                int temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
                LastExchangeIndex=j;
            }
        }
        i=LastExchangeIndex;
        cout<<"第"<<++count<<"趟改进后的冒泡排序：";
        for(int k=1;k<=ARRAY_LENGTH;k++) cout<<a[k]<<" ";
        cout<<endl;
    }
}

int main()
{
    int array[ARRAY_LENGTH+1]={-1,23,15,12,35,46,19,20,14,8,74,86,25};

    cout<<"原序列：";
    for(int i=1;i<=ARRAY_LENGTH;i++) cout<<array[i]<<" ";
    cout<<endl<<endl;

    BubbleModifiedSort(array,ARRAY_LENGTH);

    cout<<endl<<"最终结果：";
    for(int i=1;i<=ARRAY_LENGTH;i++) cout<<array[i]<<" ";
    cout<<endl;

    system("pause");
    return 0;
}