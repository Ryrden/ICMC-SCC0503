#ifndef IO_H
#define IO_H

#include "../fileHandler/fileHandler.h"
#include "../uspDatabase/uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10
#define RUN_CODES_PROBLEM 1
#define STRING_SIZE 256

void readAndWriteStudentFile(FILE *);
void readStudentFile(FILE *);

#endif //IO_H
