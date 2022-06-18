#include "./bTree/bTree.h"
#include "./uspDatabase/uspDatabase.h"
#include "./dataHandler/dataHandler.h"
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
    FILE *dataFile;
    HEADER *header;
    BTPAGE *bTree;
    FILE *bTreeFile;

				// TO DO filtrar registros iguais, não devemos aceita-los
    // TO DO: mudar para getOrCreateRoot (se existir um aquivo de arvore devemos usar ele)
    // criar getOrCreateHeader para
    // criar writeheader (header deve ser escrito por ultimo, durante o encerramento do programa)


				/*
    if (fopen("treeFile.bin", "rb") != NULL) {
        bTreeFile = fopen("treeFile.bin", "rb+");
        verifyNullPointerExceptionToFile(bTreeFile);
        header = getTreeHeader(dataFile);
        bTree = getOrCreateRoot(dataFile);
    } else {*/
        bTreeFile = fopen("treeFile.bin", "wb+");
        verifyNullPointerExceptionToFile(bTreeFile);
        dataFile = fopen("dataFile.bin", "wb+");
        verifyNullPointerExceptionToFile(dataFile);
        header = createHeader(); //Somente no final do arquivo retornar aqui dps
        bTree = createTree(bTreeFile, header);
    //}

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
            strcpy(name, &token[1]);
												name[strlen(name)-1] = '\0';

            token = strtok(NULL, ",");
            strcpy(lastName, &token[1]);
												lastName[strlen(lastName)-1] = '\0';

            token = strtok(NULL, ",");
            strcpy(course, &token[1]);
												course[strlen(course)-1] = '\0';

            token = strtok(NULL, ",");
            grade = atof(token);

												// write student on dataFile
            STUDENT *student = create_student(nusp, name, lastName, course, grade);
												writeStudentDataInFile(student, RRN, dataFile);
												erase_student(&student);

            // add registry to bTree
            RECORD *record = createRecord(nusp, RRN);
            bTreeInsert(record, bTree, header, bTreeFile);
												bTree = changeRootIfNeeded(bTree, header, bTreeFile);

												free(record);
												record = NULL;
            RRN++;

            continue;
        } else if (select_command(command) == search_) {
            token = strtok(NULL, ",");
            unsigned int key = atoi(token);
												long itemRRN = bTreeSelect(bTree, key, bTreeFile);
												if (itemRRN == -1){
																printf("Registro nao encontrado!\n");
												}
												else {
																STUDENT *std = readStudentDataInFile(dataFile, itemRRN);
																print_item(std);
																erase_student(&std);
												}
												continue;

        } else if (select_command(command) == update_) {
												NUSP nusp;
            NAME name;
            LASTNAME lastName;
            COURSE course;
            GRADE grade;

            token = strtok(NULL, ",");
            nusp = atoi(token);

            token = strtok(NULL, ",");
            strcpy(name, &token[1]);
												name[strlen(name)-1] = '\0';

            token = strtok(NULL, ",");
            strcpy(lastName, &token[1]);
												lastName[strlen(lastName)-1] = '\0';

            token = strtok(NULL, ",");
            strcpy(course, &token[1]);
												course[strlen(course)-1] = '\0';

            token = strtok(NULL, ",");
            grade = atof(token);

            STUDENT *student = create_student(nusp, name, lastName, course, grade);
												long itemRRN = bTreeSelect(bTree, nusp, bTreeFile);
												writeStudentDataInFile(student, itemRRN, dataFile);

												erase_student(&student);
												continue;

        } else if (select_command(command) == exit_) {
            break;
        }
    }
    free(line);
    fclose(bTreeFile);
    // fclose(indexFile); has to be created yet
    return EXIT_SUCCESS;
}
