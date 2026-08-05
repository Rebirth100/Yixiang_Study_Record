#include "003.h"
#include <stdio.h>
#include <stdlib.h>


// 比较两个 int* 的值
int cmp_int(void *a, void *b) {
    int *pa = (int *)a;
    int *pb = (int *)b;
    return (*pa - *pb);   // 返回 0 表示相等
}

// 打印 int*
void print_int(void *p) {
    int *pi = (int *)p;
    printf("%d ", *pi);
}

// 释放 int* 数据
void free_int(void *p) {
    free(p);
}

int main() {
    // 1. 创建链表
    linkList *list = createLinkList();
    if (list == NULL) {
        printf("创建链表失败\n");
        return -1;
    }

    // 2. 插入一些整数（动态分配内存）
    int *p1 = (int *)malloc(sizeof(int)); *p1 = 10;
    int *p2 = (int *)malloc(sizeof(int)); *p2 = 20;
    int *p3 = (int *)malloc(sizeof(int)); *p3 = 30;
    int *p4 = (int *)malloc(sizeof(int)); *p4 = 40;

    insertTail(list, p1);
    insertTail(list, p2);
    insertHead(list, p3);    // 头插 30
    insertAt(list, 2, p4);   // 在位置2插入40（0-based）

    printf("初始链表（共%d个）：", getSize(list));
    traverse(list, print_int);
    printf("\n");

    // 3. 查找 20
    int key = 20;
    int *found = (int *)search(list, &key, cmp_int);
    if (found)
        printf("找到值 %d\n", *found);
    else
        printf("未找到 %d\n", key);

    // 4. 删除第一个值为 20 的节点（数据不释放，由我们后续处理）
    int *deleted = (int *)deleteNode(list, &key, cmp_int);
    if (deleted) {
        printf("删除了值 %d\n", *deleted);
        free(deleted);   // 释放数据（因为不再使用）
    }

    printf("删除后链表：");
    traverse(list, print_int);
    printf("\n");

    // 5. 删除位置 1 的节点（此时链表为 30, 40, 10？顺序：头插30，尾插10,20，插入40在位置2，所以初始 30->10->40->20，删除20后是30->10->40）
    // 删除位置1（第二个节点，值为10）
    void *del2 = deleteAt(list, 1);
    if (del2) {
        printf("删除位置1的数据：%d\n", *(int *)del2);
        free(del2);
    }

    printf("再次删除后链表：");
    traverse(list, print_int);
    printf("\n");

    // 6. 销毁链表（连同剩余数据一起释放）
    destroyLinkList(list, free_int);

    return 0;
}