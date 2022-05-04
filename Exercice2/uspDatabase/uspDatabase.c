#include "uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student_st {
    int nUsp;
    char name[NAME_SIZE];
    char course[COURSE_SIZE];
    float grade;
};

STUDENT *create_student(NUSP nusp, NAME name, COURSE course, GRADE grade) {
    STUDENT *student = (STUDENT *)malloc(sizeof(STUDENT));
    student->nUsp = nusp;
    strcpy(student->name, name);
    strcpy(student->course, course);
    student->grade = grade;
    return student;
}

void erase_student(STUDENT **student){
    free(*student);
    (*student) = NULL;
}

int get_student_data_size(){
    return sizeof(STUDENT);
}

void print_student(STUDENT *student) {
    printf("nUSP: %d\n", student->nUsp);
    printf("Nome: %s\n", student->name);
    printf("Curso: %s\n", student->course);
    printf("Nota: %.2f\n", student->grade);
}

NUSP get_nUsp(STUDENT *student) {
    if (student != NULL) {
        return student->nUsp;
    }
    return ERRO;
}

char *get_name(STUDENT *student){
    if (student != NULL) {
        return student->name;
    }
    return NULL;
}

char *get_course(STUDENT *student){
    if (student != NULL) {
        return student->course;
    }
    return NULL;
}

GRADE get_grade(STUDENT *student){
    if (student != NULL) {
        return student->grade;
    }
    return ERRO;
}