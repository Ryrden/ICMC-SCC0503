#ifndef USPDATABASE_H
#define USPDATABASE_H

#include "../Util/util.h"
#define NAME_SIZE 50
#define LASTNAME_SIZE 50
#define COURSE_SIZE 50

typedef int NUSP;
typedef char NAME[NAME_SIZE];
typedef char LASTNAME[LASTNAME_SIZE];
typedef char COURSE[COURSE_SIZE];
typedef float GRADE;

typedef struct student_st STUDENT;

typedef enum {
    insert_ = 1,
    search_,
    delete_,
    exit_,
    ERROR = -1
} operation;

operation select_command(char *command);

int get_student_data_size();
STUDENT *create_student(NUSP, NAME, LASTNAME, COURSE, GRADE);
void erase_student(STUDENT **);
void print_student(STUDENT *);
NUSP get_key(STUDENT *student);
char *get_name(STUDENT *student);
char *get_lastName(STUDENT *student);
char *get_course(STUDENT *student);
GRADE get_grade(STUDENT *student);

#endif // !USPDATABASE_H