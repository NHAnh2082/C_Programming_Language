/*****************************************************************************
 * @file     : queue_linear.c
 * @brief    : Định nghĩa các hàm cho cấu trúc dữ liệu hàng dợi tuyến tính
 * @details  : Định nghĩa các hàm để khởi tạo, thêm/xóa phần tử, 
 *             kiểm tra trạng thái hàng đợi
 * @author   : Anh Nguyen
 * @date     : 2025-01-04
 * @version  : 1.0
 *****************************************************************************/

 
/* =========================== [INCLUDE FILES] ============================= */
#include "..\\Header\\queue_circular.h"


/* =========================== [FUNCTION IMPLEMENTATION] =================== */
/**
 * @brief   Khởi tạo hàng đợi.
 * @param   queue   Con trỏ đến hàng đợi cần khởi tạo.
 * @param   size    Kích thước tối đa của hàng đợi.
 * @return  void
 */
void queue_init(Queue *queue, int size)
{
    queue->size  = size;
    queue->item  = (int*)malloc(size * sizeof(int));
    queue->front = queue->rear = -1;
}


/**
 * @brief   Kiểm tra xem hàng đợi có rỗng không.
 * @param   queue   Hàng đợi cần kiểm tra.
 * @return  true    Nếu hàng đợi rỗng.
 * @return  false   Nếu hàng đợi không rỗng.
 */
bool queue_isEmpty(Queue queue)
{
    return (queue.front == -1);
}


/**
 * @brief   Kiểm tra xem hàng đợi có đầy không.
 * @param   queue   Hàng đợi cần kiểm tra.
 * @return  true    Nếu hàng đợi đầy.
 * @return  false   Nếu hàng đợi chưa đầy.
 */
bool queue_isFull(Queue queue)
{
    return ((queue.rear + 1) % queue.size == queue.front);
}


/**
 * @brief   Thêm một phần tử vào hàng đợi.
 * @param   queue   Con trỏ đến hàng đợi.
 * @param   data    Dữ liệu cần thêm vào hàng đợi.
 * @return  void
 */
void enqueue(Queue *queue, int data)
{
    if (queue_isFull(*queue))
    {
        printf("Hàng đợi đầy!\n");
        return;
    }
    
    if (queue->front == -1)
    {
        queue->front = queue->rear = 0;
    } 
    else 
    {
        queue->rear = (queue->rear + 1) % queue->size; 
    }
    queue->item[queue->rear] = data;
    printf("Enqueued %d\n", data);
}


/**
 * @brief   Lấy phần tử đầu tiên ra khỏi hàng đợi.
 * @param   queue   Con trỏ đến hàng đợi.
 * @return  int     Giá trị của phần tử được lấy ra.
 */
int dequeue(Queue *queue)
{
    if (queue_isEmpty(*queue))
    {
        printf("Hàng đợi rỗng!\n");
        return QUEUE_EMPTY;
    }
    
    int dequeue_value = queue->item[queue->front];
    
    if (queue->front == queue->rear && (queue->rear ==  queue->size - 1))
    {
        queue->front = queue->rear = -1;
    } 
    else 
    {
        queue->front = (queue->front + 1) % queue->size;
    }
    return dequeue_value;
}


/**
 * @brief   Trả về phần tử đầu tiên trong hàng đợi mà không xóa nó.
 * @param   queue   Hàng đợi cần truy vấn.
 * @return  int     Giá trị của phần tử đầu tiên.
 */
int front(Queue queue)
{
    if (queue_isEmpty(queue))
    {
        printf("Hàng đợi rỗng!\n");
        return QUEUE_EMPTY;
    }
    
    return queue.item[queue.front];
}


/**
 * @brief   Trả về phần tử cuối cùng trong hàng đợi mà không xóa nó.
 * @param   queue   Hàng đợi cần truy vấn.
 * @return  int     Giá trị của phần tử cuối cùng.
 */
int rear(Queue queue)
{
    if (queue_isEmpty(queue))
    {
        printf("Hàng đợi rỗng!\n");
        return QUEUE_EMPTY;
    }
    
    return queue.item[queue.rear];
}


/**
 * @brief   Hiển thị nội dung của hàng đợi.
 * @param   queue   Hàng đợi cần hiển thị.
 * @return  void
 */
void display(Queue queue)
{
    printf("Hàng đợi: ");
    for (int i = 0; i < queue.size; i++) 
    {
        if (queue.front <= queue.rear) 
        {
            if (i >= queue.front && i <= queue.rear)
                printf("%d ", queue.item[i]);
            else
                printf("* "); // Đánh dấu vị trí trống
        } 
        else 
        {
            if (i >= queue.front || i <= queue.rear)
                printf("%d ", queue.item[i]);
            else
                printf("* "); // Đánh dấu vị trí trống
        }
    }
    printf("\n");
}


/**
 * @brief   Giải phóng bộ nhớ của hàng đợi.
 * @param   queue   Con trỏ tới Queue.
 */
void queue_free(Queue *queue)
{
    if (queue->item != NULL)
    {
        free(queue->item);
        queue->item = NULL; 
    }
}