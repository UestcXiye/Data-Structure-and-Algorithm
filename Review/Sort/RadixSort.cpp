#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define ARRAY_LENGTH 12

int maxbit(int a[], int n) //辅助函数，求数据的最大位数
{
    int maxData = a[0]; ///< 最大数
    /// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
    for (int i = 1; i < n; ++i)
    {
        if (maxData < a[i])
            maxData = a[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        //p *= 10; // Maybe overflow
        maxData /= 10;
        ++d;
    }
    return d;
    /*    int d = 1; //保存最大的位数
    int p = 10;
    for(int i = 0; i < n; ++i)
    {
        while(data[i] >= p)
        {
            p *= 10;
            ++d;
        }
    }
    return d;*/
}

void RadixSort(int a[], int n) //基数排序
{
    int d = maxbit(a, n);
    int *tmp = new int[n];
    int *count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++) //进行d次排序
    {
        for (j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for (j = 0; j < n; j++)
        {
            k = (a[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for (j = n - 1; j >= 0; j--)            //将所有桶中记录依次收集到tmp中
        {
            k = (a[j] / radix) % 10;
            tmp[count[k] - 1] = a[j];
            count[k]--;
        }
        for (j = 0; j < n; j++) //将临时数组的内容复制到data中
            a[j] = tmp[j];
        radix = radix * 10;
    }
    delete[] tmp;
    delete[] count;
}

int main()
{
    int array[ARRAY_LENGTH] = {23, 15, 12, 35, 46, 19, 20, 14, 8, 74, 86, 25};

    cout << "原序列：";
    for (int i = 0; i < ARRAY_LENGTH; i++)
        cout << array[i] << " ";
    cout << endl
         << endl;

    RadixSort(array, ARRAY_LENGTH);

    cout << endl
         << "最终结果：";
    for (int i = 0; i < ARRAY_LENGTH; i++)
        printf("%d ", array[i]);
    cout << endl;
    system("pause");
    return 0;
}