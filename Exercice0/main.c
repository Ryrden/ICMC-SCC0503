#include "./UspDatabase/uspDatabase.h"
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

long int getDataSize(FILE *arq, STUDENT student);

int main() {
    FILE *arq;
    char file[10];
    scanf("%s", &file);

    arq = fopen(file, "rb");
    if (arq == NULL) {
        perror("Error to open Archive");
        exit(EXIT_FAILURE);
    }

    STUDENT student;
    int command;
    scanf("%d", command);

    if (select_command(command) == all){

    }else if (select)

    long int dataSize = getDataSize(arq, student);
    for (int i = 0; i < dataSize; i++) {
        fread(&student, sizeof(STUDENT), 1, arq);
        printf("nUSP: %d \nNome: %s\nCurso: %s \nNota: %.2f\n\n", student.nUsp, student.name, student.course, student.grade);
    }
}

long int getDataSize(FILE *arq, STUDENT student) {
    long int fileSize, structSize, dataSize;

    fseek(arq, 0, SEEK_END);
    fileSize = ftell(arq);
    fseek(arq, 0, SEEK_SET);
    structSize = sizeof(student);

    dataSize = fileSize / structSize;

    return dataSize;
}