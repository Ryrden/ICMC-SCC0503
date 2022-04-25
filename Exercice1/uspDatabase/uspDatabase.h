#ifndef USPDATABASE_H
#define USPDATABASE_H

#include "../Util/util.h"
#define NAME_SIZE 50
#define COURSE_SIZE 50


typedef int NUSP;
typedef char NAME[NAME_SIZE];
typedef char COURSE[COURSE_SIZE];
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
STUDENT *create_student(NUSP, NAME, COURSE, GRADE);
void print_item(STUDENT *);

#endif // !USPDATABASE_H