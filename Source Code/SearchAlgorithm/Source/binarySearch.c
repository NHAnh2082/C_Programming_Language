#include <stdio.h>
#include "..\\Header\\binarySearch.h"

#define NO_FOUND -1     

int binarySearch(int* arr, int l, int r, int x)
{
    if (r >= l)
    {
        int mid = (r + l) / 2;

        if (arr[mid] == x){
            return mid;
        }
        else if (arr[mid] > x){
            return binarySearch(arr, l, mid - 1, x);
        }
        else{
            return binarySearch(arr, mid + 1, r, x);
        }
    }
    return NO_FOUND;
}