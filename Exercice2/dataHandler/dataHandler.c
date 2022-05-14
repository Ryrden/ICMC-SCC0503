#include "dataHandler.h"

void writeStudentDataInFile(STUDENT *student, FILE *file) {
    NUSP nusp = get_nusp(student);
    char *name = get_name(student);
    char *lastName = get_lastName(student);
    char *course = get_course(student);
    GRADE grade = get_grade(student);

    // Adicionar Delimit
    fwrite(&nusp, sizeof(NUSP), 1, file);
    fwrite(name, sizeof(NAME), 1, file);
    fwrite(lastName, sizeof(LASTNAME), 1, file);
    fwrite(course, sizeof(COURSE), 1, file);
    fwrite(&grade, sizeof(NUSP), 1, file);
}

void logicalDeletion(FILE *dataFile, unsigned int studentOffset) {
    fseek(dataFile, studentOffset, SEEK_SET);
    fwrite("*|", 2, 1, dataFile);
}

STUDENT *readStudentDataInFile(FILE *file) {
    NUSP nusp;
    NAME name;
    LASTNAME lastName;
    COURSE course;
    GRADE grade;

    // Ler com delimitador
    fread(&nusp, sizeof(NUSP), 1, file);
    fread(name, sizeof(NAME), 1, file);
    fread(lastName, sizeof(LASTNAME), 1, file);
    fread(course, sizeof(COURSE), 1, file);
    fread(&grade, sizeof(GRADE), 1, file);

    STUDENT *student = create_student(nusp, name, lastName, course, grade);

    return student;
}
