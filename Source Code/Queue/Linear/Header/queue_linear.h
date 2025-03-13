/*****************************************************************************
 * @file     : queue_linear.h
 * @brief    : Triển khai cấu trúc dữ liệu hàng đợi tuyến tính (Linear Queue)
 * @details  : Cung cấp các hàm để khởi tạo, thêm/xóa phần tử, 
 *             kiểm tra trạng thái hàng đợi
 * @author   : Anh Nguyen
 * @date     : 2025-01-04
 * @version  : 1.0
 *****************************************************************************/

#ifndef QUEUE_LINEAR_H
#define QUEUE_LINEAR_H

/* =========================== [INCLUDE FILES] ============================= */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* =========================== [MACRO DEFINITIONS] ========================= */
#define QUEUE_EMPTY -1  /**< Giá trị trả về khi hàng đợi rỗng */


/* =========================== [TYPE DEFINITIONS] ========================== */
/**
 * @brief Cấu trúc của hàng đợi tuyến tính
 */
typedef struct
{
    int *item;  /**< Mảng lưu trữ giá trị các phần tử */ 
    int size;   /**< Số lượng phần tử tối đa          */
    int front;  /**< Chỉ số của phần tử đầu hàng đợi  */
    int rear;   /**< Chỉ số của phần tử cuối hàng đợi */
} Queue;


/**
 * @brief   Khởi tạo hàng đợi.
 * @param   queue   Con trỏ đến hàng đợi cần khởi tạo.
 * @param   size    Kích thước tối đa của hàng đợi.
 * @return  void
 */
void queue_init(Queue *queue, int size);


/**
 * @brief   Kiểm tra xem hàng đợi có rỗng không.
 * @param   queue   Hàng đợi cần kiểm tra.
 * @return  true    Nếu hàng đợi rỗng.
 * @return  false   Nếu hàng đợi không rỗng.
 */
bool queue_isEmpty(Queue queue);


/**
 * @brief   Kiểm tra xem hàng đợi có đầy không.
 * @param   queue   Hàng đợi cần kiểm tra.
 * @return  true    Nếu hàng đợi đầy.
 * @return  false   Nếu hàng đợi chưa đầy.
 */
bool queue_isFull(Queue queue);


/**
 * @brief   Thêm một phần tử vào hàng đợi.
 * @param   queue   Con trỏ đến hàng đợi.
 * @param   data    Dữ liệu cần thêm vào hàng đợi.
 * @return  void
 */
void enqueue(Queue *queue, int data);


/**
 * @brief   Lấy phần tử đầu tiên ra khỏi hàng đợi.
 * @param   queue   Con trỏ đến hàng đợi.
 * @return  int     Giá trị của phần tử được lấy ra.
 */
int dequeue(Queue *queue);


/**
 * @brief   Trả về phần tử đầu tiên trong hàng đợi mà không xóa nó.
 * @param   queue   Hàng đợi cần truy vấn.
 * @return  int     Giá trị của phần tử đầu tiên.
 */
int front(Queue queue);


/**
 * @brief   Trả về phần tử cuối cùng trong hàng đợi mà không xóa nó.
 * @param   queue   Hàng đợi cần truy vấn.
 * @return  int     Giá trị của phần tử cuối cùng.
 */
int rear(Queue queue);


/**
 * @brief   Hiển thị nội dung của hàng đợi.
 * @param   queue   Hàng đợi cần hiển thị.
 * @return  void
 */
void display(Queue queue);


/**
 * @brief   Giải phóng bộ nhớ của hàng đợi.
 * @param   queue   Con trỏ tới Queue.
 */
void queue_free(Queue *queue);

#endif  // QUEUE_LINEAR_H