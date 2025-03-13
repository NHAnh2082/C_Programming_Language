#include <stdio.h>
#include <stdlib.h>
#include "..\\Header\\random.h"
#include "..\\Header\\bubbleSort.h"
#include "..\\Header\\binarySearch.h"

#define SIZE 20000

int main()
{
    int arr[SIZE], x;
    generateRandom(arr, SIZE);
    
    bubbleSort(arr, SIZE);

    printf("Nhập giá trị cần tìm: ");
    scanf("%d", &x);

    int result = binarySearch(arr, 0, SIZE - 1, x);
    if (result == -1){
        printf("Khong tim thay %d trong mang.\n", x);
    } 
    else{
        printf("Tim thay %d tai vi tri %d trong mang.\n", x, result);
    }

    return 0;
}
