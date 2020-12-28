#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define ARRAY_LENGTH 12

int QuickPass(int a[],int left,int right)
{
    int i=left;
    int j=right;
    int x=a[left];
    while(i<j)
    {
        while(i<j && a[j]>=x) j--;
        if(i<j)
        {
            a[i]=a[j];
            i++;
        }
        while(i<j && a[i]<x) i++;
        if(i<j)
        {
            a[j]=a[i];
            j--;
        }
    }
    a[i]=x;
    return i;
}

void QuickSort(int a[],int low,int high)
{
  if(low<high)
  {
    int pos=QuickPass(a,low,high);
    QuickSort(a,low,pos-1);
    QuickSort(a,pos+1,high);
  }
}


int main()
{
    int array[ARRAY_LENGTH+1]={-1,23,15,12,35,46,19,20,14,8,74,86,25};

    cout<<"原序列：";
    for(int i=1;i<=ARRAY_LENGTH;i++) cout<<array[i]<<" ";
    cout<<endl<<endl;

    QuickSort(array,1,ARRAY_LENGTH);

    cout<<endl<<"最终结果：";
    for(int i=1;i<=ARRAY_LENGTH;i++) cout<<array[i]<<" ";
    cout<<endl;

    system("pause");
    return 0;
}