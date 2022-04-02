#include "./list/list.h"
#include "./uspDatabase/uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME_SIZE 10

/*INFORMAÇÕES:
    NOME: Ryan Souza Sá Teles
    nUSP: 12822062
    Turma: BSI [021]
    Instituto: Instituto de Ciências Matemáticas e de Computação
    Disciplina: Estrutura de Dados II
    Professor: Leonardo Tórtoro Pereira
*/ 

long int getDataSize(LIST *, FILE *);
void showAllData(LIST *);
void showHalfDataFromStart(LIST *);
void showHalfDataFromEnd(LIST *);
void showDataFromRange(LIST *, int, int);
void showSpecificData(LIST *, int);

void readDataAndInsert(LIST *, char *);
void processOperation(LIST *, int);

int main() {
    LIST *list = create_list();

    char *file;
    file = (char*) malloc(sizeof(char)*FILE_NAME_SIZE);
    
    scanf("%s", file);
    readDataAndInsert(list, file);

    int command;
    scanf("%d", &command);

    processOperation(list, command);

    free(file);
    list_erase(&list);
}

void readDataAndInsert(LIST *list, char *file) {
    FILE *arq = fopen(file, "rb");
    if (arq == NULL) {
        perror("Error to open Archive");
        exit(EXIT_FAILURE);
    }

    NUSP nUSP;
    NAME name;
    COURSE course;
    GRADE grade;

    long dataSize = getDataSize(list, arq);
    long key = 0;
    for (long i = 0; i < dataSize; i++) {
        fread(&nUSP, sizeof(nUSP), 1, arq);
        fread(&name, sizeof(name), 1, arq);
        fread(&course, sizeof(course), 1, arq);
        fread(&grade, sizeof(grade), 1, arq);

        STUDENT *student = create_student(key, nUSP, name, course, grade);
        list_insert(list, student);
        key++;
    }

    fclose(arq);
}

void processOperation(LIST *list, int command) {
    int start, end;
    if (select_command(command) == all) {
        showAllData(list);
    } else if (select_command(command) == halfFromStart) {
        showHalfDataFromStart(list);
    } else if (select_command(command) == halfFromEnd) {
        showHalfDataFromEnd(list);
    } else if (select_command(command) == fromRangeTo) {
        scanf("%d", &start);
        scanf("%d", &end);
        showDataFromRange(list, start, end);
    } else if (select_command(command) == specificData) {
        int key;
        scanf("%d", &key);
        showSpecificData(list, key);
    } else {
        perror("\n\nCommand not found");
    }
}

long int getDataSize(LIST *list, FILE *arq) {
    long int fileSize, structSize, dataSize;

    fseek(arq, 0, SEEK_END);
    fileSize = ftell(arq);
    fseek(arq, 0, SEEK_SET);
    structSize = get_student_data_size();
    dataSize = (fileSize / structSize); // key on the struct

    return dataSize;
}

void showAllData(LIST *list) {
    int start, end;
    start = 0;
    end = list_size(list) - 1;
    print_list(list, start, end);
}

void showHalfDataFromStart(LIST *list) {
    int start, end;
    start = 0;
    end = (list_size(list) - 1) / 2;
    print_list(list, start, end);
}

void showHalfDataFromEnd(LIST *list) {
    int start, end;
    start = (list_size(list) / 2);
    end = (list_size(list) - 1);
    print_list(list, start, end);
}

void showDataFromRange(LIST *list, int start, int end) {
    start -= 1;
    if (end > list_size(list))
        end = list_size(list);
    print_list(list, start, end - 1);
}

void showSpecificData(LIST *list, int key) {
    if (key > list_size(list))
        key = list_size(list);

    STUDENT *student = sequential_search(list, key - 1);
    print_item(student);
}