/*
* File: binarySearch.h
* Author: Anh Nguyen
* Date: 20/07/2024
* Description: This is a header file consist of declare functions and variables for binary search
*/
#ifndef _BINARYSEARCH_H
#define _BINARYSEARCH_H

/*
* Function: binarySearch
* Description: This function will perform binary search
* Input:
*   *arr: an array that stores the values ​​of its elements
*   l: index of the first element in the current array
*   r: index of the last element in the current array
*   x: number need to find in array
* Output:
*   return index of the number to search in the array
*/
int binarySearch(int* arr, int l, int r, int x);

#endif

// Cmake