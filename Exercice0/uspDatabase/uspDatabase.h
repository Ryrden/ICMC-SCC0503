#ifndef USPDATABASE_H
#define USPDATABASE_H

#include "../Util/util.h"

typedef int NUSP;
typedef char NAME[50];
typedef char COURSE[50];
typedef float GRADE;
typedef struct student_st STUDENT;

typedef enum {
    all = 1,
    halfFromStart,
    halfFromEnd,
    fromRangeTo,
    specificData,
    ERRO = -1
} operation;

operation select_command(int);
int get_student_data_size();
STUDENT *create_student(long,NUSP, NAME, COURSE, GRADE);
NUSP get_key(STUDENT *);
boolean item_apagar(void **);
void print_item(STUDENT *);

#endif // !USPDATABASE_H