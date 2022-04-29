#include "./fileHandler/fileHandler.h"
#include "./uspDatabase/uspDatabase.h"
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

void readAndWriteStudentFile(FILE *);
void readStudentFile(FILE *);

int main() {
    FILE *dataFile = fopen("datafile.bin", "wb+");
    if (dataFile == NULL) {
        perror("Error to open Archive");
        exit(EXIT_FAILURE);
    }

    readAndWriteStudentFile(dataFile);
    readStudentFile(dataFile);
    fclose(dataFile);
    return EXIT_SUCCESS;
}

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