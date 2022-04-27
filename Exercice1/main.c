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
    while(fgets(line, sizeof(char)*256, stdin)){
								char *token = strtok(line, ",");
								nUSP = atoi(token);
								token = strtok(NULL, ",");
								strcpy(name, token);
								token = strtok(NULL, ",");
								strcpy(course, token);
								token = strtok(NULL, ",");
								grade = atof(token);
				}
    free(line);
				
				printf("%i %s %s %f\n", nUSP, name, course, grade);
    //Salvar os dados lidos em dois arquivos binários
    //um para o índice e outro de dados


    
    return EXIT_SUCCESS;
}
