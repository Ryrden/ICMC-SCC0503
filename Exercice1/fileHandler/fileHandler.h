#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Util/util.h"
#include "../uspDatabase/uspDatabase.h"

#define DELIMITER_CHAR '|'

typedef struct fileHeader_st FILEHEADER;

void writeDelimitedStudentDataInFile(STUDENT*, FILE*);
STUDENT *readDelimitedStudentDataInFile(FILE*);

#endif //FILEHANDLER_H
