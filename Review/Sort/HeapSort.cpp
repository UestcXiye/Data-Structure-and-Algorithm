#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define ARRAY_LENGTH 12

void max_heapify(int a[], int start, int end)
{
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end)
    {
        if (son + 1 <= end && a[son] < a[son + 1])
            son++;
        if (a[dad] > a[son])
            return;
        else
        {
            swap(a[dad], a[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void HeapSort(int a[], int len)
{
    for (int i = len / 2 - 1; i >= 0; i--)
        max_heapify(a, i, len - 1);
    for (int i = len - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        max_heapify(a, 0, i - 1);
    }
}

int main()
{
    int array[ARRAY_LENGTH] = {23, 15, 12, 35, 46, 19, 20, 14, 8, 74, 86, 25};

    cout << "原序列：";
    for (int i = 0; i < ARRAY_LENGTH; i++)
        cout << array[i] << " ";
    cout << endl
         << endl;

    HeapSort(array, ARRAY_LENGTH);

    cout << endl
         << "最终结果：";
    for (int i = 0; i < ARRAY_LENGTH; i++)
        cout << array[i] << " ";
    cout << endl;

    system("pause");
    return 0;
}