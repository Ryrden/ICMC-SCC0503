#include "uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student_st {
    int nUsp;
    char name[NAME_SIZE];
    char course[COURSE_SIZE];
    float grade;
    long key;
};

operation select_command(int command) {
    if (command == 1)
        return all;
    else if (command == 2)
        return halfFromStart;
    else if (command == 3)
        return halfFromEnd;
    else if (command == 4)
        return fromRangeTo;
    else if (command == 5)
        return specificData;

    return ERRO;
}

STUDENT *create_student(long key,NUSP nusp, NAME name, COURSE course, GRADE grade) {
    STUDENT *student = (STUDENT *)malloc(sizeof(STUDENT));
    student->nUsp = nusp;
    strcpy(student->name, name);
    strcpy(student->course, course);
    student->grade = grade;
    student->key = key;
    return student;
}

void print_item(STUDENT *student) {
    printf("nUSP: %d\n", student->nUsp);
    printf("Nome: %s\n", student->name);
    printf("Curso: %s\n", student->course);
    printf("Nota: %.2f\n", student->grade);
}

boolean item_apagar(void **item) {
    if (*item != NULL) {
        //(*item)->key = ERROR; /*apaga o item simbolicamente*/
        free(*item);
        *item = NULL;
        return TRUE;
    }
    return FALSE;
}

NUSP get_key(STUDENT *student) {
    if (student != NULL) {
        return student->key;
    }
    return ERRO;
}

int get_student_data_size(){
    return sizeof(STUDENT) - LONG_INT_SIZE_ON_STRUCT;
}