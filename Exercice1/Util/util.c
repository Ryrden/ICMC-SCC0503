#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void boolean_print(boolean bool) {
    if (bool == TRUE) {
        printf("TRUE\n");
    } else if (bool == FALSE) {
        printf("FALSE\n");
    } else {
        printf("ERRO\n");
    }
}

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

char *readStringUntilReach(char *str1, char caractere) {
    char c;
    char *str2 = (char *)malloc(sizeof(char) * 256);
    int index = 0;
    while ((c = str1[index]) != EOF) {
        if (c == caractere) {
            str2[index] = '\0';
            break;
        }
        str2[index] = c;
        index++;
    }
    return str2;
}

long int getDataSize(FILE *file) {
    long int fileSize, structSize, dataSize;

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    structSize = get_student_data_size();
    dataSize = (fileSize / structSize); // key on the struct

    return dataSize;
}
