#ifndef PRIMARYINDEX_H
#define PRIMARYINDEX_H

#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct indexFile_st INDEXFILE;

unsigned int get_key(INDEXFILE *);
unsigned int get_offset(INDEXFILE *);
INDEXFILE *createIndexData(unsigned int key, unsigned int offSet);
INDEXFILE *search(FILE *indexFile, unsigned int key);
FILE* deleteIndexInFile(FILE *indexFile, unsigned int key);
boolean writeIndexInFile(FILE *, INDEXFILE *);

#endif // PRIMARYINDEX_H
