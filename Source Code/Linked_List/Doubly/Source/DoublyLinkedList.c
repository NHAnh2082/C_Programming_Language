/***********************************************************************************
 * @file    Doubly_Linked_List.c
 * @brief   Implement danh sách liên kết đôi (Doubly Linked List).
 * @details Chương trình này cung cấp các thao tác cơ bản trên danh sách liên kết
 *          đôi như thêm, xóa, chèn, truy vấn và hiển thị danh sách theo hai chiều.
 * @version 1.0
 * @date    2025-02-20
 * @author  Anh Nguyen
 ***********************************************************************************/

#include "..\\Header\\DoublyLinkedList.h"


/**
 * @brief   Khởi tạo một node mới.
 * @param   newData Giá trị của node mới.
 * @return  Con trỏ đến node mới được tạo.
 */
Node* createNode(int newData)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = newData;
    node->next = NULL;
    node->prev = NULL;
    return node;
}


/**
 * @brief   Đếm số lượng node trong danh sách liên kết.
 * @param   head Con trỏ đến node đầu tiên của danh sách.
 * @return  Số lượng node trong danh sách.
 */
int size(Node *head)
{
    unsigned int count = 0;

    if (head == NULL) return 0;

    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}


/**
 * @brief   Thêm một node vào đầu danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @param   newData Giá trị của node mới.
 */
void push_front(Node **head, int newData)
{
    Node *new_node = createNode(newData);

    if (*head == NULL) 
    {
        *head = new_node;
    }
    else
    {
        new_node->next = *head;

        (*head)->prev = new_node;
    
        *head = new_node;
    }
}


/**
 * @brief   Thêm một node vào cuối danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @param   newData Giá trị của node mới.
 */
void push_back(Node **head, int newData)
{
    Node *new_node = createNode(newData);

    if (*head == NULL)
    {
        *head = new_node;
    }
    else 
    {
        Node *p = *head;

        // Duyệt qua từng Node để tìm Node cuối cùng
        while (p->next != NULL) p = p->next;

        p->next = new_node;

        new_node->prev = p;
    }
}


/**
 * @brief   Chèn một node vào vị trí bất kỳ trong danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @param   newData Giá trị của node mới.
 * @param   position Vị trí cần chèn.
 */
void insert(Node **head, int newData, uint8_t position)
{
    Node *new_node = createNode(newData);

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    if (position == 0)
    {
        push_front(head, newData);
    }
    else if (position == (size(*head) - 1) || position == (size(*head)))
    {
        push_back(head, newData);
    }
    else
    {
        Node *p = *head;
        uint8_t index = 0;

        while (p != NULL && index != position - 1)
        {
            index++;
            p = p->next;
        }

        if (index == position - 1)
        {
            new_node->next = p->next;
            new_node->prev = p;

            p->next = new_node;
        }
    }
}


/**
 * @brief   Xóa node đầu tiên trong danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 */
void pop_front(Node **head)
{
    if (*head == NULL)
    {
        printf("Không tồn tại node để xóa!\n");
        return;
    }

    Node *temp = (*head)->next;
    free(*head);
    *head = temp;
}


/**
 * @brief   Xóa node cuối cùng trong danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 */
void pop_back(Node **head)
{
    if (*head == NULL)
    {
        printf("Không có Node!\n");
        return;
    }

    Node *p = *head;
    uint8_t index = 0;

    while (p->next != NULL && index != size(*head) - 2)
    {
        index++;
        p = p->next;
    }

    if (index == size(*head) - 2)
    {
        free(p->next);
        p->next = NULL;
    }
}


/**
 * @brief   Xóa node tại vị trí bất kỳ trong danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @param   position Vị trí của node cần xóa.
 */
void erase(Node **head, uint8_t position)
{
    if (*head == NULL)
    {
        printf("Không có Node!\n");
        return;
    }

    if (position == 0)
    {
        pop_front(head);
    }
    else if (position == size(*head) - 1 || position == size(*head))
    {
        pop_back(head);
    }
    else 
    {
        Node *p = *head;
        uint8_t index = 0;

        while (p != NULL && index != position - 1)
        {
            index++;
            p = p->next;
        }

        if (index == position - 1)
        {
            Node *temp = p->next;
            p->next = p->next->next;
            if (p->next != NULL) p->next->prev = p;
            free(temp);
        }
    }
}


/**
 * @brief   Đọc giá trị node đầu tiên trong danh sách.
 * @param   head Con trỏ đến node đầu tiên của danh sách.
 * @return  Giá trị của node đầu tiên.
 */
int front(Node *head)
{
    if (head == NULL)
    {
        printf("List rỗng");
        return LIST_EMPTY;
    } 
    return head->data;
}


/**
 * @brief   Đọc giá trị node cuối cùng trong danh sách.
 * @param   head Con trỏ đến node đầu tiên của danh sách.
 * @return  Giá trị của node cuối cùng.
 */
int back(Node *head)
{
    if (head == NULL)
    {
        printf("List rỗng");
        return LIST_EMPTY;
    }

    Node *p = head;
    while (p->next != NULL)  p = p->next;
    return p->data;
}


/**
 * @brief   Đọc giá trị node tại vị trí bất kỳ trong danh sách.
 * @param   head Con trỏ đến node đầu tiên của danh sách.
 * @param   position Vị trí cần lấy giá trị.
 * @return  Giá trị của node tại vị trí chỉ định.
 */
int get(Node *head, uint8_t position)
{
    if (head == NULL)
    {
        printf("List rỗng");
        return LIST_EMPTY;
    } 

    if (position == 0)
    {
        return front(head);
    }
    else if (position == size(head) - 1 || position == size(head))
    {
        return back(head);
    }
    else 
    {
        Node *p = head;
        uint8_t index = 0;

        while (p != NULL && index != position)
        {
            index++;
            p = p->next;
        }

        if (index == position) return p->data;
    }
}


/**
 * @brief   Hiển thị danh sách liên kết - duyệt theo thứ tự trái sang phải.
 * @param   head Con trỏ đến node đầu tiên của danh sách.
 */
void display_forward(Node *head)
{
    uint8_t i=0;
    if (head == NULL)
    {
        printf("Không có Node!\n");
        return;
    }

    while (head != NULL)
    {
        printf("Node %d: %d\n", i, head->data);
        head = head->next;
        i++;
    }
}


/**
 * @brief   Hiển thị danh sách liên kết - duyệt theo thứ tự phải sang trái.
 * @param   head Con trỏ đến node đầu tiên của danh sách.
 */
void display_backward(Node *head)
{
    uint8_t i=0;
    if (head == NULL)
    {
        printf("Không có Node!\n");
        return;
    }

    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
        i++;
    }

    while (temp != NULL)
    {
        printf("Node %d: %d\n", i, temp->data);
        temp = temp->prev;
        i--;
    }
}
