#ifndef HOMEWORK_LINK_H
#define HOMEWORK_LINK_H

#include "malloc.h"
#include "stdio.h"
#include "stdbool.h"

typedef int data_t;

typedef struct Node{
    data_t data;
    struct Node *next;
}linknode_t, *linklist_t;

//创建
linklist_t createLink(data_t a[], int len);

//遍历
void displayLink(linklist_t head);

//插入排序
linklist_t insertLinkSort(linklist_t head);


#endif //HOMEWORK_LINK_H
