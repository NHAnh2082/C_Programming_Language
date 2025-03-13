/******************************************************************************
 * @file     : stack.h
 * @brief    : Triển khai cấu trúc dữ liệu Stack (ngăn xếp)
 * @details  : Cung cấp các hàm để khởi tạo, thêm/xóa phần tử, 
 *             kiểm tra trạng thái Stack
 * @author   : Anh Nguyen
 * @date     : 2025-01-04
 * @version  : 1.0
 ******************************************************************************/

#ifndef STACK_H
#define STACK_H

/* =========================== [INCLUDE FILES] ============================= */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* =========================== [MACRO DEFINITIONS] ========================= */
#define STACK_EMPTY -1  /**< Giá trị trả về khi stack rỗng */


/* =========================== [TYPE DEFINITIONS] ========================== */
/**
 * @brief Cấu trúc dữ liệu của Stack
 */
typedef struct 
{
    int *item;  /**< Mảng lưu trữ giá trị các phần tử */ 
    int size;   /**< Số lượng phần tử tối đa          */ 
    int top;    /**< Chỉ số lấy giá trị ở đỉnh Stack  */
} Stack;


/**
 * @brief   Khởi tạo Stack với kích thước xác định.
 * @param   stack   Con trỏ tới Stack cần khởi tạo.
 * @param   newSize Kích thước tối đa của Stack.
 * @return  void
 */
void stack_init(Stack *stack, int newSize);


/**
 * @brief   Kiểm tra Stack có rỗng không.
 * @param   stack   Stack cần kiểm tra.
 * @return  true nếu Stack rỗng, false nếu Stack có phần tử.
 */
bool isEmpty(Stack stack);


/**
 * @brief   Kiểm tra Stack có đầy không.
 * @param   stack   Stack cần kiểm tra.
 * @return  true nếu Stack đầy, false nếu còn chỗ trống.
 */
bool isFull(Stack stack);


/**
 * @brief   Thêm phần tử vào đỉnh Stack.
 * @param   stack   Con trỏ tới Stack.
 * @param   data    Dữ liệu cần thêm.
 * @return  void
 */
void push(Stack *stack, int data);


/**
 * @brief   Lấy phần tử ở đỉnh Stack và xóa khỏi Stack.
 * @param   stack   Con trỏ tới Stack.
 * @return  Giá trị phần tử trên cùng hoặc STACK_EMPTY nếu Stack rỗng.
 */
int pop(Stack *stack);


/**
 * @brief   Đọc giá trị tại đỉnh Stack mà không xóa.
 * @param   stack   Stack cần đọc giá trị.
 * @return  Giá trị phần tử trên cùng hoặc STACK_EMPTY nếu Stack rỗng.
 */
int top(Stack stack);


/**
 * @brief   Giải phóng bộ nhớ của Stack.
 * @param   stack   Con trỏ tới Stack.
 * @return  void
 */
void stack_free(Stack *stack);

#endif  // STACK_H