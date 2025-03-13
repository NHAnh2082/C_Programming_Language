#include "..\\Header\\DoublyLinkedList.h"

int main()
{
    // Node *node1 = createNode(1);
    // Node *node2 = createNode(2);
    // Node *node3 = createNode(3);

    // node1->next = node3;
    // node1->prev = node2;
    // node2->next = node1;
    // node3->prev = node1;

    // display_forward(node2);
    // printf("\n");
    // display_backward(node2);

    Node *head = NULL;
    push_front(&head, 3);
    push_front(&head, 2);
    push_front(&head, 1);
    push_back(&head, 4);
    push_back(&head, 5);
    insert(&head, 100, 0);
    insert(&head, 150, size(head));
    insert(&head, 50, 3);

    display_forward(head);
    printf("\n");

    pop_front(&head);
    pop_back(&head);
    erase(&head, 0);
    erase(&head, size(head));
    erase(&head, 2);
    display_forward(head);
    printf("\n");

    printf("Giá trị Node đầu: %d\n", front(head));
    printf("Giá trị Node cuối: %d\n", back(head));
    printf("Giá trị Node đầu: %d\n", get(head, 0));
    printf("Giá trị Node cuối: %d\n", get(head, size(head) - 1));
    printf("Giá trị Node 1: %d\n", get(head, 1));
    
    return 0;
}