#ifndef LINKLIST_H
#define LINKLIST_H

#include <stddef.h>   // for size_t (optional)

// 节点定义
typedef struct LinkNode {
    void *data;               // 指向任意类型数据
    struct LinkNode *next;    // 下一节点
} linkNode;

// 链表定义
typedef struct LinkList {
    linkNode *head;           // 头指针
    unsigned size;            // 节点个数
} linkList;

// ---------- 函数声明 ----------

// 创建空链表
linkList* createLinkList(void);

// 销毁链表：释放所有节点，若 freeData 不为 NULL，则调用它释放每个节点的数据
void destroyLinkList(linkList *list, void (*freeData)(void *));

// 头插：成功返回 1，失败返回 0
int insertHead(linkList *list, void *data);

// 尾插：成功返回 1，失败返回 0
int insertTail(linkList *list, void *data);

// 指定位置插入（pos 从 0 开始），pos 可等于 size 表示尾插
int insertAt(linkList *list, unsigned pos, void *data);

// 删除第一个匹配 key 的节点（通过 cmp 比较），返回被删节点的数据（不释放），未找到返回 NULL
void* deleteNode(linkList *list, void *key, int (*cmp)(void *, void *));

// 删除指定位置节点（pos 从 0 开始），返回被删数据，位置无效返回 NULL
void* deleteAt(linkList *list, unsigned pos);

// 查找第一个匹配 key 的节点，返回数据指针，未找到返回 NULL
void* search(linkList *list, void *key, int (*cmp)(void *, void *));

// 遍历链表，对每个节点数据调用 print 函数
void traverse(linkList *list, void (*print)(void *));

// 返回当前节点个数
unsigned getSize(linkList *list);

#endif