#include "..\\Header\\SingleLinkedList.h"


int factorial(int n)
{
    if (n < 0)
    {
        printf("Không thể tính giai thừa của số âm!\n");
        return -1;
    }

    Node *head = NULL;
    for (int i=n; i>0; i--)
    {
        push_back(&head, i);    // 5 4 3 2 1
    }

    int result = 1;

    while (!list_isEmpty(head))
    {
        result *= back(head);  // 5*4*3*2*1
        pop_back(&head);
    }

    return result;
}

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
}


// int main()
// {
//     // tạo 3 node mới
//     Node *head   = createNode(1);     // 0x01
//     Node *second = createNode(2);     // 0xa2
//     Node *third  = createNode(3);     // 0xb6

//     // liên kết các node
//     head->next = second;
//     second->next = third;

//     // list ban đầu
//     printf("Linked list ban đầu: \n");
//     display(head);    

//     // thêm node mới vào cuối list
//     push_back(&head, 6);

//     // thêm node mới vào đầu list
//     push_front(&head, 15);

//     // thêm node vào vị trí 0 trong list
//     insert(&head, 30, 0);

//     // thêm node vào vị trị cuối trong list
//     insert(&head, 50, size(head));

//     // thêm node vào vị trị 3 trong list
//     insert(&head, 24, 3);

//     // hiển thị các node có trong list
//     printf("\nLinked list mới sau khi thêm: \n");
//     display(head);

//     printf("Số lượng node: %d\n", size(head));

//     printf("Giá trị node đầu tiên: %d\n", front(head));
//     printf("Giá trị node cuối cùng: %d\n", back(head));
//     printf("Giá trị node thứ 3: %d\n", get(head, 3));

//     printf("\nLinked list mới sau khi xóa: \n");
    
//     // xóa node cuối trong list
//     pop_back(&head);

//     // xóa node đầu trong list
//     pop_front(&head);

//     // xóa node thứ 2 trong list
//     erase(&head, 2);

//     display(head);
//     printf("Số lượng node: %d\n", size(head));
//     return 0;
// }
