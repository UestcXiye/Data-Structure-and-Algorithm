#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define ARRAY_LENGTH 12
#define D_LENGTH 3

void ShellSort(int a[],int n,int d[],int t)
{
    for(int k=0;k<t;k++)
    {
        int dk=d[k];
        for(int m=1;m<=n;m++)
        {
            for(int i=m+dk;i<=n;i+=dk)
            {
                int j;
                a[0]=a[i];
                for(j=i-dk;j>=0 && a[0]<a[j];j-=dk) a[j+dk]=a[j];
                a[j+dk]=a[0];
            }
        }
        cout<<"增量d="<<dk<<endl;
        for(int i=1;i<=ARRAY_LENGTH;i++) cout<<a[i]<<" ";
        cout<<endl;
    }
}

int main()
{
    int array[ARRAY_LENGTH+1]={-1,23,15,12,35,46,19,20,14,8,74,86,25};
    int d[D_LENGTH]={5,3,1};

    cout<<"原序列：";
    for(int i=1;i<=ARRAY_LENGTH;i++) cout<<array[i]<<" ";
    cout<<endl<<endl;

    ShellSort(array,ARRAY_LENGTH,d,D_LENGTH);
    
    system("pause");
    return 0;
}