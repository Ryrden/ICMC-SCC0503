#ifndef DATAHNDLER_H
#define DATAHNDLER_H

#include "../Util/util.h"
#include "../uspDatabase/uspDatabase.h"
#include "../fileHandler/fileHandler.h"
#include "../primaryIndex/primaryIndex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct regFields_st REGFIELDS;

int writeRegister(FILE*, REGFIELDS*, FILEHEADER, INDEXFILE )
REGFIELDS *getRegister();
void freeRegister(REGFIELDS*);
void printByRRN(unsigned int, FILE *, char);
void showAllRecords(FILE*, INDEXFILE ,FILEHEADER);

void writeStudentDataInFile(STUDENT *, FILE *);
STUDENT *readStudentDataInFile(FILE *);
long int getDataSize(FILE *);

#endif // FILEHANDLER_H
