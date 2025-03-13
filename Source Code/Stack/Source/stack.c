/******************************************************************************
 * @file     : stack.c
 * @brief    : Định nghĩa các hàm cho cấu trúc dữ liệu Stack
 * @details  : Định nghĩa các hàm để khởi tạo, thêm/xóa phần tử, 
 *             kiểm tra trạng thái Stack
 * @author   : Anh Nguyen
 * @date     : 2025-01-04
 * @version  : 1.0
 ******************************************************************************/

/* =========================== [INCLUDE FILES] ============================= */

#include "..\\Header\\stack.h"


/* =========================== [FUNCTION IMPLEMENTATION] =================== */

/**
 * @brief   Khởi tạo Stack với kích thước xác định.
 * @param   stack   Con trỏ tới Stack cần khởi tạo.
 * @param   newSize Kích thước tối đa của Stack.
 */
void stack_init(Stack *stack, int newSize)
{
    stack->size = newSize;
    stack->item = (int*)malloc(newSize * sizeof(int));
    stack->top  = -1;
}


/**
 * @brief   Kiểm tra Stack có rỗng không.
 * @param   stack   Stack cần kiểm tra.
 * @return  true nếu Stack rỗng, false nếu Stack có phần tử.
 */
bool isEmpty(Stack stack)
{
    return (stack.top == -1 ? true : false);
}


/**
 * @brief   Kiểm tra Stack có đầy không.
 * @param   stack   Stack cần kiểm tra.
 * @return  true nếu Stack đầy, false nếu còn chỗ trống.
 */
bool isFull(Stack stack)
{
    return (stack.top == (stack.size - 1) ? true : false);
}


/**
 * @brief   Thêm phần tử vào đỉnh Stack.
 * @param   stack   Con trỏ tới Stack.
 * @param   data    Dữ liệu cần thêm.
 */
void push(Stack *stack, int data)
{
    if (isFull(*stack))
    {
        printf("Stack đầy! Không thể thêm\n");
    }
    else
    {
        // stack->top++;
        // stack->item[stack->top] = data;

        stack->item[++stack->top] = data;
    }
}


/**
 * @brief   Lấy phần tử ở đỉnh Stack và xóa khỏi Stack.
 * @param   stack   Con trỏ tới Stack.
 * @return  Giá trị phần tử trên cùng hoặc STACK_EMPTY nếu Stack rỗng.
 */
int pop(Stack *stack)
{
    if (isEmpty(*stack))
    {
        printf("Stack rỗng!\n");
        return STACK_EMPTY;
    }
    else
    {
        int val = stack->item[stack->top];
        stack->item[stack->top--] = 0;
        return val;
    }
}


/**
 * @brief   Đọc giá trị tại đỉnh Stack mà không xóa.
 * @param   stack   Stack cần đọc giá trị.
 * @return  Giá trị phần tử trên cùng hoặc STACK_EMPTY nếu Stack rỗng.
 */
int top(Stack stack)
{
    if (isEmpty(stack))
    {
        printf("Stack rỗng!\n");
        return STACK_EMPTY;
    }
    else
    {
        return stack.item[stack.top];
    }
}


/**
 * @brief   Giải phóng bộ nhớ của Stack.
 * @param   stack   Con trỏ tới Stack.
 */
void stack_free(Stack *stack)
{
    if (stack->item != NULL)
    {
        free(stack->item);
        stack->item = NULL; 
    }
}