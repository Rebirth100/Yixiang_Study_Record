#include "student.h"
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

void freeStudent(student **stu)
{
    if (stu && (*stu))
    {
#ifdef DEBUG
        printf("释放了student:%s\n",(*stu)->name);
#endif
        free(*stu);
    }
}

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