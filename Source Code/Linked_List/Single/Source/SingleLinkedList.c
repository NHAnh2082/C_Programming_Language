/******************************************************************************
 * @file    Single_Linked_List.c
 * @brief   Implement danh sách liên kết đơn (Singly Linked List).
 * @details Chương trình này cung cấp các thao tác cơ bản trên danh sách liên kết
 *          đơn như thêm, xóa, chèn, truy vấn và hiển thị danh sách.
 * @version 1.0
 * @date    2025-02-20
 * @author  Anh Nguyen
 ******************************************************************************/

#include "..\\Header\\SingleLinkedList.h"

/**
 * @brief   Khởi tạo một node mới.
 * @param   newData Giá trị của node mới.
 * @return  Con trỏ đến node mới được tạo.
 */
Node* createNode(int newData)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->next = NULL;
    node->data = newData;
    return node;
}


/**
 * @brief   Kiểm tra trạng thái hiện tại của danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 */
bool list_isEmpty(Node *head)
{
    return (head == NULL);
}


/**
 * @brief   Đếm số lượng node trong danh sách liên kết.
 * @param   head Con trỏ đến node đầu tiên của danh sách.
 * @return  Số lượng node trong danh sách.
 */
int size(Node *head)
{
    unsigned int count = 0;

    if (list_isEmpty(head)) return 0;

    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}


/**
 * @brief   Thêm một node vào cuối danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @param   newData Giá trị của node mới.
 * @return  void
 */
void push_back(Node **head, int newData)
{
    Node *new_node = createNode(newData);
    
    if (list_isEmpty(*head))
    {
        *head = new_node;
        return;
    } 

    Node *p = *head;

    // Duyệt qua từng Node để tìm Node cuối cùng
    while (p->next != NULL) p = p->next;

    p->next = new_node;
}


/**
 * @brief   Thêm một node vào đầu danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @param   newData Giá trị của node mới.
 * @return  void
 */
void push_front(Node **head, int newData)
{
    Node *new_node = createNode(newData);

    if (list_isEmpty(*head))
    {
        *head = new_node;
    } 
    else 
    {
        new_node->next = *head;
        *head = new_node;
    }
}


/**
 * @brief   Chèn một node vào vị trí bất kỳ trong danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @param   newData Giá trị của node mới.
 * @param   position Vị trí cần chèn.
 * @return  void
 */
void insert(Node **head, int newData, uint8_t position)
{
    Node *new_node = createNode(newData);

    if (list_isEmpty(*head))
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
            p->next = new_node;
        }
    }
}


/**
 * @brief   Xóa node cuối cùng trong danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @return  void
 */
void pop_back(Node **head)
{
    if (list_isEmpty(*head))
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
 * @brief   Xóa node đầu tiên trong danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @return  void
 */
void pop_front(Node **head)
{
    if (list_isEmpty(*head))
    {
        printf("Không tồn tại node để xóa!\n");
        return;
    }

    Node *new_head = (*head)->next;
    free(*head);
    *head = new_head;
}


/**
 * @brief   Xóa node tại vị trí bất kỳ trong danh sách.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @param   position Vị trí của node cần xóa.
 * @return  void
 */
void erase(Node **head, int position)
{
    if (list_isEmpty(*head))
    {
        printf("Không tồn tại node để xóa!\n");
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
            free(temp);
        }
    }
}


/**
 * @brief   Hiển thị danh sách hiện tại.
 * @param   head Con trỏ đến con trỏ của node đầu tiên.
 * @return  void
 */
void display(Node *head)
{
    uint8_t i = 0;
    if (list_isEmpty(head))
    {
        printf("Không có node\n");
    } 
    else 
    {
        while (head != NULL)
        {
            printf("Node %d: %d\n", i, head->data);
            head = head->next;
            i++;
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
    if (list_isEmpty(head))
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
    if (list_isEmpty(head))
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
int get(Node *head, int position)
{
    if (list_isEmpty(head))
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
    return 0;
}
