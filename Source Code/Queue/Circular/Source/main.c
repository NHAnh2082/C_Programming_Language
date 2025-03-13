#include "..\\Header\\queue_circular.h"

// int main()
// {
//     // Queue *queue = queue_Init(5);
    
//     Queue queue;
//     queue_init(&queue, 5);

//     enqueue(&queue, 10);
//     enqueue(&queue, 15);
//     enqueue(&queue, 20);
//     enqueue(&queue, 25);
//     enqueue(&queue, 30);
//     enqueue(&queue, 35);

//     display(queue);

//     printf("Front element: %d\n", front(queue));
//     printf("Rear element: %d\n", rear(queue));

//     printf("Dequeued %d\n", dequeue(&queue));
//     // printf("Dequeued %d\n", dequeue(&queue));
//     // printf("Dequeued %d\n", dequeue(&queue));
//     // printf("Dequeued %d\n", dequeue(&queue));

//     display(queue);

//     enqueue(&queue, 50);
//     // enqueue(&queue, 100);
//     display(queue);

//     // printf("Front element: %d\n", front(queue));
//     // printf("Rear element: %d\n", rear(queue));

//     queue_free(&queue);

//     return 0;
// }



// Hàm tính giai thừa bằng stack
int factorial(int n)    // n! = n(n-1)(n-2)...1
{
    if (n < 0)
    {
        printf("Không thể tính giai thừa của số âm!\n");
        return -1;
    }
    
    Queue factQueue;
    queue_init(&factQueue, n);

    // Đưa các số từ n đến 1 vào stack
    for (int i = n; i > 0; i--) enqueue(&factQueue, i);

    int result = 1;

    // Lấy các số ra khỏi stack và nhân
    while (!queue_isEmpty(factQueue))
    {
        result *= dequeue(&factQueue);
    }

    // Giải phóng bộ nhớ
    queue_free(&factQueue);

    return result;
}

// 5*4*3*2*1

int main()
{
    int number;
    
    printf("Nhập số cần tính giai thừa: ");
    scanf("%d", &number);

    int result = factorial(number);
    if (result != -1)
    {
        printf("Giai thừa của %d là: %d\n", number, result);
    }

    return 0;
}