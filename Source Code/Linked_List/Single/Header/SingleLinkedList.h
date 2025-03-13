/******************************************************************************
 * @file    Single_Linked_List.h
 * @brief   Declaration danh sách liên kết đơn (Singly Linked List).
 * @details Chương trình này cung cấp các thao tác cơ bản trên danh sách liên kết
 *          đơn như thêm, xóa, chèn, truy vấn và hiển thị danh sách.
 * @version 1.0
 * @date    2025-02-20
 * @author  Anh Nguyen
 ******************************************************************************/
#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define LIST_EMPTY 0

/**
 * @struct  Node
 * @brief   Cấu trúc dữ liệu của một nút trong danh sách liên kết đơn.
 */
typedef struct Node
{
    int data;               /**< Dữ liệu của node           */
    struct Node *next;      /**< Con trỏ đến node tiếp theo */
} Node;


/**
 * @brief   Khởi tạo một node mới.
 * @param   newData Giá trị của node mới.
 * @return  Con trỏ đến node mới được tạo.
 */
Node* createNode(int newData);


/**
 * @brief   Đếm số lượng node trong danh sách liên kết.
 * @param   head Con trỏ đến node đầu tiên của danh sách.
 * @return  Số lượng node trong danh sách.
 */
int size(Node *head);


/**
 * @brief   Kiểm tra trạng thái hiện tại của danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 */
bool list_isEmpty(Node *head);

/**
 * @brief   Thêm một node vào cuối danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @param   newData Giá trị của node mới.
 */
void push_back(Node **head, int newData);


/**
 * @brief   Thêm một node vào đầu danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @param   newData Giá trị của node mới.
 */
void push_front(Node **head, int newData);


/**
 * @brief   Chèn một node vào vị trí bất kỳ trong danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @param   newData Giá trị của node mới.
 * @param   position Vị trí cần chèn.
 */
void insert(Node **head, int newData, uint8_t position);


/**
 * @brief   Xóa node cuối cùng trong danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 */
void pop_back(Node **head);


/**
 * @brief   Xóa node đầu tiên trong danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 */
void pop_front(Node **head);


/**
 * @brief   Xóa node tại vị trí bất kỳ trong danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @param   position Vị trí của node cần xóa.
 */
void erase(Node **head, int position);


/**
 * @brief   Hiển thị danh sách hiện tại.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 */
void display(Node *head);


/**
 * @brief   Đọc giá trị node đầu tiên trong danh sách.
 * @param   head Con trỏ đến node đầu tiên của danh sách.
 * @return  Giá trị của node đầu tiên.
 */
int front(Node *head);


/**
 * @brief   Đọc giá trị node cuối cùng trong danh sách.
 * @param   head Con trỏ đến node đầu tiên của danh sách.
 * @return  Giá trị của node cuối cùng.
 */
int back(Node *head);


/**
 * @brief   Đọc giá trị node tại vị trí bất kỳ trong danh sách.
 * @param   head Con trỏ đến node đầu tiên của danh sách.
 * @param   position Vị trí cần lấy giá trị.
 * @return  Giá trị của node tại vị trí chỉ định.
 */
int get(Node *head, int position);


#endif  // SINGLELINKEDLIST_H