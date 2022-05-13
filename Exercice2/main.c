#include "dataHandler/dataHandler.h"
#include "primaryIndex/primaryIndex.h"
#include "uspDatabase/uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10
#define RUN_CODES_PROBLEM 1
#define STRING_SIZE 256

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

void readStudentFile(FILE *dataFile, unsigned int studentOffset);

int main() {
    FILE *dataFile = fopen("datafile.bin", "wb+");
    if (dataFile == NULL) {
        perror("Error to open Archive");
        exit(EXIT_FAILURE);
    }
    FILE *indexFile = fopen("indexfile.bin", "wb+");
    if (indexFile == NULL) {
        perror("Error to open Archive");
        exit(EXIT_FAILURE);
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
            } else {
                printf("O Registro ja existe!\n");
            }
        } else if (select_command(command) == search_) {
            token = strtok(NULL, ",");
            unsigned int key = atoi(token);
            INDEXFILE *registerIndex = search(indexFile, key);
            if (registerIndex)
                readStudentFile(dataFile, get_offset(registerIndex));
            else
                printf("Registro nao encontrado!\n");
        } else if (select_command(command) == delete_) {
            token = strtok(NULL, ",");
            unsigned int key = atoi(token);
            INDEXFILE *registerIndex = search(indexFile, key);
            if (registerIndex) {
                logicalDeletion(dataFile, get_offset(registerIndex));
                deleteIndexInFile(indexFile, key);
            }
        } else if (select_command(command) == exit_) {
            free(line);
            fclose(dataFile);
            break;
        }
    }
    return EXIT_SUCCESS;
}

void readStudentFile(FILE *dataFile, unsigned int studentOffset) {
    fseek(dataFile, studentOffset, SEEK_SET);
    STUDENT *student = readStudentDataInFile(dataFile);

    print_item(student);

    erase_student(&student);
}
