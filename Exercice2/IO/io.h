#ifndef IO_H
#define IO_H

#include "../uspDatabase/uspDatabase.h"
#include "../dataHandler/dataHandler.h"
#include "../primaryIndex/primaryIndex.h"
#include "../list/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10
#define RUN_CODES_PROBLEM 1
#define STRING_SIZE 256

void insertData(char *line, FILE *dataFile);
void readAndWriteStudentFile(FILE *);
void readStudentFile(FILE *, unsigned int);

#endif //IO_H
