#include "./uspDatabase/uspDatabase.h"
#include "./fileHandler/fileHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME_SIZE 10

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
    NUSP nUSP;
    NAME name;
    COURSE course;
    GRADE grade;

    //Leitura na ordem
    //[Numero USP][Nome][Curso][Nota]]
    char *line = (char*)malloc(sizeof(char)*256);
    while(line = readLine()){
        nUSP = readStringUntilReach(line,DELIMITER_CHAR)
        line++ = line.strstr(line,',');
        name = readStringUntilReach(line,DELIMITER_CHAR)
        line++ = line.strstr(line,',');
        course = readStringUntilReach(line,DELIMITER_CHAR)
        line++ = line.strstr(line,',');
        grade = line;
    }
    free(line);

    //Salvar os dados lidos em dois arquivos binários
    //um para o índice e outro de dados


    
    return EXIT_SUCCESS;
}