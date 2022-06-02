#include "./bTree/bTree.h"
#include "./pageHandler/pageHandler.h"
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
    FILE *dataFile = fopen("datafile.bin", "wb+");
    verifyNullPointerExceptionToFile(dataFile);

				// TO DO: mudar para getOrCreateRoot (se existir um aquivo de arvore devemos usar ele)
				// criar getOrCreateHeader para 
				// criar writeheader (header deve ser escrito por ultimo, durante o encerramento do programa)
    FILE *bTreeFile = fopen("datafile.bin", "wb+");
    verifyNullPointerExceptionToFile(dataFile);

				HEADER *header = createHeader();
    BTPAGE *bTree = createTree(bTreeFile, header);

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

            STUDENT *student = create_student(nusp, name, lastName, course, grade);

												// add registry to bTree
												RECORD *record = createRecord(nusp, RRN);
												RRN++;

												continue;
												// add registry to registryFile/dataFile

        } else if (select_command(command) == search_) {
            token = strtok(NULL, ",");
            unsigned int key = atoi(token);

        } else if (select_command(command) == delete_) {
            token = strtok(NULL, ",");
            unsigned int key = atoi(token);

        } else if (select_command(command) == exit_) {
            break;
        }
    }
    free(line);
    fclose(dataFile);
    // fclose(indexFile); has to be created yet
    return EXIT_SUCCESS;
}
