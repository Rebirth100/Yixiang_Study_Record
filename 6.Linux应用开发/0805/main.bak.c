#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"
#include "student.h"
#define TEST_COUNT 20

int main()
{
    linkList *list = initLinkList();

    for (int i = 0; i < TEST_COUNT; i++)
    {
        insertLinkList(list, 0, initStudent());
    }

    printLinkList(list, printStudent);

    int pos;
    while (1)
    {
        puts("请输入查找位置(-1退出):");
        scanf("%d", &pos);
        if (pos == -1)
        {
            break;
        }
        linkNode *res = getLinkListNode(list, pos);
        if (res)
        {
            printStudent(res);
        }
    }

    while (1)
    {
        puts("请输入删除位置(-1退出):");
        scanf("%d", &pos);
        if (pos == -1)
        {
            break;
        }
        linkNode *res = getLinkListNode(list, pos);
        if (res)
        {
            removeLinkList(list,pos);
            freeStudent((student**)&res);
        }
        printLinkList(list, printStudent);
    }

    printLinkList(list, printStudent);

    size_t  count=list->size;
    for(int i=0;i<count;i++)
    {
        linkNode *res = getLinkListNode(list, 0);
        if (res)
        {
            removeLinkList(list,0);
            freeStudent((student**)&res);
        }
    }

    freeLinkList(&list);

    return 0;
}


/**************************
 linkList  *List=initLinkList();
 while(1)
 {
    switch(menu())
    {
        case '1':
        case '0':
            //释放所有节点
            //释放链表
            //退出
    }
 }
 * ************************** */




 /**************************
 linkList  *List=initLinkList();
 //从文件载入数据大链表
 //XXXXXXX
 
 while(1)
 {
    switch(menu())
    {
        case '1':
        case '0':
            //保存现有数据到文件
            //释放所有节点
            //释放链表
            //退出
    }
 }
 * ************************** */