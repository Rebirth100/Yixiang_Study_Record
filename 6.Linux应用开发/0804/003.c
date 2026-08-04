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