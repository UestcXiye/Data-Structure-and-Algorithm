#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define ARRAY_LENGTH 12

//合并过程中 p<=q<r
void Merge(int array[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    int *L;
    L = (int *)malloc(sizeof(int) * n1);
    int *R;
    R = (int *)malloc(sizeof(int) * n2);

    int i = 0;
    int j = 0;

    for (i; i < n1; i++)
        L[i] = array[i + p];
    for (j; j < n2; j++)
        R[j] = array[j + q + 1];

    i = j = 0;

    int k = p;

    while (i != n1 && j != n2)
    {
        if (L[i] <= R[j])
            array[k++] = L[i++];
        else
            array[k++] = R[j++];
    }

    while (i < n1)
        array[k++] = L[i++];
    while (j < n2)
        array[k++] = R[j++];

    free(L);
    free(R);
}

void MergeSort(int array[], int p, int q)
{
    if (p < q)
    {
        int r = (p + q) / 2;
        MergeSort(array, p, r);
        MergeSort(array, r + 1, q);
        Merge(array, p, r, q);
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

    MergeSort(array, 0, ARRAY_LENGTH - 1);

    cout << endl
         << "最终结果：";
    for (int i = 0; i < ARRAY_LENGTH; i++)
        printf("%d ", array[i]);
    cout << endl;
    system("pause");
    return 0;
}