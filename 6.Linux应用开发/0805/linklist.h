#ifndef LINK_LIST_H_V0805_HGG_001
#define LINK_LIST_H_V0805_HGG_001
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>

//节点
typedef  struct LinkNode
{
     struct LinkNode *next; //指针域   
}linkNode;


//TODO:链表
typedef  struct LinkList
{
    linkNode head; //头节点指针
    size_t  size;//有效节点数
}linkList;

//TODO:链表初始化
linkList*initLinkList(void);

//TODO:释放链表
void freeLinkList(linkList**);

//TODO:新增数据
void insertLinkList(linkList*,size_t pos,linkNode *);

//TODO:输出链表
void printLinkList(linkList*,void (*print)(linkNode*));


//TODO: 查找节点
linkNode *getLinkListNode(linkList*,size_t pos);

//TODO:删除节点
void  removeLinkList(linkList*,size_t pos);

// typedef void (*Print)(linkNode*);
// void printLinkList(linkList*,Print  p);

#endif