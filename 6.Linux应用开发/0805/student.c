#include "student.h"
// TODO: initStudent
linkNode *initStudent()
{
    student *s = (student *)malloc(sizeof(student));
    if (s)
    {
        memset(s, '\0', sizeof(student));
        s->node.next = NULL;
        memset(s->name, rand() % 26 + 64, 4);
        memset(s->name + 4, rand() % 26 + 97, 4);
        memset(s->name + 8, rand() % 26 + 97, 4);

        for (int i = 0; i < SCORE_SIZE; i++)
        {
            s->score[i] = rand() % 70 + 30;
        }

        s->sum = 0;

        // return  &(s->node);

        return (linkNode *)s;
    }
    return NULL;
}
// TODO: freeStudent
void freeStudent(student **stu)
{
    if (stu && (*stu))
    {
#ifdef DEBUG
        printf("释放了student:%s\n", (*stu)->name);
#endif
        free(*stu);
    }
}
// TODO: getStudentSum
int getStudentSum(linkNode *stu)
{
    if (stu)
    {
        student *s = (student *)stu;
        s->sum = 0;
        for (int i = 0; i < SCORE_SIZE; i++)
        {
            s->sum += s->score[i];
        }
        return s->sum;
    }

    return 0;
}
// TODO: printStudent
void printStudent(linkNode *s)
{
    if (s)
    {
        student *stu = (student *)s;
        printf("%s\t", stu->name);
        for (int i = 0; i < SCORE_SIZE; i++)
        {
            printf("%-4d", stu->score[i]);
        }
        printf("%d\n", stu->sum);
    }
}

// TODO: studentMenu
char studentMenu()
{
    char select[8] = "\0";
    fprintf(stderr, "+++++++++++++++++++++++++++++++++\n");
    fprintf(stderr, "|  1.新增 2.删除 3.修改  4.查找 |\n");
    fprintf(stderr, "|  0.退出    其他任意键浏览所有 |\n");
    fprintf(stderr, "+++++++++++++++++++++++++++++++++\n");
    scanf("%1s", select);
    while (getchar() != '\n')
        ;
    return *select;
}

// TODO: inputStudent
linkNode *inputStudent(student *s)
{
    if (s)
    {
        student *stu = (student *)malloc(sizeof(student));
        memcpy(stu, s, sizeof(student));
        stu->node.next = NULL;
        return (linkNode *)stu;
    }
    return NULL;
}

// TODO:modifyStudent
void modifyStudent(linkNode *stu)
{
    if (stu)
    {
        char num[8] = "\0";
        student *s = (student *)stu;
        puts("姓名:");
        fgets(s->name, NAME_SIZE, stdin);
        s->name[strlen(s->name) - 1] = '\0';
        for (int i = 0; i < SCORE_SIZE; i++)
        {
            printf("请输入成绩[%d](0~100)\n", i + 1);
            fgets(num, 8, stdin);
            if (atoi(num) < 0 || atoi(num) > 100)
            {
                puts("成绩范围0~100");
                i--;
                continue;
            }
            if (!(*num >= '0' && *num <= '9'))
            {
                puts("成绩必须是数字");
                i--;
                continue;
            }

            s->score[i] = atoi(num);
        }
        s->sum = 0;
    }
}


//TODO:compareStudent
int compareStudent(linkNode*a,linkNode*b)
{
    if(a==NULL || b==NULL)
    {
        return 0xff;
    }
    student  *x=(student*)a;
    student  *y=(student*)b;
    return strcmp(x->name,y->name);
}