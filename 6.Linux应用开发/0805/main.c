#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"
#include "student.h"

int main()
{
    linkList *list = initLinkList();
    char num[8];
    while (1)
        switch (studentMenu())
        {
            // TODO:新增
        case '1':
        {
            puts("新增");
            student s;
            modifyStudent((linkNode *)&s);
            linkNode *newStu = inputStudent(&s);
            getStudentSum(newStu);
            insertLinkList(list, 0, newStu);
        }
        break;
            // TODO:删除
        case '2':
        {
            puts("删除");
            printf("请输入删除的数据索引0~%ld\n", list->size - 1);
            fgets(num, 8, stdin);
            int pos = atol(num);
            if (pos < 0 || pos > list->size - 1)
            {
                printf("数据索引可用值 0~%ld\n", list->size - 1);
                break;
            }
            if (!(*num >= '0' && *num <= '9'))
            {
                puts("索引必须是数字");
                break;
            }

            student *delNode = (student *)getLinkListNode(list, pos);
            removeLinkList(list, pos);
            freeStudent(&delNode);
        }
        break;
        case '3':
        {
            // TODO:修改
            puts("修改");
            printf("请输入修改的数据索引0~%ld\n", list->size - 1);
            fgets(num, 8, stdin);
            int pos = atol(num);
            if (pos < 0 || pos > list->size - 1)
            {
                printf("数据索引可用值 0~%ld\n", list->size - 1);
                break;
            }
            if (!(*num >= '0' && *num <= '9'))
            {
                puts("索引必须是数字");
                break;
            }
            modifyListList(list, pos, modifyStudent);
        }
        break;
        case '4':
        {
            // TODO:查找
            puts("查找");
            student s;
            puts("姓名:");
            fgets(s.name, NAME_SIZE, stdin);
            s.name[strlen(s.name) - 1] = '\0';
            size_t findStart = 0;
            int findSize = 0;
            while (1)
            {
                size_t findPos = findLinkList(list, findStart, (linkNode *)&s, compareStudent);

                if (findPos < list->size)
                {
                    linkNode *resNode = getLinkListNode(list, findPos);
                    printStudent(resNode);
                    findSize++;
                    findStart=findPos+1;
                    continue;
                }
                
                break;
            }

            if (findSize == 0)
            {
                puts("查无此人");
            }
        }
        break;
        case '0':
            // TODO:退出
            // 安全删除现有节点后释放链表
            size_t delSize = list->size;
            for (size_t i = 0; i < delSize; i++)
            {
                student *delNode = (student *)getLinkListNode(list, 0);
                removeLinkList(list, 0);
                freeStudent(&delNode);
            }
            freeLinkList(&list);
            return 0;
        default:
            // TODO:浏览所有
            printLinkList(list, printStudent);
            break;
        }
}