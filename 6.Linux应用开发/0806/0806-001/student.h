#ifndef STUDENT_H_V0805_HGG_001
#define STUDENT_H_V0805_HGG_001
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#define  NO_LINK_LIST

#ifdef  NO_LINK_LIST
    typedef  struct LinkNode
    {
        struct LinkNode *next; 
    }linkNode;
#else
    #include "linklist.h"
#endif

#define     NAME_SIZE 128
#define     SCORE_SIZE 4

//TODO: student
struct  student
{
    linkNode  node;//8
    char name[NAME_SIZE];//128
    int score[SCORE_SIZE];//16
    int sum;//4
};
typedef struct  student student;

//TODO: autoSetStudent
void autoSetStudent(student *);


//TODO: initStudent
linkNode *initStudent();
//TODO: inputStudent
linkNode* inputStudent(linkNode *s);
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