#include "io.h"

void readAndWriteStudentFile(FILE *dataFile) {
    NUSP nusp;
    NAME name;
    COURSE course;
    GRADE grade;

    char *line = (char *)malloc(sizeof(char) * STRING_SIZE);
    while (fgets(line, sizeof(char) * STRING_SIZE, stdin)) {
        char *token = strtok(line, ",");
        nusp = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
            break;
        strcpy(name, token);

        token = strtok(NULL, ",");
        strcpy(course, token);

        token = strtok(NULL, ",");
        grade = atof(token);

        STUDENT *student = create_student(nusp, name, course, grade);
        writeStudentDataInFile(student, dataFile);
        erase_student(&student);
    }
    free(line);
}

void readStudentFile(FILE *dataFile) {
    long dataSize = getDataSize(dataFile);
    long studentSize = get_student_data_size();
    for (int i = dataSize - TAM; i < dataSize; i++) {

        long studentOffset = i * studentSize;

        fseek(dataFile, studentOffset, SEEK_SET);
        STUDENT *student = readStudentDataInFile(dataFile);

        print_student(student);
        if (i < dataSize - RUN_CODES_PROBLEM)
            printf("\n");

        erase_student(&student);
    }
}
