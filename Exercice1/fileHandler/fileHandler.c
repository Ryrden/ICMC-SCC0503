#include "fileHandler.h"

void writeStudentDataInFile(STUDENT *student, FILE *file) {
    NUSP nusp = get_nUsp(student);
    char *name = get_name(student);
    char *course = get_course(student);
    GRADE grade = get_grade(student);

    fwrite(&nusp, sizeof(NUSP), 1, file);
    fwrite(name, sizeof(NAME), 1, file);
    fwrite(course, sizeof(COURSE), 1, file);
    fwrite(&grade, sizeof(NUSP), 1, file);
}

STUDENT *readStudentDataInFile(FILE *file) {
    NUSP nusp;
    NAME name;
    COURSE course;
    GRADE grade;

    fread(&nusp, sizeof(NUSP), 1, file);
    fread(name, sizeof(NAME), 1, file);
    fread(course, sizeof(COURSE), 1, file);
    fread(&grade, sizeof(GRADE), 1, file);

    STUDENT *student = create_student(nusp, name, course, grade);

    return student;
}