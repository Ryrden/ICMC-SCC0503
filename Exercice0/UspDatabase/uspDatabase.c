#include "uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student_st {
    int nUsp;
    char name[50];
    char course[50];
    float grade;
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

    return ERROR;
}

STUDENT *create_student(NUSP nusp, NAME name, COURSE course, GRADE grade) {
    STUDENT *student = (STUDENT *)malloc(sizeof(STUDENT));
    student->nUsp = nusp;
    strcpy(student->name, name);
    strcpy(student->course, course);
    student->grade = grade;
    return student;
}

void printItem(STUDENT *student) {
    printf("nUSP: %d \nNome: %s\nCurso: %s \nNota: %.2f\n", student->nUsp, student->name, student->course, student->grade);
}

boolean item_apagar(void **item) {
    if (*item != NULL) {
        //(*item)->key = ERRO; /*apaga o item simbolicamente*/
        free(*item);
        *item = NULL;
        return TRUE;
    }
    return FALSE;
}

NUSP getKey(STUDENT *student) {
    if (student != NULL) {
        return student->nUsp;
    }
    return ERRO;
}

long int getStudentDataSize(){
    return sizeof(STUDENT);
}