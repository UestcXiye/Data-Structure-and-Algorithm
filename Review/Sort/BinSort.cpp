#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define ARRAY_LENGTH 12

void BinSort(int a[],int n)
{
    for(int i=2;i<=n;i++)
    {
        a[0]=a[i];
        int low=1;
        int high=i-1;
        while(low<=high)
        {
            int mid=(low+high)/2;
            if(a[0]<a[mid]) high=mid-1;
            else low=mid+1;
        }
        //high+1???????
        for(int j=i-1;j>=high+1;j--) a[j+1]=a[j];
        a[high+1]=a[0];
    }
}

int main()
{
    int array[ARRAY_LENGTH+1]={-1,8,14,12,19,15,23,20,46,25,74,86,35};

    cout<<"Ô­ÐòÁÐ£º";
    for(int i=1;i<=ARRAY_LENGTH;i++) cout<<array[i]<<" ";
    cout<<endl;

    BinSort(array,ARRAY_LENGTH);

    cout<<"ÕÛ°ë²åÈëÅÅÐò£º";
    for(int i=1;i<=ARRAY_LENGTH;i++) cout<<array[i]<<" ";
    cout<<endl;
    
    system("pause");
    return 0;
}