#include "..\\Header\\queue_linear.h"

int main()
{
    Queue liQueue;

    queue_init(&liQueue, 5);

    enqueue(&liQueue, 1);
    enqueue(&liQueue, 2);
    enqueue(&liQueue, 3);
    enqueue(&liQueue, 4);
    enqueue(&liQueue, 5);
    enqueue(&liQueue, 6);

    printf("Front: %d\n", front(liQueue));
    printf("Rear: %d\n", rear(liQueue));

    display(liQueue);

    printf("Dequeue %d\n", dequeue(&liQueue));
    printf("Dequeue %d\n", dequeue(&liQueue));
    printf("Dequeue %d\n", dequeue(&liQueue));
    printf("Dequeue %d\n", dequeue(&liQueue));
    printf("Dequeue %d\n", dequeue(&liQueue));

    display(liQueue);

    enqueue(&liQueue, 10); 
    // enqueue(&liQueue, 100);

    display(liQueue);

    // printf("Front: %d\n", front(liQueue));
    // printf("Rear: %d\n", rear(liQueue));

    // queue_free(&liQueue);

    return 0;
}