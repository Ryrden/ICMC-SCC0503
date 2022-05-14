#include "io.h"

void run() {
    FILE *dataFile = fopen("datafile.bin", "wb+");
    verifyNullPointerExceptionToFile(dataFile);
    FILE *indexFile = fopen("indexfile.bin", "wb+");
    verifyNullPointerExceptionToFile(indexFile);

    int RRN = 0;
    long studentSize = get_student_data_size();
    char *line = (char *)malloc(sizeof(char) * STRING_SIZE);
    while (fgets(line, sizeof(char) * STRING_SIZE, stdin)) {
        char *token = strtok(line, " ");
        char *command = token;

        if (select_command(command) == insert_) {
            NUSP nusp;
            NAME name;
            LASTNAME lastName;
            COURSE course;
            GRADE grade;

            token = strtok(NULL, ",");
            nusp = atoi(token);

            token = strtok(NULL, ",");
            strcpy(name, token);

            token = strtok(NULL, ",");
            strcpy(lastName, token);

            token = strtok(NULL, ",");
            strcpy(course, token);

            token = strtok(NULL, ",");
            grade = atof(token);
            INDEXFILE *registerIndex = search(indexFile, nusp);
            if (registerIndex == NULL) {
                STUDENT *student = create_student(nusp, name, lastName, course, grade);
                writeStudentDataInFile(student, dataFile);

                unsigned int studentOffset = RRN * studentSize;
                INDEXFILE *indexData = createIndexData(nusp, studentOffset);
                writeIndexInFile(indexFile, indexData);

                RRN++;
                erase_student(&student);
                eraseIndexData(&indexData);
            } else {
                eraseIndexData(&registerIndex);
                printf("O Registro ja existe!\n");
            }
        } else if (select_command(command) == search_) {
            token = strtok(NULL, ",");
            unsigned int key = atoi(token);
            INDEXFILE *registerIndex = search(indexFile, key);
            if (registerIndex) {
                readStudentFile(dataFile, get_offset(registerIndex));
                eraseIndexData(&registerIndex);
            } else {
                printf("Registro nao encontrado!\n");
            }
        } else if (select_command(command) == delete_) {
            token = strtok(NULL, ",");
            unsigned int key = atoi(token);
            INDEXFILE *registerIndex = search(indexFile, key);
            if (registerIndex) {
                logicalDeletion(dataFile, get_offset(registerIndex));
                deleteIndexInFile(indexFile, key);
                eraseIndexData(&registerIndex);
            }
        } else if (select_command(command) == exit_) {
            break;
        }
    }
    free(line);
    fclose(dataFile);
    fclose(indexFile);
}

void readStudentFile(FILE *dataFile, unsigned int studentOffset) {
    fseek(dataFile, studentOffset, SEEK_SET);
    STUDENT *student = readStudentDataInFile(dataFile);

    print_item(student);

    erase_student(&student);
}