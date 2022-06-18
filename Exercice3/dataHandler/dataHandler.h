#ifndef DATAHNDLER_H
#define DATAHNDLER_H

#include "../Util/util.h"
#include "../uspDatabase/uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeStudentDataInFile(STUDENT *, long, FILE *);
void logicalDeletion(FILE *dataFile, unsigned int studentOffset);
STUDENT *readStudentDataInFile(FILE *, long);

#endif // FILEHANDLER_H
