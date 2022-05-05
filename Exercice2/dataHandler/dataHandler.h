#ifndef DATAHNDLER_H
#define DATAHNDLER_H

#include "../Util/util.h"
#include "../uspDatabase/uspDatabase.h"
#include "../primaryIndex/primaryIndex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct regFields_st REGFIELDS;

int writeRegister(FILE*);
void freeRegister(REGFIELDS*);
void printByRRN(unsigned int, FILE *, char);
void showAllRecords(FILE*, INDEXFILE);

void writeStudentDataInFile(STUDENT *, FILE *);
STUDENT *readStudentDataInFile(FILE *);
long int getDataSize(FILE *);

#endif // FILEHANDLER_H
