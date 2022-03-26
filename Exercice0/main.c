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

int main() {
    FILE *arq;
    char file[10];
    scanf("%s", file);

    arq = fopen(file, "rb");
    if (arq == NULL) {
        perror("Error to open Archive");
        exit(EXIT_FAILURE);
    }

    /* STUDENT student;
    long int fileSize, structSize, dataSize;

    fseek(arq, 0, SEEK_END);
    fileSize = ftell(arq);
    fseek(arq, 0, SEEK_SET);
    structSize = sizeof(student);

    dataSize = fileSize / structSize; */

    NUSP nUSP;
    NAME name;
    COURSE course;
    GRADE grade;
    LIST *list;
    list = createList();
    while (!feof(arq)) {
        fread(&nUSP, sizeof(nUSP), 1, arq);
        fread(&name, sizeof(name), 1, arq);
        fread(&course, sizeof(course), 1, arq);
        fread(&grade, sizeof(grade), 1, arq);

        STUDENT *student = create_student(nUSP, name, course, grade);
        listInsert(list, student);

        printf("nUSP: %d \nNome: %s\nCurso: %s \nNota: %.2f\n\n", nUSP, name, course, grade);
    }

    int command;
    scanf("%d", &command);

    if (select_command(command) == all) {

    } else if (select_command(command) == halfFromStart) {

    } else if (select_command(command) == halfFromEnd) {

    } else if (select_command(command) == fromRangeTo) {

    } else if (select_command(command) == specificData) {

    } else {
        perror("\n\nCommand not found");
    }
}

