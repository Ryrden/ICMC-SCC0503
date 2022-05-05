#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "../Util/util.h"
#include "../uspDatabase/uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REG_SIZE 128
#define REGHEADER_SIZE 5

#define HEADER_SIZE 9

typedef struct fileHeader_st FILEHEADER;

FILEHEADER *getHeader(FILE *);
boolean writeHeader(FILE *, FILEHEADER *);

void writeStudentDataInFile(STUDENT *, FILE *);
STUDENT *readStudentDataInFile(FILE *);
long int getDataSize(FILE *);

#endif // FILEHANDLER_H
