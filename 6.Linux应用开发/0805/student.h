#ifndef STUDENT_H_V0805_HGG_001
#define STUDENT_H_V0805_HGG_001


#include  "linklist.h"

#define     NAME_SIZE 128
#define     SCORE_SIZE 4

//TODO: student
struct  student
{
    linkNode  node;
    char name[NAME_SIZE];
    int score[SCORE_SIZE];
    int sum;
};
typedef struct  student student;


//TODO: initStudent
linkNode *initStudent();
//TODO: inputStudent
linkNode* inputStudent(student *s);
//TODO: freeStudent
void freeStudent(student **);
//TODO: getStudentSum
int getStudentSum(linkNode *);
//TODO: printStudent
void printStudent(linkNode *);
//TODO: studentMenu
char studentMenu();
//TODO:modifyStudent
void modifyStudent(linkNode*);
//TODO:compareStudent
int compareStudent(linkNode*,linkNode*);
#endif