#ifndef USPDATABASE_H
#define USPDATABASE_H

#include "../Util/util.h"


typedef int NUSP;
typedef char *NAME;
typedef char *COURSE;
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

operation select_command(char *command);

#endif // !USPDATABASE_H