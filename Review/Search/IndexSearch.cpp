#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX 16

typedef int DataType;

typedef struct elem
{
    DataType key; //关键字
} Seq;

//索引结构
struct index
{
    DataType key; //索引值
    long low;     //起始位置
    long high;    //终止位置
};

int IndexSearch(elem e[], DataType key, int n, index idx[], int idx_length)
{
    int k = 0;
    //采用顺序查找的方法在索引表里找到关键字所在的块
    while (k <= idx_length && key > idx[k].key)
        k++;
    if (k > idx_length)
        return -1;
    else
    {
        //采用顺序查找的方法从块中查找关键值
        int i = idx[k].low;

        while (i <= idx[k].high && e[i].key != key)
        {
            i++;
        }

        if (i > idx[k].high)
            return -1;
        else
            return i;
    }
}

int main()
{
    Seq linelist[MAX] = {
        8, 20, 13, 17,
        40, 42, 45, 32,
        49, 58, 50, 52,
        67, 79, 78, 80};

    int n = sizeof(linelist) / sizeof(elem);
    DataType key;

    //建立索引表
    index index_table[4] = {{20, 0, 3}, {45, 4, 7}, {58, 8, 11}, {80, 12, 15}};
    int idx_length = sizeof(index_table) / sizeof(index);

    printf("索引表中的元素为：\n");
    for (int i = 0; i < n; i++)
    {
        cout << linelist[i].key << " ";
    }
    cout << endl
         << endl;
    cout << "请输入要查找的值：";
    cin >> key;

    if (IndexSearch(linelist, key, n, index_table, idx_length) != -1)
    {
        printf("\n查命中，关键字%d在线性表中的位置下标为%d\n\n", key, IndexSearch(linelist, key, n, index_table, idx_length));
    }
    else
        cout << "查不命中" << endl;

    system("pause");
    return 0;
}