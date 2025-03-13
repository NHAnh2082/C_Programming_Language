#include <stdio.h>
#include <time.h>
#include "..\\Header\\random.h"

void generateRandom(int *arr, int size) 
{
    // Khởi tạo bộ sinh số ngẫu nhiên
    srand(time(NULL));

    // Sinh ngẫu nhiên các phần tử cho mảng
    for (int i=0; i<size; i++) {
        arr[i] = rand() % 10000;  // sinh số ngẫu nhiên
    }

    for (int i=0; i<size; i++){
        printf("%d\t", arr[i]);
    }

    printf("\n");
}