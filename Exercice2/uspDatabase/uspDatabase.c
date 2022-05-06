#include "uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student_st {
    int nUsp;
    char name[NAME_SIZE];
    char lastName[LASTNAME_SIZE];
    char course[COURSE_SIZE];
    float grade;
};

operation select_command(char *command){
    if (!strcmp(command, "insert"))
        return insert_;
    else if (!strcmp(command, "search"))
        return search_;
    else if (!strcmp(command, "delete"))
        return delete_;
    else if (!strcmp(command, "exit"))
        return exit_;

    return ERROR;
}

STUDENT *create_student(NUSP nusp, NAME name, LASTNAME lastName, COURSE course, GRADE grade) {
    STUDENT *student = (STUDENT *)malloc(sizeof(STUDENT));
    student->nUsp = nusp;
    strcpy(student->name, name);
    strcpy(student->lastName, lastName);
    strcpy(student->course, course);
    student->grade = grade;
    return student;
}

void erase_student(STUDENT **student) {
    free(*student);
    (*student) = NULL;
}

int get_student_data_size() {
    return sizeof(STUDENT);
}

void print_item(STUDENT *student) {
    printf("-------------------------------\n");
    printf("nUSP: %d\n", student->nUsp);
    printf("Nome: %s\n", student->name);
    printf("Sobrenome: %s\n", student->lastName);
    printf("Curso: %s\n", student->course);
    printf("Nota: %.2f\n", student->grade);
    printf("-------------------------------\n");
}

NUSP get_nusp(STUDENT *student) {
    if (student != NULL) {
        return student->nUsp;
    }
    return ERRO;
}

char *get_name(STUDENT *student) {
    if (student != NULL) {
        return student->name;
    }
    return NULL;
}

char *get_lastName(STUDENT *student) {
    if (student != NULL) {
        return student->lastName;
    }
    return NULL;
}

char *get_course(STUDENT *student) {
    if (student != NULL) {
        return student->course;
    }
    return NULL;
}

GRADE get_grade(STUDENT *student) {
    if (student != NULL) {
        return student->grade;
    }
    return ERRO;
}