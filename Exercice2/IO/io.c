#include "io.h"

void readAndWriteStudentFile(FILE *dataFile) {
    NUSP nusp;
    NAME name;
    COURSE course;
    GRADE grade;

    char *line = (char *)malloc(sizeof(char) * STRING_SIZE);
    while (fgets(line, sizeof(char) * STRING_SIZE, stdin)) {
        char *token = strtok(line, " ");
        char *command = token;

        processOperation(line, command);
    }
    free(line);
}

void processOperation(char *line, char *command) {
    if (select_command(command) == insert) {
        insert(line);
    } else if (select_command(command) == search) {
        // search
    } else if (select_command(command) == delete_) {
        // delete
    } else if (select_command(command) == exit_) {
        // exit
    } else {
        perror("\n\nCommand not found");
    }
}

void insert(char *line) {
    char *token = strtok(line, " ");

    token = strtok(NULL, ",");

    nusp = atoi(token);
    strcpy(name, token);

    token = strtok(NULL, ",");
    strcpy(course, token);

    token = strtok(NULL, ",");
    grade = atof(token);

    STUDENT *student = create_student(nusp, name, course, grade);
    writeStudentDataInFile(student, dataFile);
    erase_student(&student);
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
