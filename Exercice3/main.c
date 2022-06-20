#include "IO/io.h"

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

    if (fopen("treeFile.bin", "rb") != NULL) {
        bTreeFile = fopen("treeFile.bin", "rb+");
        verifyNullPointerExceptionToFile(bTreeFile);

        dataFile = fopen("dataFile.bin", "rb+");
        verifyNullPointerExceptionToFile(dataFile);

        header = getTreeHeader(bTreeFile);
        bTree = getRoot(bTreeFile, header);
    } else {
        bTreeFile = fopen("treeFile.bin", "wb+");
        verifyNullPointerExceptionToFile(bTreeFile);

        dataFile = fopen("dataFile.bin", "wb+");
        verifyNullPointerExceptionToFile(dataFile);

        header = createHeader(); // Somente no final do arquivo retornar aqui dps
        bTree = createTree(bTreeFile, header);
    }

    process(&bTree, &header, &bTreeFile, &dataFile);

    freeAllMemory(&bTreeFile, &dataFile, &bTree, &header);
    return EXIT_SUCCESS;
}