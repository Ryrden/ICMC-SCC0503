#ifndef IO_H
#define IO_H

#include "../bTree/bTree.h"
#include "../dataHandler/dataHandler.h"
#include "../uspDatabase/uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRING_SIZE 300

void process(BTPAGE **, HEADER **, FILE **, FILE **);

void freeAllMemory(FILE **, FILE **, BTPAGE **, HEADER **);

void insertAndWriteInFile(BTPAGE **, FILE **, FILE **, HEADER **, STUDENT **, RECORD **, long);

void searchAndPrint(BTPAGE **, unsigned int, FILE **, FILE **);

void searchAndUpdate(BTPAGE **, STUDENT **, FILE **, FILE **);

#endif // IO_H