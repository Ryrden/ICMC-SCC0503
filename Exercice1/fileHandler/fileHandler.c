#include "fileHandler.h"

static char readCurrentInput(FILE *file, char *currentInput){
    char currentChar;
    int currentInputIndex;
    currentInputIndex = 0;
    currentChar = fgetc(file);
    while((currentChar != EOF) && (currentChar != DELIMITER_CHAR))
    {
        currentInput[currentInputIndex++] = currentChar;
        currentChar = fgetc(file);
    }
    currentInput[currentInputIndex] = '\0';
    return currentChar;
}

void writeDelimitedStudentDataInFile(STUDENT student, FILE *file){
    fprintf(file, "%s", student.name);
    fputc(DELIMITER_CHAR, file);
    fprintf(file, "%d", student.age);
    fputc(DELIMITER_CHAR, file);
    fprintf(file, "%d", student.grade);
    fputc(DELIMITER_CHAR, file);
}

STUDENT readDelimitedStudentDataInFile(FILE *file){
    STUDENT student;
    char currentInput[50];
    readCurrentInput(file, currentInput);
    strcpy(student.name, currentInput);
    readCurrentInput(file, currentInput);
    student.age = atoi(currentInput);
    readCurrentInput(file, currentInput);
    student.grade = atoi(currentInput);
    return student;
}