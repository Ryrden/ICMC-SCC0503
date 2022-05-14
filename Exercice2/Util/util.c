#include "util.h"
#include <stdio.h>
#include <stdlib.h>

char *readLine() {
    char *string = NULL;
    char currentInput;
    int index = 0;
    do {
        currentInput = (char)getchar();
        string = (char *)realloc(string, sizeof(char) * (index + 1));
        string[index] = currentInput;
        index++;
        if (currentInput == '\r') {
            currentInput = (char)getchar();
        }
    } while ((currentInput != '\n') && (currentInput != EOF));
    string[index - 1] = '\0';
    return string;
}

char *readStringUntilReach(char caractere) {
    char c;
    char *string = (char *)malloc(sizeof(char) * 256);
    int index = 0;
    while (scanf("%c", &c) != EOF) {
        if (c == caractere) {
            string[index] = '\0';
            break;
        }
        string[index] = c;
        index++;
    }
    return string;
}

long int getDataSize(FILE *file, long structSize) {
    long int fileSize, dataSize;

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    dataSize = (fileSize / structSize); // key on the struct

    return dataSize;
}

void verifyNullPointerExceptionToFile(FILE *file){
    if (file == NULL) {
            perror("Error to open Archive");
            exit(EXIT_FAILURE);
        }
}