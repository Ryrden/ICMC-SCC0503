#ifndef DATAHNDLER_H
#define DATAHNDLER_H

#include "../Util/util.h"
#include "../uspDatabase/uspDatabase.h"
#include "../primaryIndex/primaryIndex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITER "|"

void writeStudentDataInFile(STUDENT *, FILE *);
void logicalDeletion(FILE *dataFile, unsigned int studentOffset);
STUDENT *readStudentDataInFile(FILE *);

#endif // FILEHANDLER_H
