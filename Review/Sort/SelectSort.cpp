#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define ARRAY_LENGTH 12

void SelectSort(int a[],int n)
{
  for(int i=1;i<=n-1;i++)
  {
    int k=i;
    for(int j=i+1;j<=n;j++) 
    {
        if(a[j]<a[k]) k=j;
    }
    if(k!=i) 
    { 
      int temp=a[i]; 
      a[i]=a[k];
      a[k]=temp;
    }
    cout<<"第"<<i<<"趟简单选择排序：";
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

    SelectSort(array,ARRAY_LENGTH);

    cout<<endl<<"最终结果：";
    for(int i=1;i<=ARRAY_LENGTH;i++) cout<<array[i]<<" ";
    cout<<endl;
    
    system("pause");
    return 0;
}