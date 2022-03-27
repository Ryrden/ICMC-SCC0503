#ifndef USPDATABASE_H
#define USPDATABASE_H

#include "../Util/util.h"
#define ERRO (-32000)

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
    specificData
} operation;

operation select_command(int command);
long int getStudentDataSize();
STUDENT *create_student(NUSP nusp, NAME name, COURSE course, GRADE grade);
NUSP getKey(STUDENT *student);
boolean item_apagar(void **item);
void printItem(STUDENT *student);

#endif // !USPDATABASE_H