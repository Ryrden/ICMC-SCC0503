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
void searchAndPrint(FILE *file, KEY key);
void searchAndDelete(FILE *, FILE *, KEY);
void insertIfNotExists(FILE *, FILE *, STUDENT*);

int main() {
    FILE *dataFile = fopen("datafile.bin", "wb+");
    verifyNullPointerExceptionToFile(dataFile);

    FILE *indexFile = fopen("indexfile.bin", "wb+");
    verifyNullPointerExceptionToFile(indexFile);

    int RRN = 0;                
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

            STUDENT *student = create_student(nusp, name, lastName, course, grade);
            
            insertIfNotExists(dataFile, indexFile, student);
            
            erase_student(&student);
        } else if (select_command(command) == search_) {
            token = strtok(NULL, ",");
            KEY key = atoi(token);
            searchAndPrint(dataFile,key);
        } else if (select_command(command) == delete_) {
            token = strtok(NULL, ",");
            KEY key = atoi(token);
            searchAndDelete(indexFile,dataFile,key);
        } else if (select_command(command) == exit_) {
            break;
        }
    }
    free(line);
    fclose(dataFile);
    fclose(indexFile);
    return EXIT_SUCCESS;
}

void insertIfNotExists(FILE *dataFile, FILE *indexFile, STUDENT *student){
    INDEXFILE *registerIndex = search(indexFile, get_nusp(student));
    if (registerIndex == NULL) {
        writeStudentDataInFile(student, dataFile);
        
        unsigned int studentOffset = RRN * studentSize;
        INDEXFILE *indexData = createIndexData(get_nusp(student), studentOffset);
        writeIndexInFile(indexFile, indexData);

        RRN++;
        eraseIndexData(&indexData);
    } else {
        eraseIndexData(&registerIndex);
        printf("O Registro ja existe!\n");
    }
}

void searchAndPrint(FILE *file, KEY key){
    INDEXFILE *registerIndex = search(file, key);
    if (registerIndex) {
        readStudentFile(file, get_offset(registerIndex));
        eraseIndexData(&registerIndex);
    } else {
        printf("Registro nao encontrado!\n");
    }
}

void searchAndDelete(FILE *indexFile, FILE *dataFile, KEY key){
    INDEXFILE *registerIndex = search(indexFile, key);
    if (registerIndex) {
        logicalDeletion(dataFile, get_offset(registerIndex));
        deleteIndexInFile(indexFile, key);
        eraseIndexData(&registerIndex);
    }
}

void readStudentFile(FILE *dataFile, unsigned int studentOffset) {
    fseek(dataFile, studentOffset, SEEK_SET);
    STUDENT *student = readStudentDataInFile(dataFile);

    print_item(student);

    erase_student(&student);
}
