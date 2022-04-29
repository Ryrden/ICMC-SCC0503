#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Util/util.h"
#include "../uspDatabase/uspDatabase.h"

void writeStudentDataInFile(STUDENT*, FILE*);
STUDENT *readStudentDataInFile(FILE*);
long int getDataSize(FILE *);

#endif //FILEHANDLER_H
