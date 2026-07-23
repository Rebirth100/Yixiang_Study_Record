#include "link.h"

//创建
linklist_t createLink(data_t a[], int len){
    linklist_t head, tail;

    tail = head = malloc(sizeof(linknode_t));
    head->next = NULL;

    for (int i = 0; i < len; ++i) {
        linklist_t p;

        p = malloc(sizeof(linknode_t));
        p->data = a[i];
        p->next = NULL;

        tail->next = p;
        tail = p;
    }

    return head;
}

//遍历
void displayLink(linklist_t head){
    head = head->next;

    while (head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

linklist_t insertLinkSort(linklist_t head){
}