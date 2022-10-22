#include <stdio.h>
#include <stdlib.h>
typedef struct  node 
{
    int val;
    struct node *next;
} node_t;



// 리스트 삭제 함수
void delete_list(node_t **ptr_head)  {
    node_t *current = *ptr_head;
    *ptr_head = NULL;

    while (current != NULL)  {
        free(current); 
        current = current->next;
    }
}

// 리스트 출력 함수
// 이중포인터를 사용하지 않은 이유는 head포인터를 업데이트 하지 않아도 되기 때문
void print_list(node_t *head)  {
    node_t *current = head;

    while (current != NULL) {
        printf("{%d} -> ", current->val);
        current = current->next;
    }
    printf("NULL");
    printf("\n");
}

// 리스트 추가 함수
void append(node_t **ptr_head, int val) {

    if (*ptr_head == NULL)  {
        *ptr_head = (node_t *)malloc(sizeof(node_t));
        (*ptr_head)->val = val;
        (*ptr_head)->next = NULL;
        return;
    }

    node_t *current = *ptr_head;
    while (current->next != NULL)
        current = current->next;

    current->next = (node_t *)malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

// 맨 앞 노드 생성
void unshift(node_t **ptr_head, int val){

    node_t *new_node;
    new_node = (node_t *)malloc(sizeof(node_t));

    new_node->val = val;
    new_node->next = *ptr_head;
    *ptr_head = new_node;
}

// 맨 앞 노드 삭제 함수
int shift(node_t **ptr_head)   {
    node_t *current = *ptr_head;
    if (current == NULL)
        return -1;

    *ptr_head = current->next;
    int retval = current->val;
    free(current);
    return retval;
}

// 맨뒤 노드 삭제 함수
int pop(node_t **ptr_head)  {
    
    if (*ptr_head == NULL)
        return -1;
    
    node_t *current = *ptr_head;
    
    if (current->next == NULL)  {
        *ptr_head = NULL;
        int retval = current->val;
        free(current);
        return retval;
    }

    node_t *before = *ptr_head;
    current = current->next;

    while (current->next != NULL)  {
        before = before->next;
        current = current->next;
    }

    before->next = NULL;
    int retval = current->val;
    free(current);
    return retval;
}
// 해당 인덱스의 노드를 삭제하는 함수
int remove_by_index(node_t **ptr_head, int index)   {
    if (*ptr_head == NULL)
        return -1;
    else{
        if (index == 0)
            return shift(ptr_head);
        else{
            node_t *current = *ptr_head;
            node_t *before = *ptr_head;

            current = current->next;

            if (current == NULL)
                return -1;

            for (int i = 1; i < index; i++) {
                current = current->next;
                before = before->next;
                if (current == NULL)
                    return -1;   

            before->next = current->next;
            int retval = current->val;
            free(current);
            return retval;
        
        }
    
            
        }
       
    }
    
}

// 메인 함수
int main()  {
    // 첫 노드를 null 설정 -> 일관성있게 작성하기 위해
    node_t *head = NULL;

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    unshift(&head, 4);
    unshift(&head, 5);

    printf("나온 숫자: %d\n", shift(&head));
    printf("나온 숫자: %d\n", remove_by_index(&head,0));
    printf("나온 숫자: %d\n", remove_by_index(&head,1));
    print_list(head);
    printf("나온 숫자: %d\n", pop(&head));

    print_list(head);

    delete_list(&head);
}