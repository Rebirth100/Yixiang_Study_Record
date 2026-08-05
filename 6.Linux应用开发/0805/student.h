#ifndef STUDENT_H_V0805_HGG_001
#define STUDENT_H_V0805_HGG_001


#include  "linklist.h"

#define  NAME_SIZE 128
#define SCORE_SIZE 4
struct  student
{
    linkNode  node;
    char name[NAME_SIZE];
    int score[SCORE_SIZE];
    int sum;
};
typedef struct  student student;

linkNode *initStudent();
void freeStudent(student **);
int getStudentSum(linkNode *);
void printStudent(linkNode *);

#endif