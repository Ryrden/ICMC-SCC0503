#ifndef PRIMARYINDEX_H
#define PRIMARYINDEX_H

#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct indexFile_st INDEXFILE;

unsigned int get_key(INDEXFILE *);
unsigned int get_offset(INDEXFILE *);
unsigned int set_key(INDEXFILE *, unsigned int);
unsigned int set_offset(INDEXFILE *, unsigned int);
INDEXFILE *createIndexData(unsigned int key, unsigned int offSet);
void eraseIndexData(INDEXFILE **indexData);
INDEXFILE *search(FILE *indexFile, unsigned int key);
void deleteIndexInFile(FILE *indexFile, unsigned int key);
boolean writeIndexInFile(FILE *, INDEXFILE *);

#endif // PRIMARYINDEX_H
