#include "io.h"

void process(BTPAGE **bTree, HEADER **header, FILE **bTreeFile, FILE **dataFile) {
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
            strcpy(name, &token[1]);
            name[strlen(name) - 1] = '\0';

            token = strtok(NULL, ",");
            strcpy(lastName, &token[1]);
            lastName[strlen(lastName) - 1] = '\0';

            token = strtok(NULL, ",");
            strcpy(course, &token[1]);
            course[strlen(course) - 1] = '\0';

            token = strtok(NULL, ",");
            grade = atof(token);

            STUDENT *student = create_student(nusp, name, lastName, course, grade);
            RECORD *record = createRecord(nusp, RRN);

            insertAndWriteInFile(bTree, bTreeFile, dataFile, header, &student, &record, RRN);

            erase_student(&student);
            free(record);
            record = NULL;
            RRN++;
        } else if (select_command(command) == search_) {
            token = strtok(NULL, ",");
            unsigned int key = atoi(token);
            searchAndPrint(bTree, key, bTreeFile, dataFile);
        } else if (select_command(command) == update_) {
            NUSP nusp;
            NAME name;
            LASTNAME lastName;
            COURSE course;
            GRADE grade;

            token = strtok(NULL, ",");
            nusp = atoi(token);

            token = strtok(NULL, ",");
            strcpy(name, &token[1]);
            name[strlen(name) - 1] = '\0';

            token = strtok(NULL, ",");
            strcpy(lastName, &token[1]);
            lastName[strlen(lastName) - 1] = '\0';

            token = strtok(NULL, ",");
            strcpy(course, &token[1]);
            course[strlen(course) - 1] = '\0';

            token = strtok(NULL, ",");
            grade = atof(token);

            STUDENT *student = create_student(nusp, name, lastName, course, grade);

            searchAndUpdate(bTree, &student, bTreeFile, dataFile);

            erase_student(&student);
            continue;

        } else if (select_command(command) == exit_) {
            writeTreeHeader(*header, *bTreeFile);
            break;
        }
    }
    free(line);
}

void freeAllMemory(FILE **bTreeFile, FILE **dataFile, BTPAGE **bTree, HEADER **header) {
    fclose(*bTreeFile);
    fclose(*dataFile);
    freePage(*bTree);
    free(*header);
}

void insertAndWriteInFile(BTPAGE **bTree, FILE **bTreeFile, FILE **dataFile, HEADER **header, STUDENT **student, RECORD **record, long RRN) {
    writeStudentDataInFile(*student, RRN, *dataFile);
    // add registry to bTree
    bTreeInsert(*record, *bTree, *header, *bTreeFile);
    (*bTree) = changeRootIfNeeded(*bTree, *header, *bTreeFile);
}

void searchAndPrint(BTPAGE **bTree, unsigned int key, FILE **bTreeFile, FILE **dataFile) {
    long itemRRN = bTreeSearch(*bTree, key, *bTreeFile);

    if (itemRRN == -1) {
        printf("Registro nao encontrado!\n");
    } else {
        STUDENT *std = readStudentDataInFile(*dataFile, itemRRN);
        print_item(std);
        erase_student(&std);
    }
}

void searchAndUpdate(BTPAGE **bTree, STUDENT **student, FILE **bTreeFile, FILE **dataFile) {
    long itemRRN = bTreeSearch(*bTree, get_nusp(*student), *bTreeFile);
    writeStudentDataInFile(*student, itemRRN, *dataFile);
}