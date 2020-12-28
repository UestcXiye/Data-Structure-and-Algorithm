#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define KEY 11
#define ARRAY_SIZE 9
#define HASH_SIZE 13

void BuildHash(int array[],int hash[],int SearchLength[])
{
    for(int i=0;i<ARRAY_SIZE;i++)
    {
        int x=array[i]%KEY;
        if(hash[x] == -1)
        {
            hash[x]=array[i];
            SearchLength[x]=1;
        }
        else
        {
            int k=1;
            while(x<HASH_SIZE && hash[x] != -1)
            {
                x++;
                k++;
            }
            if(x<HASH_SIZE  && hash[x] == -1)
            {
                hash[x]=array[i];
                SearchLength[x]=k;
            }
            
        }
    }
}

int main()
{
    int array[ARRAY_SIZE]={16,28,41,22,37,79,30,19,38};
    int hash[HASH_SIZE];
    int SearchLength[HASH_SIZE];
    float ASL=0.0;

    memset(hash,-1,sizeof(hash));
    memset(SearchLength,0,sizeof(SearchLength));
    
    cout<<"线性表为：";
    for(int i=0;i<ARRAY_SIZE;i++) cout<<array[i]<<" ";
    cout<<endl;
    
    BuildHash(array,hash,SearchLength);

    cout<<"散列表为：";
    for(int i=0;i<HASH_SIZE;i++) cout<<hash[i]<<" ";
    cout<<endl;

    cout<<"查找长度为：";
    for(int i=0;i<HASH_SIZE;i++)
    {
        cout<<SearchLength[i]<<" ";
        ASL+=SearchLength[i];
    }
    cout<<endl;
    cout<<"平均查找长度（ASL）为："<<ASL/ARRAY_SIZE<<endl;

    system("pause");
    return 0;
}