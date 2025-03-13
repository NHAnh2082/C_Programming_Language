#include <stdio.h>
#include "stack.h"

int main()
{
    Stack stack1;

    stack_init(&stack1, 5);

    printf("Push process\n");
    push(&stack1, 10);
    push(&stack1, 20);
    push(&stack1, 30);
    push(&stack1, 40);
    push(&stack1, 50);
    push(&stack1, 60);

    printf("\n");
    printf("Display element\n");
    for(int i = 0; i < stack1.size; i++)
    {
        printf("Element: %d -> addr: %p\n", stack1.item[i], &(stack1.item[i]));
    }

    printf("\n");
    printf("Pop process\n");
    for(int i = 0; i < stack1.size; i++)
    {
        printf("Top element: %d -> Addr: %p\n", top(stack1), &(stack1.item[stack1.top]));
        pop(&stack1);
    }

    // Giải phóng bộ nhớ của stack
    stack_free(&stack1);

    return 0;
}