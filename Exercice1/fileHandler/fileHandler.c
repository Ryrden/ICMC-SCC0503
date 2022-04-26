#include "fileHandler.h"

struct fileHeader_st {
    unsigned int nRegister;
    unsigned char regSize;
    int stackHead;
};

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

void writeDelimitedStudentDataInFile(STUDENT *student, FILE *file){
    NUSP nusp = get_nUsp(student);
    char *name = get_name(student);
    char *course = get_course(student);
    GRADE grade = get_grade(student);
    
    //Escrever dado, delimitador, dado, delimitador, ... 
    fwrite(&nusp, sizeof(NUSP), 1, file);
    //fwrite(DELIMITER_CHAR, sizeof(char), 1, file);
    fwrite(&name, sizeof(char), 1, file);
    //fwrite(DELIMITER_CHAR, sizeof(char), 1, file);
    fwrite(&course, sizeof(char), 1, file);
    //fwrite(DELIMITER_CHAR, sizeof(char), 1, file);
    fwrite(&grade, sizeof(NUSP), 1, file);
}

STUDENT *readDelimitedStudentDataInFile(FILE *file){
    STUDENT *student = create_student(1,"a","b",5);
    return student;
}