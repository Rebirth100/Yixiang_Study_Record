#include "linklist.h"
// TODO:链表初始化
linkList *initLinkList(void)
{
    linkList *list = (linkList *)malloc(sizeof(linkList));
    if (list)
    {
        list->head.next = NULL;
        list->size = 0;
#ifdef DEBUG
        printf("链表初始化完毕 list:%p\n", list);
#endif
        return list;
    }

    return NULL;
}

// TODO:释放链表
void freeLinkList(linkList **list)
{
    if (list && (*list))
    {
#ifdef DEBUG
        printf("释放 list:%p ", *list);
#endif
        free(*list);
        *list = NULL;
#ifdef DEBUG
        printf("释放成功\n");
#endif
    }
}

// TODO:新增数据
void insertLinkList(linkList *list, size_t pos, linkNode *data)
{
    if (list == NULL || data == NULL)
    {
        return;
    }

    if (pos >= list->size)
    {
        pos = 0;
    }

    linkNode *prev = &(list->head);
    for (int i = 0; i < pos; i++)
    {
        prev = prev->next;
    }
    data->next = prev->next;
    prev->next = data;
    list->size++;
}

// TODO:输出链表
void printLinkList(linkList *list, void (*print)(linkNode *))
{
    if (list == NULL || print == NULL)
    {
        return;
    }
    if (list->size == 0)
    {
        printf("空链表 size=0\n");
        return;
    }
    linkNode *current = list->head.next;
    size_t index = 0;
    while (current != NULL)
    {
        printf("[%ld]\t", index++);
        print(current);
        current = current->next;
    }
}

// TODO: 查找节点
linkNode *getLinkListNode(linkList *list, size_t pos)
{
    if (list == NULL || pos >= list->size)
    {
        return NULL;
    }
    linkNode *prev = &(list->head);
    for (size_t i = 0; i < pos; i++)
    {
        prev = prev->next;
    }
    return prev->next;
}

// TODO:删除节点
void removeLinkList(linkList *list, size_t pos)
{
    if (list == NULL || pos >= list->size)
    {
        return;
    }
    linkNode *prev = &(list->head);
    for (size_t i = 0; i < pos; i++)
    {
        prev = prev->next;
    }
    prev->next = prev->next->next;
    list->size--;
}

// TODO:修改节点
void modifyListList(linkList *list, size_t pos, void (*modify)(linkNode *))
{
    if (list == NULL || pos >= list->size || modify == NULL)
    {
        return;
    }
    linkNode *prev = &(list->head);
    for (size_t i = 0; i < pos; i++)
    {
        prev = prev->next;
    }
    modify(prev->next);
}

// TODO:查找节点(从start位置开始向后查找信息)
size_t findLinkList(linkList *list, size_t start, linkNode *data, int (*compare)(linkNode *, linkNode *))
{
    if (list == NULL || start > list->size - 1 || data == NULL || compare == NULL)
    {
        return 0xFFFFFFFF;
    }

    linkNode *prev = &(list->head);
    for (size_t i = 0; i < start; i++)
    {
        prev = prev->next;
    }

    for (size_t s = start; s < list->size; s++)
    {
        if (compare(data, prev->next) == 0)
        {
            return s;
        }
        prev = prev->next;
    }
    return 0xFFFFFFFF;
}

// TODO:链表数据持久化存储
void saveLinkList(linkList *list, size_t enumSize, char *dbPath)
{
    char dbFileName[256] = "\0";
    if (list == NULL || enumSize <= sizeof(linkNode) || dbPath == NULL)
    {
#ifdef DEBUG
        fprintf(stderr, "call %s 参数错误 list:%p enumSize=%ld dbPath=%s\n",
            __FUNCTION__,list,enumSize,dbPath
        );
#endif
        return;
    }

    if (strlen(dbPath) == 0)
    {
        sprintf(dbFileName, "%s","linkDB");
    }
    else
    {
        sprintf(dbFileName, "%s", dbPath);
    }

    // 创建数据库文件
    FILE *fp = fopen(dbFileName, "wb+");
    if (fp == NULL)
    {
#ifdef DEBUG
        fprintf(stderr, "call %s 创建数据库文件失败\n",
            __FUNCTION__
        );
#endif
        return;
    }
    size_t size=0;
    fwrite(&size,sizeof(size),1,fp);
    if(list->size!=0)
    {
        linkNode  *prev=&(list->head);
        size_t  index=0;
        while(prev->next!=NULL)
        {
            fwrite(prev->next,enumSize,1,fp);
            index++;
#ifdef DEBUG
        fprintf(stderr, "正在写入数据%ld\n",
             index
        );
#endif
            prev=prev->next;
        }
        rewind(fp);
        fwrite(&index,sizeof(index),1,fp);
#ifdef DEBUG
        fprintf(stderr, "保存链表到数据库文件完毕，共写入:%ld数据\n",
             index
        );
#endif
    }

    fclose(fp);
    return ;
}


//TODO:从文件载入到链表
void loadLinkList(linkList*list,size_t  enumSize,char *dbPath,linkNode *(*initLinkData)(linkNode *s))
{
    char dbFileName[256] = "\0";
    if (list == NULL || enumSize <= sizeof(linkNode) || dbPath == NULL ||initLinkData==NULL)
    {
#ifdef DEBUG
        fprintf(stderr, "call %s 参数错误 list:%p enumSize=%ld dbPath=%s initLinkData=%p\n",
            __FUNCTION__,list,enumSize,dbPath,initLinkData
        );
#endif
        return;
    }

    if (strlen(dbPath) == 0)
    {
        sprintf(dbFileName, "%s","linkDB");
    }
    else
    {
        sprintf(dbFileName, "%s", dbPath);
    }

    FILE  *fp=fopen(dbFileName,"rb+");
    if(fp==NULL)
    {
#ifdef DEBUG
        fprintf(stderr, "从磁盘载入数据未发现数据库文件，请进入主菜单按0正常退出即可,未载入数据");
#endif
        return;
    }
#ifdef DEBUG
        fprintf(stderr, "打开数据库文件成功，正在载入数据");
#endif
    size_t  count=0;
    fread(&count,sizeof(count),1,fp);
#ifdef DEBUG
        fprintf(stderr, "即将从文件载入%ld数据\n",count);
#endif 
    linkNode *dbAdd=(linkNode*)malloc(enumSize);
    if(dbAdd)
    {
         for(int i=0;i<count;i++)
         {
            fread(dbAdd,enumSize,1,fp);
#ifdef DEBUG
        fprintf(stderr, "从文件获取数据[%d]成功\n",i);
#endif
            linkNode *newData=initLinkData(dbAdd);
            insertLinkList(list,0,newData);
#ifdef DEBUG
        fprintf(stderr, "向链表插入数据[%d]\n",i);
#endif
         }
#ifdef DEBUG
        fprintf(stderr, "从磁盘载入%ld数据到链表\n",count);
#endif    
    }
   
    free(dbAdd);
    fclose(fp);
}