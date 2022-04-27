#include "fileHandler.h"

struct fileHeader_st {
    unsigned int nRegister;
    unsigned char regSize;
    int stackHead;
};

static char readCurrentInput(FILE *file, char *input){
    char currentChar;
    int inputIndex;
    inputIndex = 0;
    currentChar = fgetc(file);
    while((currentChar != EOF) && (currentChar != DELIMITER_CHAR))
    {
        input[inputIndex++] = currentChar;
        currentChar = fgetc(file);
    }
    input[inputIndex] = '\0';
    return currentChar;
}

void writeDelimitedStudentDataInFile(STUDENT *student, FILE *file){
    NUSP nusp = get_nUsp(student);
    char *name = get_name(student);
    char *course = get_course(student);
    GRADE grade = get_grade(student);
    
    fwrite(&nusp, sizeof(NUSP), 1, file);
    fputc(DELIMITER_CHAR, file);
    fwrite(&name, sizeof(char), 1, file);
    fputc(DELIMITER_CHAR, file);
    fwrite(&course, sizeof(char), 1, file);
    fputc(DELIMITER_CHAR, file);
    fwrite(&grade, sizeof(NUSP), 1, file);
    fputc(DELIMITER_CHAR, file);
}

STUDENT *readDelimitedStudentDataInFile(FILE *file){
    char input[256];
    
    //leitura
}
    return student;
}