#include "./bTree/bTree.h"
#include "./dataHandler/dataHandler.h"
#include "./uspDatabase/uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 300

/*INFORMAÇÕES:
    NOME: Ryan Souza Sá Teles
    nUSP: 12822062
    NOME: Silmar Pereira Da Silva Junior
    nUSP: 12623950
    Turma: BSI [021]
    Instituto: Instituto de Ciências Matemáticas e de Computação
    Disciplina: Estrutura de Dados II
    Professor: Leonardo Tórtoro Pereira
*/

int main() {
    FILE *dataFile;
    HEADER *header;
    BTPAGE *bTree;
    FILE *bTreeFile;

    if (fopen("treeFile.bin", "rb") != NULL) {
        bTreeFile = fopen("treeFile.bin", "rb+");
        verifyNullPointerExceptionToFile(bTreeFile);

        dataFile = fopen("dataFile.bin", "rb+");
        verifyNullPointerExceptionToFile(dataFile);

        header = getTreeHeader(bTreeFile);
        bTree = getRoot(bTreeFile, header);
    } else {
        bTreeFile = fopen("treeFile.bin", "wb+");
        verifyNullPointerExceptionToFile(bTreeFile);

        dataFile = fopen("dataFile.bin", "wb+");
        verifyNullPointerExceptionToFile(dataFile);

        header = createHeader(); // Somente no final do arquivo retornar aqui dps
        bTree = createTree(bTreeFile, header);
    }

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

            // write student on dataFile
            STUDENT *student = create_student(nusp, name, lastName, course, grade);
            writeStudentDataInFile(student, RRN, dataFile);
            erase_student(&student);

            // add registry to bTree
            RECORD *record = createRecord(nusp, RRN);
            bTreeInsert(record, bTree, header, bTreeFile);
            bTree = changeRootIfNeeded(bTree, header, bTreeFile);

            free(record);
            record = NULL;
            RRN++;

            continue;
        } else if (select_command(command) == search_) {
            token = strtok(NULL, ",");
            unsigned int key = atoi(token);
            long itemRRN = bTreeSearch(bTree, key, bTreeFile);

            if (itemRRN == -1) {
                printf("Registro nao encontrado!\n");
            } else {
                STUDENT *std = readStudentDataInFile(dataFile, itemRRN);
                print_item(std);
                erase_student(&std);
            }
            continue;

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
            long itemRRN = bTreeSearch(bTree, nusp, bTreeFile);
            writeStudentDataInFile(student, itemRRN, dataFile);

            erase_student(&student);
            continue;

        } else if (select_command(command) == exit_) {
            writeTreeHeader(header, bTreeFile);
            break;
        }
    }
    free(line);
    fclose(bTreeFile);
    fclose(dataFile);
    freePage(bTree);
    free(header);
    return EXIT_SUCCESS;
}
