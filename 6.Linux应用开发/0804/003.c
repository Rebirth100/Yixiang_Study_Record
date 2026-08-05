/*
//作业:从以下三种定义中实现链表或者动态数组,要求通用性(能处理任意类型的数据)
////////////////1////////////////
//节点
typedef  struct  LinkNode
{
    void *data;//数据域
    struct LinkNode *next;//指针域
}linkNode;
//链表
typedef  struct  LinkList
{
    linkNode *head;//链表头指针
    unsigned  size;//数据个数
}linkList;

///////////////2/////////////////
//节点
typedef  struct  LinkNode
{
    struct LinkNode *next;
}linkNode;

//链表
typedef  struct  LinkList
{
    linkNode  head;
    unsigned  size;
}linkList;


//使用链表构建自定义数据
typedef  struct  Data
{
   linkNode next;
   char name;
   int age;
   int score[64];
}data;

///////////////3/////////////////
typedef  struct DynamicArray
{
    void **data;//数据域数组  每个void*托管一个数据
    unsigned size; //有效元素个数
    unsigned capacity;//当前数组容量
}dynamicArray;

*/

#include "003.h"
#include <stdlib.h>

// 创建空链表
linkList* createLinkList(void) {
    linkList *list = (linkList *)malloc(sizeof(linkList));
    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->size = 0;
    return list;
}

// 销毁链表
void destroyLinkList(linkList *list, void (*freeData)(void *)) {
    if (list == NULL)
        return;
    linkNode *cur = list->head;
    while (cur != NULL) {
        linkNode *next = cur->next;
        if (freeData != NULL)
            freeData(cur->data);   // 用户负责释放数据
        free(cur);                 // 释放节点
        cur = next;
    }
    free(list);
}

// 内部：创建新节点
static linkNode* createNode(void *data) {
    linkNode *node = (linkNode *)malloc(sizeof(linkNode));
    if (node == NULL)
        return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

// 头插
int insertHead(linkList *list, void *data) {
    if (list == NULL)
        return 0;
    linkNode *node = createNode(data);
    if (node == NULL)
        return 0;
    node->next = list->head;
    list->head = node;
    list->size++;
    return 1;
}

// 尾插
int insertTail(linkList *list, void *data) {
    if (list == NULL)
        return 0;
    linkNode *node = createNode(data);
    if (node == NULL)
        return 0;
    if (list->head == NULL) {
        list->head = node;
    } else {
        linkNode *cur = list->head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = node;
    }
    list->size++;
    return 1;
}

// 指定位置插入
int insertAt(linkList *list, unsigned pos, void *data) {
    if (list == NULL || pos > list->size)
        return 0;
    if (pos == 0)
        return insertHead(list, data);
    if (pos == list->size)
        return insertTail(list, data);

    linkNode *node = createNode(data);
    if (node == NULL)
        return 0;

    // 找到前驱
    linkNode *cur = list->head;
    for (unsigned i = 0; i < pos - 1; ++i)
        cur = cur->next;
    node->next = cur->next;
    cur->next = node;
    list->size++;
    return 1;
}

// 删除第一个匹配 key 的节点
void* deleteNode(linkList *list, void *key, int (*cmp)(void *, void *)) {
    if (list == NULL || list->head == NULL || cmp == NULL)
        return NULL;

    linkNode *prev = NULL;
    linkNode *cur = list->head;
    while (cur != NULL) {
        if (cmp(cur->data, key) == 0) {
            // 删除 cur
            if (prev == NULL)
                list->head = cur->next;
            else
                prev->next = cur->next;
            void *data = cur->data;
            free(cur);
            list->size--;
            return data;
        }
        prev = cur;
        cur = cur->next;
    }
    return NULL;
}

// 删除指定位置节点
void* deleteAt(linkList *list, unsigned pos) {
    if (list == NULL || list->head == NULL || pos >= list->size)
        return NULL;

    linkNode *prev = NULL;
    linkNode *cur = list->head;
    for (unsigned i = 0; i < pos; ++i) {
        prev = cur;
        cur = cur->next;
    }
    // 此时 cur 指向待删节点
    if (prev == NULL)
        list->head = cur->next;
    else
        prev->next = cur->next;

    void *data = cur->data;
    free(cur);
    list->size--;
    return data;
}

// 查找
void* search(linkList *list, void *key, int (*cmp)(void *, void *)) {
    if (list == NULL || list->head == NULL || cmp == NULL)
        return NULL;
    linkNode *cur = list->head;
    while (cur != NULL) {
        if (cmp(cur->data, key) == 0)
            return cur->data;
        cur = cur->next;
    }
    return NULL;
}

// 遍历打印
void traverse(linkList *list, void (*print)(void *)) {
    if (list == NULL || print == NULL)
        return;
    linkNode *cur = list->head;
    while (cur != NULL) {
        print(cur->data);
        cur = cur->next;
    }
}

// 获取大小
unsigned getSize(linkList *list) {
    return (list == NULL) ? 0 : list->size;
}