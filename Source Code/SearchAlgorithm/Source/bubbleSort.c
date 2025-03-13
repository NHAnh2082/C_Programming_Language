#include <stdio.h>
#include "..\\Header\\bubbleSort.h"

static void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int *arr, int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }

    printf("Mang sau khi sap xep\n");
    for (int i=0; i<n; i++){
        printf("%d\t", arr[i]);
    }

    printf("\n");
}