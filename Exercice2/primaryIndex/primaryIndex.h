#ifndef PRIMARYINDEX_H
#define PRIMARYINDEX_H

#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct indexFile_st INDEXFILE;

unsigned int get_key(INDEXFILE*);
INDEXFILE *createIndexData(unsigned int key, unsigned int offSet);
unsigned int search(INDEXFILE *, unsigned int);
int writeIndex(FILE *, INDEXFILE*);

#endif // PRIMARYINDEX_H