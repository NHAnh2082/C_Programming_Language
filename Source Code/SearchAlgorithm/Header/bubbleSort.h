/*
* File: bubbleSort.h
* Author: Anh Nguyen
* Date: 20/07/2024
* Description: This is a header file consist of declare functions and variables for bubble sort
*/
#ifndef _BUBBLESORT_H
#define _BUBBLESORT_H

/*
* Function: swap
* Description: This function swap two integers
* Input:
*   *a: an integer pointer stores the address of variable a
*   *b: an integer pointer stores the address of variable b
* Output:
*   return none
*/
static void swap(int *a, int *b);

/*
* Function: bubbleSort
* Description: This function will sort the elements in the array from smallest to largest
* Input:
*   *arr: an array that stores the values ​​of its elements
*   n: size of array
* Output:
*   return none
*/
void bubbleSort(int *arr, int n);

#endif