#include "./list/list.h"
#include "./uspDatabase/uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>

/*INFORMAÇÕES:
    NOME: Ryan Souza Sá Teles
    nUSP: 12822062
    Turma: BSI [021]
    Instituto: Instituto de Ciências Matemáticas e de Computação
    Disciplina: Estrutura de Dados II
    Professor: Leonardo Tórtoro Pereira
*/

long int getDataSize(LIST *list, FILE *arq);
void showAllData(LIST *list);
void showHalfDataFromStart(LIST *list);
void showHalfDataFromEnd(LIST *list);
void showDataFromRange(LIST *list, int start, int end);
void showSpecificData(LIST *list, int key);

int main() {
    FILE *arq;
    char file[10];
    scanf("%s", file);

    arq = fopen(file, "rb");
    if (arq == NULL) {
        perror("Error to open Archive");
        exit(EXIT_FAILURE);
    }

    LIST *list;
    list = createList();

    NUSP nUSP;
    NAME name;
    COURSE course;
    GRADE grade;
    long dataSize = getDataSize(list, arq);
    for (int i = 0; i < dataSize; i++) {
        fread(&nUSP, sizeof(nUSP), 1, arq);
        fread(&name, sizeof(name), 1, arq);
        fread(&course, sizeof(course), 1, arq);
        fread(&grade, sizeof(grade), 1, arq);

        STUDENT *student = create_student(nUSP, name, course, grade);
        listInsert(list, student);
    }

    int command;
    scanf("%d", &command);
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
    structSize = getStudentDataSize();
    dataSize = fileSize / structSize;

    return dataSize;
}

void showAllData(LIST *list) {
    int start, end;
    start = 0;
    end = listSize(list);
    printList(list, start, end);
}

void showHalfDataFromStart(LIST *list) {
    int start, end;
    start = 0;
    end = listSize(list) / 2;
    printList(list, start, end);
}

void showHalfDataFromEnd(LIST *list) {
    int start, end;
    start = listSize(list) / 2;
    end = listSize(list);
    printList(list, start, end);
}

void showDataFromRange(LIST *list, int start, int end) {
    long dataCycle;
    dataCycle = end - start;
    dataCycle /= listSize(list);

    start = (start < 1 || start > listSize(list)) ? 0 : start-1;
    end = (end > listSize(list) || end < 1) ? listSize(list) : end;

    if (dataCycle == 0) {
        printList(list, start, end);
    } else {
        for (int i = 0; i < dataCycle; i++) {
            printList(list, start, end);
        }
    }
    dataCycle %= listSize(list);
    if (dataCycle != 0) {
        end = dataCycle;
        printList(list, start, end);
    }
}

void showSpecificData(LIST *list, int key) {
    if (key < 1)
        key = 1;
    else if (key > listSize(list))
        key = listSize(list);

    STUDENT *student = sequentialSearch(list, key);
    printItem(student);
}