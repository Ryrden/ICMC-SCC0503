#include "io.h"

void readAndWriteStudentFile(FILE *dataFile) {

    char *line = (char *)malloc(sizeof(char) * STRING_SIZE);
    while (fgets(line, sizeof(char) * STRING_SIZE, stdin)) {
        char *token = strtok(line, " ");
        char *command = token;

    }
    free(line);
}

void insertData(char *line, FILE *dataFile) {
    NUSP nusp;
    NAME name;
    LASTNAME lastName;
    COURSE course;
    GRADE grade;

    char *token = strtok(line, " ");

    token = strtok(NULL, ",");

    nusp = atoi(token);
    strcpy(name, token);

    token = strtok(NULL, ",");
    strcpy(lastName, token);

    token = strtok(NULL, ",");
    strcpy(course, token);

    token = strtok(NULL, ",");
    grade = atof(token);

    STUDENT *student = create_student(nusp, name, lastName, course, grade);
    writeStudentDataInFile(student, dataFile);
    erase_student(&student);
}

void readStudentFile(FILE *dataFile, unsigned int studentOffset) {

    fseek(dataFile, studentOffset, SEEK_SET);
    STUDENT *student = readStudentDataInFile(dataFile);

    print_student(student);

    erase_student(&student);
}
